#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <Component.h>

namespace real
{
	class ColliderComponent;
}

class Ingredient final : public real::Component
{
public:
	explicit Ingredient(real::GameObject* pOwner) : Component(pOwner) {}
	virtual ~Ingredient() override = default;
	Ingredient(const Ingredient& other) = delete;
	Ingredient& operator=(const Ingredient& other) = delete;
	Ingredient(Ingredient&& other) = delete;
	Ingredient& operator=(Ingredient&& other) = delete;

	void Start() override;
	void Update() override;
	bool CanRender() const override { return false; }

	void PartIsTriggered();

	void SetIsFalling(bool isFalling) { m_IsFalling = isFalling; }
	bool GetIsFalling() const { return m_IsFalling; }

private:
	int m_AmountOfPartsTriggered{};
	std::vector<real::ColliderComponent*> m_PartPtrs;

	bool m_IsFalling{};
	const int m_FallSpeed{ 100 };

	int m_PlatformsToSkip{};
	int m_PlatformsCrossed{};
	unsigned short m_CurrentPlatform{ 0 };

	void InitCurrentPlatform();
	void ResetBurger();
	void Fall();
	void NotifyParts(bool playerOnBurger, real::ColliderComponent* pFeet) const;
};

#endif // INGREDIENT_H
