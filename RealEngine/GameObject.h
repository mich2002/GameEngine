#pragma once
#include <memory>
#include <vector>
#include <stdexcept>

#include "Component.h"
#include "Observer.h"

namespace real
{
	class TransformComponent;
	class Scene;
	class Texture2D;
	class Component;
	class Observer;

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject() = default;
		GameObject(Scene* pScene) : m_pScene(pScene) {}
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject& operator=(const GameObject& rhs) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(GameObject&& rhs) = delete;

		GameObject* CreateGameObject();

		void Init();

		void Update();
		void Render() const;

		//Component Logic
		template <class T>
		std::shared_ptr<T> AddComponent();
		template <class T>
		std::shared_ptr<T> GetComponent();
		template <class T>
		void RemoveComponent();
		template <class T>
		bool HasComponent() const;

		//Child-Parent Logic
		void SetParent(GameObject* pParent, const bool keepWorldPosition);
		GameObject* GetParent() const { return m_pParent; }

		size_t GetChildCount() const { return m_ChildrenPtrs.size(); }
		GameObject* GetChildAt(const unsigned int idx) const { return m_ChildrenPtrs[idx].get(); }
		std::vector<GameObject*> GetChildren() const;

		//Observer Logic
		template <class T>
		void AddObserver();
		template <class T>
		void RemoveObserver();
		template <class T>
		bool HasObserver() const;
		void NotifyObservers(Observer::GameEvent event);

	private:
		Scene* m_pScene{ nullptr };
		TransformComponent* m_pTransform{ nullptr };

		std::vector<std::shared_ptr<Component>> m_ComponentPtrs{};

		GameObject* m_pParent{ nullptr };
		std::vector<std::unique_ptr<GameObject>> m_ChildrenPtrs{};

		std::vector<std::unique_ptr<Observer>> m_ObserverPtrs{};
	};

#pragma region ComponentLogic
	template <class T>
	std::shared_ptr<T> GameObject::AddComponent()
	{
		if (HasComponent<T>())
			throw std::runtime_error("Error: Could not add component to GameObject - a component of this type is already attached. Please remove the existing component before adding another.");

		std::shared_ptr<T>pComponent = std::make_shared<T>(this);

		m_ComponentPtrs.emplace_back(pComponent);

		return pComponent;
	}

	template <class T>
	std::shared_ptr<T> GameObject::GetComponent()
	{
		if (!HasComponent<T>())
			throw std::runtime_error("Error: Could not find component on GameObject - no component of this type is attached. Please ensure the GameObject has a component of the correct type attached.");

		for (const auto& pComponent : m_ComponentPtrs)
		{
			std::shared_ptr<T> otherComponent = std::dynamic_pointer_cast<T>(pComponent);
			if (otherComponent != nullptr)
				return otherComponent;
		}
		return nullptr;
	}

	template <class T>
	void GameObject::RemoveComponent()
	{
		if (HasComponent<T>() == false)
			throw std::runtime_error("Error: Could not find component on GameObject - no component of this type is attached. Please ensure the GameObject has a component of the correct type attached.");

		for (auto it = m_ComponentPtrs.begin(); it != m_ComponentPtrs.end(); ++it)
		{
			std::shared_ptr<T> otherComponent = std::dynamic_pointer_cast<T>(*it);
			if (otherComponent != nullptr)
			{
				it = m_ComponentPtrs.erase(it);
				break;
			}
		}
	}

	template <class T>
	bool GameObject::HasComponent() const
	{
		for (const auto& pComponent : m_ComponentPtrs)
		{
			if (std::dynamic_pointer_cast<T>(pComponent) != nullptr)
				return true;
		}

		return false;
	}
#pragma endregion
#pragma region ObserverLogic
	template <class T>
	void GameObject::AddObserver()
	{
		if (HasObserver<T>())
			throw std::runtime_error("Error: Could not add observer to GameObject - a observer of this type is already attached. Please remove the existing observer before adding another.");

		m_ObserverPtrs.emplace_back(std::make_unique<T>());
	}

	template <class T>
	void GameObject::RemoveObserver()
	{
		if (HasObserver<T>() == false)
			throw std::runtime_error("Error: Could not find observer on GameObject - no observer of this type is attached. Please ensure the GameObject has a observer of the correct type attached.");

		for (auto it = m_ObserverPtrs.begin(); it != m_ObserverPtrs.end(); ++it)
		{
			if (T* otherObserver = dynamic_cast<T*>((*it).get()))
			{
				it = m_ObserverPtrs.erase(it);
				break;
			}
		}
	}

	template <class T>
	bool GameObject::HasObserver() const
	{
		for (const auto& pObserver : m_ObserverPtrs)
		{
			if (T* pOtherObserver = dynamic_cast<T*>(pObserver.get()))
				return true;
		}

		return false;
	}
#pragma endregion
}