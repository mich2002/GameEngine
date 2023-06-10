#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include <glm/vec2.hpp>

#include <Component.h>
#include <Subject.h>

#include "BaseEnemy.h"

class HealthComponent final : public real::Component
{
public:
	explicit HealthComponent(real::GameObject* pOwner, int lives = 0);
	virtual ~HealthComponent() override = default;
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;

	void Update() override;

	bool CanRender() const override { return false; }

	void SetLives(const int lives) { m_Lives = lives; }
	int GetLives() const { return m_Lives; }

	void SetSpawnPoint(const glm::vec2& spawnPoint) { m_SpawnPoint = spawnPoint; }

	void Damage();

	real::Subject<> playerDied;
private:
	int m_CurrentHealth{};
	int m_Lives{};
	glm::vec2 m_SpawnPoint{};

	bool m_PlayerDied{};
	float m_AccuTime{};
	float m_TimeToRespawn{ 4 };
	bool m_SpriteChanged{};

	std::vector<BaseEnemy*> m_EnemyPtrs;

	void Kill();
	void Respawn() const;
};

#endif // HEALTHCOMPONENT_H