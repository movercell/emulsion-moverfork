#pragma once
#include "basecombatweapon.h"

class CWeaponPaintgun : public CBaseCombatWeapon {
	DECLARE_CLASS(CWeaponPaintgun, CBaseCombatWeapon);
	DECLARE_NETWORKCLASS();
public:

	CWeaponPaintgun();

	virtual void Spawn();
	void FirePaint(bool erase = false);
	void PrimaryAttack() { FirePaint(); }
	void SecondaryAttack() { FirePaint(true); }

	virtual	int	UpdateClientData(CBasePlayer* pPlayer);

	virtual void Equip(CBaseCombatCharacter* pOwner);
	virtual void Drop(const Vector& vecVelocity);

private:

	float m_flNextFireTime = 0.0f;
	CNetworkVar(int, m_nPaintType);

};
