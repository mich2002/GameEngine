#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <string>

#include <Audio.h>

struct Tags
{
	inline static const std::string player = "Player";
	inline static const std::string stair = "Stair";
	inline static const std::string floor = "Floor";
	inline static const std::string boundary = "Boundary";
	inline static const std::string hotDog = "HotDog";
	inline static const std::string egg = "Egg";
	inline static const std::string ingredient = "Ingredient";
};

struct Colors
{
	inline static const glm::vec4 red = { 255,0,0,255 };
	inline static const glm::vec4 green = { 0,255,0,255 };
	inline static const glm::vec4 blue = { 0,0,255,255 };
	inline static const glm::vec4 white = { 255,255,255,255 };
	inline static const glm::vec4 black = { 0,0,0,255 };
	inline static const glm::vec4 yellow = { 255,255,0,255 };
	inline static const glm::vec4 cyan = { 0,255,255,255 };
	inline static const glm::vec4 purple = { 255,0,255,255 };
	inline static const glm::vec4 appelblauwzeegroen = { 0,237,116,255 };
};

struct Scenes
{
	inline static const std::string level01 = "Level01";
	inline static const std::string level02 = "Level02";
	inline static const std::string level03 = "Level03";
};

struct InputMaps
{
	inline static const std::string gameplay = "Gameplay";
	inline static const std::string menu = "Menu";
};

struct Sounds
{
	using sound_id = unsigned short;
	
	inline static const real::Sound background = { 1, MIX_MAX_VOLUME, -1, "../data/audio/11_main.ogg" };
};

#endif // GAMEINFO_H