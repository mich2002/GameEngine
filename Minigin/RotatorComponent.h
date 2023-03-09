#pragma once
#include "Component.h"

namespace dae
{
	class RotatorComponent final : public Component
	{
	public:
		explicit RotatorComponent(const std::weak_ptr<GameObject>& pOwner) : Component(pOwner) {}
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent operator=(const RotatorComponent& rhs) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent operator=(RotatorComponent&& rhs) = delete;

		void Update() override;

		void SetPivot(const glm::vec3& pivot) { m_Pivot = pivot; }
		void SetSpeed(const float speed) { m_Speed = speed; }

		bool CanRender() const override { return false; }

	private:
		glm::vec3 m_Pivot{};
		float m_Speed{ 50 };
		float m_Angle{};
	};
}