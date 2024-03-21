#include "SIMD.h"

simd_vec4_t LiLib_SetSIMD(float x, float y, float z, float w)
{
	return { _mm_set_ps(x, y, z, w) };
}

simd_mat4_t LiLib_SetSIMD(float values[4][4])
{
	return {_mm512_set_ps(values[0][0], values[1][0], values[2][0], values[3][0], 
						values[0][1], values[1][1], values[2][1], values[3][1], 
						values[0][2], values[1][2], values[2][2], values[3][2], 
						values[0][3], values[1][3], values[2][3], values[3][3])};
}

simd_vec4_t LiLib_AddSIMD(simd_vec4_t left, simd_vec4_t right)
{
	return { _mm_add_ps(left.vec, right.vec) };
}

simd_vec4_t LiLib_SubSIMD(simd_vec4_t left, simd_vec4_t right)
{
	return { _mm_sub_ps(left.vec, right.vec) };
}

simd_vec4_t LiLib_DivSIMD(simd_vec4_t left, simd_vec4_t right)
{
	return { _mm_div_ps(left.vec, right.vec) };;
}

simd_vec4_t LiLib_MulSIMD(simd_vec4_t left, simd_vec4_t right)
{
	return { _mm_mul_ps(left.vec, right.vec) };
}