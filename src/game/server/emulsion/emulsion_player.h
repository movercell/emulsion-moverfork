#include "cbase.h"
#include "predicted_viewmodel.h"
#include "player_pickup.h"
#include "emulsion_pickupcontroller.h"
#include "emulsion_gamemovement.h"
#include "igamemovement.h"

extern IGameMovement* g_pGameMovement;

class CEmulsionPlayer : public CBasePlayer {
public:
	DECLARE_CLASS(CEmulsionPlayer, CBasePlayer );
	DECLARE_NETWORKCLASS();

	CEmulsionPlayer();

	virtual void Precache();
	virtual void Spawn();
	virtual void Activate();

	virtual int		UpdateTransmitState() override { return SetTransmitState(FL_EDICT_ALWAYS); }

	void			CalcPlayerView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
	void			CreateViewModel(int index);
	virtual void	Touch(CBaseEntity* pOther) override;
	virtual void	EndTouch(CBaseEntity* pOther) override;
	void			FireBullets(const FireBulletsInfo_t& info);

	virtual void	PlayerUse();
	virtual void	PickupObject(CBaseEntity* pObject, bool bLimitMassAndSize);
	virtual	bool	IsHoldingEntity(CBaseEntity* pEnt);
	virtual float	GetHeldObjectMass(IPhysicsObject* pHeldObject);

	void			SetGravityDir(Vector axis);
	void			SetStickParent(CBaseEntity* pParent);
	CBaseEntity*	GetStickParent();

	virtual void	PreThink(void) override;
	void	Think(void);
	virtual void	PostThink(void) override;
	void			ProcessCameraRot();
	void			ProcessPowerUpdate();
	
	void			BouncePlayer(cplane_t plane);
	void			StickPlayer(PaintInfo_t info);
	void			UnStickPlayer();
	void			RotateBBox(Vector vecUp);

	virtual CBaseEntity* FindUseEntity() override;

	QAngle StickEyeAngles() { return m_vecStickEyeAngles; }
	Vector StickEyeOrigin() { return m_vecStickEyeOrigin; }

	Vector GetHalfHeight_Stick();
	Vector GetForward_Stick();
	
	Vector StickGravity() { return m_vecGravity; }

	friend class CEmulsionGameMovement;
	friend class CGrabController;
protected:
	
	CEmulsionGameMovement* pMove;

	PaintInfo_t m_tPrevPaintInfo;
	PaintInfo_t m_tCurPaintInfo;
	CBaseEntity* m_pStickParent;

	VMatrix m_mEyeRotationMat;
	VMatrix m_mGravityTransform;

	QAngle m_angInitialAngles;

	Vector m_vecCurLerpUp;
	QAngle m_vecStickEyeAngles;
	Vector m_vecStickEyeOrigin;
	//Vector m_vecEyeAxisRot;

	float m_flEyeRotation;
	bool m_bPlayUseDenySound;
	bool m_bIsTouchingStickParent;
	bool m_bIsHoldingObject;

	CGrabController* m_pGrabber;

	CNetworkHandle(CBaseEntity, m_hStickParent);
	CNetworkVar(bool, m_bPlayerPickedUpObject);
	CNetworkVar(int, m_nPaintPower);
	CNetworkVector(m_vecGravity);
	CNetworkVector(m_vecPrevUp);
	CNetworkVector(m_vecStickRight);
	CNetworkVector(m_vecSurfaceForward);
	CNetworkVector(m_vecPrevOrigin);
	CNetworkVector(m_vecUp);
};

inline CEmulsionPlayer* ToEmulsionPlayer(CBaseEntity* pEntity) {
	if (!pEntity || !pEntity->IsPlayer())
		return NULL;

#ifdef _DEBUG
	Assert(dynamic_cast<CEmulsionPlayer*>(pEntity) != 0);
#endif
	return static_cast<CEmulsionPlayer*>(pEntity);
}