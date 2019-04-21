#include "math.h"

vec3_t global_math::vector_transform(vec3_t vector, matrix3x4_t matrix) {
	return vec3_t(vector.Dot2(matrix[0]) + matrix[0][3], vector.Dot2(matrix[1]) + matrix[1][3], vector.Dot2(matrix[2]) + matrix[2][3]);
}

double global_math::deg2rad(double deg) {
	return deg * pi_aprox / 180.;
}

int global_math::clamp_int(int value, int min, int max) {
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}

float global_math::clamp_float(float value, float min, float max) {
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}

void global_math::normalize_angles(vec3_t& angles) {
	for (auto i = 0; i < 3; i++) {
		while (angles[i] < -180.0f) angles[i] += 360.0f;
		while (angles[i] > 180.0f) angles[i] -= 360.0f;
	}
}

void global_math::vector_angles(const vec3_t& forward, vec3_t& angles) {
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0) {
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else {
		yaw = (atan2(forward[1], forward[0]) * 180 / pi_aprox);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / pi_aprox);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

void inline sin_cos(float radians, float* sine, float* cosine) {
	*sine = sin(radians);
	*cosine = cos(radians);
}

vec3_t global_math::calculate_angle(const vec3_t& src, const vec3_t& dst) {
	vec3_t ret;
	global_math::vector_angles(dst - src, ret);
	return ret;
}

void global_math::angle_vectors(const vec3_t& angles, vec3_t* forward, vec3_t* right, vec3_t* up) {
	float sr, sp, sy, cr, cp, cy;

	sin_cos(deg2rad(angles[1]), &sy, &cy);
	sin_cos(deg2rad(angles[0]), &sp, &cp);
	sin_cos(deg2rad(angles[2]), &sr, &cr);

	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right) {
		right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right->y = (-1 * sr * sp * sy + -1 * cr * cy);
		right->z = -1 * sr * cp;
	}

	if (up) {
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}