#ifndef DAMAGECOMMAND_H
#define DAMAGECOMMAND_H

#include <Command.h>

class DamageCommand final : public real::Command
{
public:
	explicit DamageCommand(real::GameObject* object, const int damage = 1);
	virtual ~DamageCommand() override = default;

	void Execute() override;

	void SetDamageAmount(const int amount) { m_Damage = amount; }
private:
	int m_Damage;
};

#endif // DAMAGECOMMAND_H