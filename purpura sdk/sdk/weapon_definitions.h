#pragma once

enum class item_definition_index : short {
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALIL = 13,
	WEAPON_M249,
	WEAPON_M4A4 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_ZEUS,
	WEAPON_P2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG553,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INC,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1S,
	WEAPON_USPS,
	WEAPON_CZ75 = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_SNOWBALL,
	WEAPON_BUMPMINE,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035
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
