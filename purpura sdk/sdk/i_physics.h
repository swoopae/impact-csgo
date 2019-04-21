#pragma once

struct surfacephysicsparams_t {
	float    friction;
	float    elasticity; // collision elasticity - used to compute coefficient of restitution
	float    density;    // physical density (in kg / m^3)
	float    thickness;    // material thickness if not solid (sheet materials) in inches
	float    dampening;
};

struct surfaceaudioparams_t {
	float    reflectivity;             // like elasticity, but how much sound should be reflected by this surface
	float    hardness_factor;           // like elasticity, but only affects impact sound choices
	float    roughness_factor;          // like friction, but only affects scrape sound choices
	float    rough_threshold;           // surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
	float    hard_threshold;            // surface hardness > this causes "hard" impacts, < this causes "soft" impacts
	float    hard_velocity_threshold;    // collision velocity > this causes "hard" impacts, < this causes "soft" impacts
	float    high_pitch_occlusion;       // a value betweeen 0 and 100 where 0 is not occluded at all and 100 is silent (except for any additional reflected sound)
	float    mid_pitch_occlusion;
	float    low_pitch_occlusion;
};

// idk what all this shit is
struct surfacesoundnames_t {
	unsigned short    walkStepLeft;
	unsigned short    walkStepRight;
	unsigned short	  runStepLeft;
	unsigned short	  runStepRight;
	unsigned short    impactSoft;
	unsigned short    impactHard;
	unsigned short    scrapeSmooth;
	unsigned short    scrapeRough;
	unsigned short    bulletImpact;
	unsigned short    rolling;
	unsigned short    breakSound;
	unsigned short    strainSound;
};

struct surfacegameprops_t {
public:
	float max_speed_factor;
	float jump_factor;
	float fl_penetration_modifier;
	float fl_damage_modifier;
	unsigned short material;
	byte climbable;
	char pad00[0x4];
};

struct surfacedata_t {
	surfacephysicsparams_t    physics;
	surfaceaudioparams_t	  audio;
	surfacesoundnames_t       sounds;
	surfacegameprops_t        game;
};

class i_physics_surface_props {
public:
	virtual ~i_physics_surface_props(void) { }
	virtual int             parse_surface_data(const char *pFilename, const char *pTextfile) = 0;
	virtual int             surface_prop_count(void) const = 0;
	virtual int             get_surface_index(const char *pSurfacePropName) const = 0;
	virtual void            get_phys_propreties(int surfaceDataIndex, float *density, float *thickness, float *friction, float *elasticity) const = 0;
	virtual surfacedata_t*  surface_data(int surfaceDataIndex) = 0;
	virtual const char*     get_string(unsigned short stringTableIndex) const = 0;
	virtual const char*     prop_name(int surfaceDataIndex) const = 0;
	virtual void            set_world_material_index_table(int *pMapArray, int mapSize) = 0;
	virtual void            phys_parameters(int surfaceDataIndex, surfacephysicsparams_t *pParamsOut) const = 0;
};