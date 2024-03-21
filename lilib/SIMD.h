#ifndef LILIB_SIMD_H
#define LILIB_SIMD_H
#include <immintrin.h>

union simd_vec4_t {
	__m128 vec;
	struct {
		float v[4];
	};
	struct {
		float x, y, z, w;
	};
};

union simd_mat4_t {
	__m512 mat;
	struct {
		float whole[16];
	};
	struct {
		float values[4][4];
	};
};

// SIMD setting
simd_vec4_t LiLib_SetSIMD(float x, float y, float z, float w);
simd_mat4_t LiLib_SetSIMD(float values[4][4]);

// SIMD ops
simd_vec4_t LiLib_AddSIMD(simd_vec4_t left, simd_vec4_t right);
simd_vec4_t LiLib_SubSIMD(simd_vec4_t left, simd_vec4_t right);
simd_vec4_t LiLib_DivSIMD(simd_vec4_t left, simd_vec4_t right);
simd_vec4_t LiLib_MulSIMD(simd_vec4_t left, simd_vec4_t right);

#endif