#pragma once
#include <glm/glm.hpp>

#include "Component.h"

namespace dae
{
	class GameObject;
	class TransformComponent final : public Component
	{
	public:
		TransformComponent() = default;
		explicit TransformComponent(const std::shared_ptr<GameObject>& pOwner) : Component(pOwner) {}
		~TransformComponent() override = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent& operator=(const TransformComponent& rhs) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(TransformComponent&& rhs) = delete;

		void Update() override;
 
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z = 0);

		bool CanRender() const override { return false; }

	private:
		glm::vec3 m_position{};
	};
}