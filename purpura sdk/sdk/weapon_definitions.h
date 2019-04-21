#pragma once

// idk if 100% accurate, todo: reverse urself and find out if outdated or nah
enum class item_definition_index : short {
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_MP5 = 23,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516
};

enum class cs_weapon_type : int {
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

// stolen from antario and too tired to rename all this bullshit to snake case

class weapon_info_t {
public:
	void *pVTable;                       // 0x0000
	char *consoleName;                   // 0x0004
	char pad_0008[12];                   // 0x0008
	int iMaxClip1;                       // 0x0014
	int iMaxClip2;                       // 0x0018
	int iDefaultClip1;                   // 0x001C
	int iDefaultClip2;                   // 0x0020
	char pad_0024[8];                    // 0x0024
	char *szWorldModel;                  // 0x002C
	char *szViewModel;                   // 0x0030
	char *szDroppedMode;                 // 0x0034
	char pad_0038[4];                    // 0x0038
	char *szShotSound;                   // 0x003C
	char pad_0040[56];                   // 0x0040
	char *szEmptySound;                  // 0x0078
	char pad_007C[4];                    // 0x007C
	char *szBulletType;                  // 0x0080
	char pad_0084[4];                    // 0x0084
	char *szHudName;                     // 0x0088
	char *szWeaponName;                  // 0x008C
	char pad_0090[56];                   // 0x0090
	cs_weapon_type iWeaponType;          // 0x00C8
	char pad_00CC[4];                    // 0x00CC
	int iWeaponPrice;                    // 0x00D0
	int iKillAward;                      // 0x00D4
	char *szAnimationPrefix;             // 0x00D8
	float flCycleTime;                   // 0x00DC
	float flCycleTimeAlt;                // 0x00E0
	float flTimeToIdle;                  // 0x00E4
	float flIdleInterval;                // 0x00E8
	bool bFullAuto;                      // 0x00EC
	char pad_00ED[3];                    // 0x00ED
	int iDamage;                         // 0x00F0
	float flArmorRatio;                  // 0x00F4
	int iBullets;                        // 0x00F8
	float flPenetration;                 // 0x00FC
	float flFlinchVelocityModifierLarge; // 0x0100
	float flFlinchVelocityModifierSmall; // 0x0104
	float flRange;                       // 0x0108
	float flRangeModifier;               // 0x010C
	float flThrowVelocity;               // 0x0110
	char pad_0114[12];                   // 0x0114
	bool bHasSilencer;                   // 0x0120
	char pad_0121[3];                    // 0x0121
	char *pSilencerModel;                // 0x0124
	int iCrosshairMinDistance;           // 0x0128
	int iCrosshairDeltaDistance;         // 0x012C
	float flMaxPlayerSpeed;              // 0x0130
	float flMaxPlayerSpeedAlt;           // 0x0134
	float flMaxPlayerSpeedMod;           // 0x0138
	float flSpread;                      // 0x013C
	float flSpreadAlt;                   // 0x0140
	float flInaccuracyCrouch;            // 0x0144
	float flInaccuracyCrouchAlt;         // 0x0148
	float flInaccuracyStand;             // 0x014C
	float flInaccuracyStandAlt;          // 0x0150
	float flInaccuracyJumpInitial;       // 0x0154
	float flInaccuracyJump;              // 0x0158
	float flInaccuracyJumpAlt;           // 0x015C
	float flInaccuracyLand;              // 0x0160
	float flInaccuracyLandAlt;           // 0x0164
	float flInaccuracyLadder;            // 0x0168
	float flInaccuracyLadderAlt;         // 0x016C
	float flInaccuracyFire;              // 0x0170
	float flInaccuracyFireAlt;           // 0x0174
	float flInaccuracyMove;              // 0x0178
	float flInaccuracyMoveAlt;           // 0x017C
	float flInaccuracyReload;            // 0x0180
	int iRecoilSeed;                     // 0x0184
	float flRecoilAngle;                 // 0x0188
	float flRecoilAngleAlt;              // 0x018C
	float flRecoilAngleVariance;         // 0x0190
	float flRecoilAngleVarianceAlt;      // 0x0194
	float flRecoilMagnitude;             // 0x0198
	float flRecoilMagnitudeAlt;          // 0x019C
	float flRecoilMagnitudeVariance;     // 0x01A0
	float flRecoilMagnitudeVarianceAlt;  // 0x01A4
	float flRecoveryTimeCrouch;          // 0x01A8
	float flRecoveryTimeStand;           // 0x01AC
	float flRecoveryTimeCrouchFinal;     // 0x01B0
	float flRecoveryTimeStandFinal;      // 0x01B4
	char pad_01B8[40];                   // 0x01B8
	char *szWeaponClass;                 // 0x01E0
	char pad_01E4[8];                    // 0x01E4
	char *szEjectBrassEffect;            // 0x01EC
	char *szTracerEffect;                // 0x01F0
	int iTracerFrequency;                // 0x01F4
	int iTracerFrequencyAlt;             // 0x01F8
	char *szMuzzleFlashEffect_1stPerson; // 0x01FC
	char pad_0200[4];                    // 0x0200
	char *szMuzzleFlashEffect_3rdPerson; // 0x0204
	char pad_0208[4];                    // 0x0208
	char *szMuzzleSmokeEffect;           // 0x020C
	float flHeatPerShot;                 // 0x0210
	char *szZoomInSound;                 // 0x0214
	char *szZoomOutSound;                // 0x0218
	float flInaccuracyPitchShift;        // 0x021C
	float flInaccuracySoundThreshold;    // 0x0220
	float flBotAudibleRange;             // 0x0224
	char pad_0228[12];                   // 0x0228
	bool bHasBurstMode;                  // 0x0234
	bool bIsRevolver;                    // 0x0235
};                                     // Size: 0x0236

class c_weapon_system {
	virtual void pad0x000();
	virtual void pad0x001();
public:
	virtual weapon_info_t* get_weapon_data(item_definition_index idx);
};