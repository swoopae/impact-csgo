#pragma once

#include "vector.h"
#include "vmatrix.h"

#define pi_aprox   3.14159265358979323846264338327950288

namespace global_math {
	vec3_t vector_transform(vec3_t vector, matrix3x4_t matrix);
	double deg2rad(double deg);
	int clamp_int(int value, int min, int max);
	float clamp_float(float value, float min, float max);
	void normalize_angles(vec3_t &angles);
	void vector_angles(const vec3_t & forward, vec3_t & angles);
	vec3_t calculate_angle(const vec3_t & src, const vec3_t & dst);
	void angle_vectors(const vec3_t & angles, vec3_t * forward, vec3_t * right = nullptr, vec3_t * up = nullptr);
}