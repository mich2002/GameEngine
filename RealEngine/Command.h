#pragma once
#include <glm/vec2.hpp>

namespace real
{
	class GameObject;

	class Command
	{
	public:
		explicit Command(GameObject* object) { m_pGameObject = object; }
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command& operator=(const Command& rhs) = delete;
		Command(Command&& other) = delete;
		Command& operator=(Command&& rhs) = delete;

		virtual void Execute() = 0;

	protected:
		GameObject* GetObject() const { return m_pGameObject; }

	private:
		GameObject* m_pGameObject;
	};

	class MoveCommand final : public Command
	{
	public:
		explicit MoveCommand(GameObject* object, const float speed = 50);
		virtual ~MoveCommand() override = default;

		void Execute() override;
		void SetDirection(const glm::vec2& direction) { m_Direction = direction; }
		void SetSpeed(const float speed) { m_Speed = speed; }

	private:
		glm::vec2 m_Direction{};
		float m_Speed{};
	};

	class TestCommand final : public Command
	{
	public:
		explicit TestCommand(GameObject* object) : Command(object) {}

		void Execute() override;
	};
}