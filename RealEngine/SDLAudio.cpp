//#include "stdafx.h"
#include "SDLAudio.h"

#include <SDL_mixer.h>
#include <map>
#include <cassert>
#include <mutex>
#include <thread>

#define AMOUNT_OF_CHANNELS 2

namespace real
{
	class SDLAudio::SDLAudioImpl final : public Audio
	{
	public:
		explicit SDLAudioImpl()
		{
			if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			}

			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, AMOUNT_OF_CHANNELS, 2048) < 0)
			{
				printf("SDL_mixer could not open audio! SDL_mixer Error: %s\n", Mix_GetError());
			}

			m_Head = 0;
			m_Tail = 0;
		}
		virtual ~SDLAudioImpl() override
		{
			for (const auto& [sound, chunk] : m_AudioClips)
			{
				Mix_FreeChunk(chunk);
				//Mix_FreeChunk(chunk.get());
			}

			m_AudioClips.clear();
		}
		SDLAudioImpl(const SDLAudioImpl& other) = delete;
		SDLAudioImpl operator=(const SDLAudioImpl& rhs) = delete;
		SDLAudioImpl(SDLAudioImpl&& other) = delete;
		SDLAudioImpl operator=(SDLAudioImpl&& rhs) = delete;

		void Update() override
		{
			// TODO: eventqueue : https://gameprogrammingpatterns.com/event-queue.html
			// TODO: implement threading
			// use Mix_FreeChunk when done playing.

			if (m_Head == m_Tail)
				return;

			const auto sound = m_Pending[m_Head];

			if (IsLoaded(sound) == false)
			{
				std::jthread loadingThread(&SDLAudioImpl::LoadSound, this, sound);
				loadingThread.detach();
				//LoadSound(sound);

				std::unique_lock<std::mutex> lock(m_Mutex);
				m_Condition.wait(lock, [this, sound]()
					{
						return IsLoaded(sound);
					});
			}

			std::thread playingThread(&SDLAudioImpl::PlaySound, this, sound);
			playingThread.detach();

			m_Head = (m_Head + 1) % static_cast<int>(max_pending);
		}
		void Play(const Sound sound, const int volume = -1, const int loops = -1) override
		{
			for (int i = m_Head; i != m_Tail; i = (i + 1) % static_cast<int>(max_pending))
			{
				if (m_Pending[i].id == sound.id)
				{
					m_Pending[i].volume = std::max(volume, m_Pending[i].volume);
					return;
				}
			}

			assert((m_Tail + 1) % static_cast<int>(max_pending) != m_Head);

			m_Pending[m_Tail].id = sound.id;
			m_Pending[m_Tail].fileName = sound.fileName;

			if (volume != -1)
				m_Pending[m_Tail].volume = volume;
			else
				m_Pending[m_Tail].volume = sound.volume;

			if (loops != -1)
				m_Pending[m_Tail].loops = loops;
			else
				m_Pending[m_Tail].loops = sound.loops;

			m_Tail = (m_Tail + 1) % static_cast<int>(max_pending);
		}
		void Stop(const Sound /*sound*/) override
		{
			//if (IsLoaded(id) == false)
			//	return;

			
		}

	private:
		bool IsLoaded(const Sound sound)
		{
			//if (m_AudioClips[id].second == nullptr)
			if (m_AudioClips[sound] == nullptr)
				return false;

			return true;
			
			//const auto it = m_AudioClips.find(sound);
			//return it != m_AudioClips.end() && it->second != nullptr;
		}
		void LoadSound(const Sound sound)
		{
			const auto mixChunk = Mix_LoadWAV(sound.fileName.c_str());

			if (!mixChunk) {
				printf("SDL_mixer could not load sound effect file! SDL_mixer Error: %s\n", Mix_GetError());
				return;
			}

			std::lock_guard<std::mutex> lock(m_Mutex);

			//m_AudioClips[sound] = std::unique_ptr<Mix_Chunk>(mixChunk);
			m_AudioClips[sound] = mixChunk;

			m_Condition.notify_all();
		}
		void PlaySound(const Sound sound)
		{
			//const auto mixChunk = m_AudioClips[sound].get();
			const auto mixChunk = m_AudioClips[sound];

			const int result = Mix_PlayChannel(-1, mixChunk, sound.loops);
			if (result == -1) {
				printf("SDL_mixer could not play sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			}

			Mix_Volume(result, sound.volume);
		}
	private:
		std::map<Sound, Mix_Chunk*> m_AudioClips;
		//std::map<Sound, std::unique_ptr<Mix_Chunk>> m_AudioClips;

		std::mutex m_Mutex{};
		std::condition_variable m_Condition{};
		
		static constexpr size_t max_pending = 16;
		std::array<Sound, max_pending> m_Pending{};
		int m_NumPending{};
	};
};

real::SDLAudio::SDLAudio()
{
	m_pImpl = std::make_unique<SDLAudioImpl>();
}

void real::SDLAudio::Update()
{
	m_pImpl->Update();
}

void real::SDLAudio::Play(const Sound sound, const int volume, const int loops)
{
	m_pImpl->Play(sound, volume, loops);
}

void real::SDLAudio::Stop(const Sound sound)
{
	m_pImpl->Stop(sound);
}