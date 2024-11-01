#include "miniRT.h"

t_mat4s	lag_mat4s_transpose_ret(const t_mat4s m)
{
	t_mat4s			ret0;
	const __m128	tmp0 = _mm_unpacklo_ps(m.r1.simd, m.r2.simd);
	const __m128	tmp1 = _mm_unpacklo_ps(m.r3.simd, m.r4.simd);
	const __m128	tmp2 = _mm_unpackhi_ps(m.r1.simd, m.r2.simd);
	const __m128	tmp3 = _mm_unpackhi_ps(m.r3.simd, m.r4.simd);

	ret0.r1.simd = _mm_movelh_ps(tmp0, tmp1);
	ret0.r2.simd = _mm_movehl_ps(tmp1, tmp0);
	ret0.r3.simd = _mm_movelh_ps(tmp2, tmp3);
	ret0.r4.simd = _mm_movehl_ps(tmp3, tmp2);
	return (ret0);
}