#pragma once

#include "bsp_flags.h"

#define CHAR_TEX_ANTLION		'A'
#define CHAR_TEX_BLOODYFLESH	'B'
#define	CHAR_TEX_CONCRETE		'C'
#define CHAR_TEX_DIRT			'D'
#define CHAR_TEX_EGGSHELL		'E' // egg
#define CHAR_TEX_FLESH			'F'
#define CHAR_TEX_GRATE			'G'
#define CHAR_TEX_ALIENFLESH		'H'
#define CHAR_TEX_CLIP			'I'

//#define CHAR_TEX_UNUSED		'J'
#define CHAR_TEX_SNOW			'K'
#define CHAR_TEX_PLASTIC		'L'
#define CHAR_TEX_METAL			'M'
#define CHAR_TEX_SAND			'N'
#define CHAR_TEX_FOLIAGE		'O'
#define CHAR_TEX_COMPUTER		'P'

//#define CHAR_TEX_UNUSED		'Q'
#define CHAR_TEX_REFLECTIVE		'R'
#define CHAR_TEX_SLOSH			'S'
#define CHAR_TEX_TILE			'T'
#define CHAR_TEX_CARDBOARD		'U'
#define CHAR_TEX_VENT			'V'
#define CHAR_TEX_WOOD			'W'

//#define CHAR_TEX_UNUSED		'X' ///< do not use - "fake" materials use this (ladders, wading, clips, etc)
#define CHAR_TEX_GLASS			'Y'
#define CHAR_TEX_WARPSHIELD		'Z' ///< wierd-looking jello effect for advisor shield.

#define CHAR_TEX_STEAM_PIPE		11

struct c_ray
{
	vec3_t m_Start; // starting point, centered within the extents
	vec3_t m_Delta; // direction + length of the ray
	vec3_t m_StartOffset; // Add this to m_Start to get the actual ray start
	vec3_t m_Extents; // Describes an axis aligned box extruded along a ray
	const matrix3x4_t* m_pWorldAxisTransform;

	//const matrix3x4_t *m_pWorldAxisTransform;
	bool m_IsRay; // are the extents zero?
	bool m_IsSwept; // is delta != 0?

	c_ray(vec3_t _start, vec3_t _end)
	{
		init(_start, _end);
	}

	c_ray(vec3_t _start, vec3_t _end, vec3_t _mins, vec3_t _maxs)
	{
		init(_start, _end, _mins, _maxs);
	}

	void init(const vec3_t& vecStart, const vec3_t& vecEnd)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;
		m_IsRay = true;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = vecStart;
	}

	void init(vec3_t& vecStart, vec3_t& vecEnd, vec3_t min, vec3_t max)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.x = (max.x - min.x);
		m_Extents.y = (max.y - min.y);
		m_Extents.z = (max.z - min.z);
		m_IsRay = false;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = vecStart + ((max + min) * 0.5f);
	}

private:
};

struct c_surface_t
{
	const char* name;
	short surface_props;
	unsigned short flags;
};

struct c_plane_t
{
	vec3_t normal;
	float dist;
	byte type;
	byte signbits;
	byte pad[2];
};

struct c_trace
{
	bool did_hit_world() const
	{
		return m_pEnt && m_pEnt->ent_index() == 0;
	}

	bool did_hit_non_world_ent() const
	{
		return m_pEnt != NULL && !did_hit_world();
	}

	bool did_hit() const
	{
		return flFraction < 1.f;
	}

	vec3_t start;
	vec3_t end;
	c_plane_t plane;
	float flFraction;
	int contents;
	WORD dispFlags;
	bool allsolid;
	bool startSolid;
	float fractionLeftSolid;
	c_surface_t surface;
	int hitGroup;
	short physicsBone;
	c_base_entity* m_pEnt;
	int hitbox;
};

enum trace_type_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY, // NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY, // NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS, // NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

class i_trace_filter
{
public:
	virtual bool should_hit_entity(void* pEntity, int contentsMask) = 0;
	virtual trace_type_t get_trace_entity() const = 0;
};

class c_trace_filter : public i_trace_filter
{
public:

	explicit c_trace_filter(c_base_entity* entity, trace_type_t tracetype = TRACE_EVERYTHING)
	{
		p_skip_1 = entity;
	}

	bool should_hit_entity(void* pEntityHandle, int contentsMask)
	{
		return (pEntityHandle != p_skip_1);
	}

	trace_type_t get_trace_entity() const
	{
		return TRACE_EVERYTHING;
	}

	void* p_skip_1;
};

class c_trace_filter_one_entity : public i_trace_filter
{
public:

	explicit c_trace_filter_one_entity(c_base_entity* entity, trace_type_t tracetype = TRACE_EVERYTHING)
	{
		p_ent = entity;
	}

	bool should_hit_entity(void* pEntityHandle, int contentsMask)
	{
		return (pEntityHandle == p_ent);
	}

	trace_type_t get_trace_entity() const
	{
		return TRACE_EVERYTHING;
	}

	void* p_ent;
};

class c_trace_filter_one_entity_2 : public i_trace_filter
{
public:

	explicit c_trace_filter_one_entity_2(c_base_entity* entity, trace_type_t tracetype = TRACE_EVERYTHING)
	{
		p_ent = entity;
	}

	bool should_hit_entity(void* pEntityHandle, int contentsMask)
	{
		return (pEntityHandle == p_ent);
	}

	trace_type_t get_trace_entity() const
	{
		return TRACE_ENTITIES_ONLY;
	}

	void* p_ent;
};

class c_trace_filter_skip_two_entities : public i_trace_filter
{
public:
	c_trace_filter_skip_two_entities(void* pPassEnt1, void* pPassEnt2)
	{
		passentity1 = pPassEnt1;
		passentity2 = pPassEnt2;
	}

	virtual bool should_hit_entity(void* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == passentity1 || pEntityHandle == passentity2);
	}

	virtual trace_type_t get_trace_entity() const
	{
		return TRACE_EVERYTHING;
	}

	void* passentity1;
	void* passentity2;
};

class c_trace_entity : public i_trace_filter
{
public:

	explicit c_trace_entity(c_base_entity* entity, trace_type_t tracetype = TRACE_EVERYTHING)
	{
		pSkip1 = entity;
	}

	bool should_hit_entity(void* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip1);
	}

	trace_type_t get_trace_entity() const
	{
		return TRACE_ENTITIES_ONLY;
	}

	void* pSkip1;
};

class c_trace_world_only : public i_trace_filter
{
public:

	explicit c_trace_world_only(c_base_entity* entity = nullptr, trace_type_t tracetype = TRACE_EVERYTHING)
	{
		pSkip1 = entity;
	}

	bool should_hit_entity(void* pEntityHandle, int contentsMask)
	{
		return false;
	}

	trace_type_t get_trace_entity() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip1;
};

class i_engine_trace
{
public:

	// Returns the contents mask + entity at a particular world-space position
	virtual int		get_point_contents(const vec3_t &vecAbsPosition, int contentsMask = mask_all, i_handle_entity** ppEntity = NULL) = 0;

	// Returns the contents mask of the world only @ the world-space position (static props are ignored)
	virtual int		get_point_contents_world_only(const vec3_t &vecAbsPosition, int contentsMask = mask_all) = 0;

	// Get the point contents, but only test the specific entity. This works
	// on static props and brush models.
	//
	// If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
	// bFailed to true if bFailed is non-null.
	virtual int		get_point_contents_collideable(collideable_t *pCollide, const vec3_t &vecAbsPosition) = 0;

	// Traces a ray against a particular entity
	virtual void	clip_ray_to_entity(const c_ray &ray, unsigned int fMask, i_handle_entity *pEnt, c_trace *pTrace) = 0;

	// Traces a ray against a particular entity
	virtual void	clip_ray_to_collideable(const c_ray &ray, unsigned int fMask, collideable_t *pCollide, c_trace *pTrace) = 0;

	// A version that simply accepts a ray (can work as a traceline or tracehull)
	virtual void	trace_ray(const c_ray &ray, unsigned int fMask, i_trace_filter *pTraceFilter, c_trace *pTrace) = 0;
};