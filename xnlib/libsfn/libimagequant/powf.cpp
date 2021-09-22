/*
 * Copyright (c) 2017-2018, Arm Limited.
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>

/* from powf_data.h and exp2f_data.h */
#define EXP2F_TABLE_BITS 5
#define EXP2F_POLY_ORDER 3
extern const struct exp2f_data {
	uint64_t tab[1 << EXP2F_TABLE_BITS];
	double shift_scaled;
	double poly[EXP2F_POLY_ORDER];
	double shift;
	double invln2_scaled;
	double poly_scaled[EXP2F_POLY_ORDER];
} __exp2f_data;

#define POWF_LOG2_TABLE_BITS 4
#define POWF_LOG2_POLY_ORDER 5
#if TOINT_INTRINSICS
#define POWF_SCALE_BITS EXP2F_TABLE_BITS
#else
#define POWF_SCALE_BITS 0
#endif
#define POWF_SCALE ((double)(1 << POWF_SCALE_BITS))
extern const struct powf_log2_data {
	struct {
		double invc, logc;
	} tab[1 << POWF_LOG2_TABLE_BITS];
	double poly[POWF_LOG2_POLY_ORDER];
} __powf_log2_data;

/* from internal/libm.h */
#define __math_xflowf(sign, y) (float)(eval_as_float(fp_barrierf((uint32_t)(sign) ? -((float)(y)) : (float)(y)) * (float)(y)))
#define issignalingf_inline(x) 0
#define issignaling_inline(x) 0
static inline float eval_as_float(float x)
{
        float y = x;
        return y;
}

static inline double eval_as_double(double x)
{
        double y = x;
        return y;
}

/* fp_barrier returns its input, but limits code transformations
   as if it had a side-effect (e.g. observable io) and returned
   an arbitrary value.  */

#ifndef fp_barrierf
#define fp_barrierf fp_barrierf
static inline float fp_barrierf(float x)
{
        volatile float y = x;
        return y;
}
#endif

/* from powf_data.c and exp2f_data.c */
const struct powf_log2_data __powf_log2_data = {
  .tab = {
  { 0x1.661ec79f8f3bep+0, -0x1.efec65b963019p-2 * POWF_SCALE },
  { 0x1.571ed4aaf883dp+0, -0x1.b0b6832d4fca4p-2 * POWF_SCALE },
  { 0x1.49539f0f010bp+0, -0x1.7418b0a1fb77bp-2 * POWF_SCALE },
  { 0x1.3c995b0b80385p+0, -0x1.39de91a6dcf7bp-2 * POWF_SCALE },
  { 0x1.30d190c8864a5p+0, -0x1.01d9bf3f2b631p-2 * POWF_SCALE },
  { 0x1.25e227b0b8eap+0, -0x1.97c1d1b3b7afp-3 * POWF_SCALE },
  { 0x1.1bb4a4a1a343fp+0, -0x1.2f9e393af3c9fp-3 * POWF_SCALE },
  { 0x1.12358f08ae5bap+0, -0x1.960cbbf788d5cp-4 * POWF_SCALE },
  { 0x1.0953f419900a7p+0, -0x1.a6f9db6475fcep-5 * POWF_SCALE },
  { 0x1p+0, 0x0p+0 * POWF_SCALE },
  { 0x1.e608cfd9a47acp-1, 0x1.338ca9f24f53dp-4 * POWF_SCALE },
  { 0x1.ca4b31f026aap-1, 0x1.476a9543891bap-3 * POWF_SCALE },
  { 0x1.b2036576afce6p-1, 0x1.e840b4ac4e4d2p-3 * POWF_SCALE },
  { 0x1.9c2d163a1aa2dp-1, 0x1.40645f0c6651cp-2 * POWF_SCALE },
  { 0x1.886e6037841edp-1, 0x1.88e9c2c1b9ff8p-2 * POWF_SCALE },
  { 0x1.767dcf5534862p-1, 0x1.ce0a44eb17bccp-2 * POWF_SCALE },
  },
  .poly = {
  0x1.27616c9496e0bp-2 * POWF_SCALE, -0x1.71969a075c67ap-2 * POWF_SCALE,
  0x1.ec70a6ca7baddp-2 * POWF_SCALE, -0x1.7154748bef6c8p-1 * POWF_SCALE,
  0x1.71547652ab82bp0 * POWF_SCALE,
  }
};

#define N (1 << EXP2F_TABLE_BITS)

const struct exp2f_data __exp2f_data = {
  /* tab[i] = uint(2^(i/N)) - (i << 52-BITS)
     used for computing 2^(k/N) for an int |k| < 150 N as
     double(tab[k%N] + (k << 52-BITS)) */
  .tab = {
0x3ff0000000000000, 0x3fefd9b0d3158574, 0x3fefb5586cf9890f, 0x3fef9301d0125b51,
0x3fef72b83c7d517b, 0x3fef54873168b9aa, 0x3fef387a6e756238, 0x3fef1e9df51fdee1,
0x3fef06fe0a31b715, 0x3feef1a7373aa9cb, 0x3feedea64c123422, 0x3feece086061892d,
0x3feebfdad5362a27, 0x3feeb42b569d4f82, 0x3feeab07dd485429, 0x3feea47eb03a5585,
0x3feea09e667f3bcd, 0x3fee9f75e8ec5f74, 0x3feea11473eb0187, 0x3feea589994cce13,
0x3feeace5422aa0db, 0x3feeb737b0cdc5e5, 0x3feec49182a3f090, 0x3feed503b23e255d,
0x3feee89f995ad3ad, 0x3feeff76f2fb5e47, 0x3fef199bdd85529c, 0x3fef3720dcef9069,
0x3fef5818dcfba487, 0x3fef7c97337b9b5f, 0x3fefa4afa2a490da, 0x3fefd0765b6e4540,
  },
  .shift_scaled = 0x1.8p+52 / N,
  .poly = {
  0x1.c6af84b912394p-5, 0x1.ebfce50fac4f3p-3, 0x1.62e42ff0c52d6p-1,
  },
  .shift = 0x1.8p+52,
  .invln2_scaled = 0x1.71547652b82fep+0 * N,
  .poly_scaled = {
  0x1.c6af84b912394p-5/N/N/N, 0x1.ebfce50fac4f3p-3/N/N, 0x1.62e42ff0c52d6p-1/N,
  },
};
#undef N

/*
POWF_LOG2_POLY_ORDER = 5
EXP2F_TABLE_BITS = 5

ULP error: 0.82 (~ 0.5 + relerr*2^24)
relerr: 1.27 * 2^-26 (Relative error ~= 128*Ln2*relerr_log2 + relerr_exp2)
relerr_log2: 1.83 * 2^-33 (Relative error of logx.)
relerr_exp2: 1.69 * 2^-34 (Relative error of exp2(ylogx).)
*/

#define N (1 << POWF_LOG2_TABLE_BITS)
#define T __powf_log2_data.tab
#define A __powf_log2_data.poly
#define OFF 0x3f330000

/* Subnormal input is normalized so ix has negative biased exponent.
   Output is multiplied by N (POWF_SCALE) if TOINT_INTRINICS is set.  */
static inline double log2_inline(uint32_t ix)
{
	double z, r, r2, r4, p, q, y, y0, invc, logc;
	uint32_t iz, top, tmp;
	int k, i;

	/* x = 2^k z; where z is in range [OFF,2*OFF] and exact.
	   The range is split into N subintervals.
	   The ith subinterval contains z and c is near its center.  */
	tmp = ix - OFF;
	i = (tmp >> (23 - POWF_LOG2_TABLE_BITS)) % N;
	top = tmp & 0xff800000;
	iz = ix - top;
	k = (int32_t)top >> (23 - POWF_SCALE_BITS); /* arithmetic shift */
	invc = T[i].invc;
	logc = T[i].logc;
	z = (double)((float)(iz));

	/* log2(x) = log1p(z/c-1)/ln2 + log2(c) + k */
	r = z * invc - 1;
	y0 = logc + (double)k;

	/* Pipelined polynomial evaluation to approximate log1p(r)/ln2.  */
	r2 = r * r;
	y = A[0] * r + A[1];
	p = A[2] * r + A[3];
	r4 = r2 * r2;
	q = A[4] * r + y0;
	q = p * r2 + q;
	y = y * r4 + q;
	return y;
}

#undef N
#undef T
#define N (1 << EXP2F_TABLE_BITS)
#define T __exp2f_data.tab
#define SIGN_BIAS (1 << (EXP2F_TABLE_BITS + 11))

/* The output of log2 and thus the input of exp2 is either scaled by N
   (in case of fast toint intrinsics) or not.  The unscaled xd must be
   in [-1021,1023], sign_bias sets the sign of the result.  */
static inline float exp2_inline(double xd, uint32_t sign_bias)
{
	uint64_t ki, ski, t;
	double kd, z, r, r2, y, s;

#if TOINT_INTRINSICS
#define C __exp2f_data.poly_scaled
	/* N*x = k + r with r in [-1/2, 1/2] */
	kd = roundtoint(xd); /* k */
	ki = converttoint(xd);
#else
#define C __exp2f_data.poly
#define SHIFT __exp2f_data.shift_scaled
	/* x = k/N + r with r in [-1/(2N), 1/(2N)] */
	kd = eval_as_double(xd + SHIFT);
	ki = (uint64_t)(kd);
	kd -= SHIFT; /* k/N */
#endif
	r = xd - kd;

	/* exp2(x) = 2^(k/N) * 2^r ~= s * (C0*r^3 + C1*r^2 + C2*r + 1) */
	t = T[ki % N];
	ski = ki + sign_bias;
	t += ski << (52 - EXP2F_TABLE_BITS);
	s = (double)(t);
	z = C[0] * r + C[1];
	r2 = r * r;
	y = C[2] * r + 1;
	y = z * r2 + y;
	y = y * s;
	return eval_as_float(y);
}

/* Returns 0 if not int, 1 if odd int, 2 if even int.  The argument is
   the bit representation of a non-zero finite floating-point value.  */
static inline int checkint(uint32_t iy)
{
	int e = iy >> 23 & 0xff;
	if (e < 0x7f)
		return 0;
	if (e > 0x7f + 23)
		return 2;
	if (iy & ((1 << (0x7f + 23 - e)) - 1))
		return 0;
	if (iy & (1 << (0x7f + 23 - e)))
		return 1;
	return 2;
}

static inline int zeroinfnan(uint32_t ix)
{
	return 2 * ix - 1 >= 2u * 0x7f800000 - 1;
}

float liqpowf(float x, float y)
{
	uint32_t sign_bias = 0;
	uint32_t ix, iy;

	ix = (unsigned int)(x);
	iy = (unsigned int)(y);
	if ((ix - 0x00800000 >= 0x7f800000 - 0x00800000 ||
			  zeroinfnan(iy))) {
		/* Either (x < 0x1p-126 or inf or nan) or (y is 0 or inf or nan).  */
		if ((zeroinfnan(iy))) {
			if (2 * iy == 0)
				return issignalingf_inline(x) ? x + y : 1.0f;
			if (ix == 0x3f800000)
				return issignalingf_inline(y) ? x + y : 1.0f;
			if (2 * ix > 2u * 0x7f800000 ||
			    2 * iy > 2u * 0x7f800000)
				return x + y;
			if (2 * ix == 2 * 0x3f800000)
				return 1.0f;
			if ((2 * ix < 2 * 0x3f800000) == !(iy & 0x80000000))
				return 0.0f; /* |x|<1 && y==inf or |x|>1 && y==-inf.  */
			return y * y;
		}
		if ((zeroinfnan(ix))) {
			float x2 = x * x;
			if (ix & 0x80000000 && checkint(iy) == 1)
				x2 = -x2;
			/* Without the barrier some versions of clang hoist the 1/x2 and
			   thus division by zero exception can be signaled spuriously.  */
			return iy & 0x80000000 ? fp_barrierf(1 / x2) : x2;
		}
		/* x and y are non-zero finite.  */
		if (ix & 0x80000000) {
			/* Finite x < 0.  */
			int yint = checkint(iy);
			if (yint == 0)
				return (x - x) / (x - x);
			if (yint == 1)
				sign_bias = SIGN_BIAS;
			ix &= 0x7fffffff;
		}
		if (ix < 0x00800000) {
			/* Normalize subnormal x so exponent becomes negative.  */
			ix = (unsigned int)(x * 0x1p23f);
			ix &= 0x7fffffff;
			ix -= 23 << 23;
		}
	}
	double logx = log2_inline(ix);
	double ylogx = y * logx; /* cannot overflow, y is single prec.  */
	if ((((uint64_t)(ylogx) >> 47 & 0xffff) >=
			  (uint64_t)(126.0 * POWF_SCALE) >> 47)) {
		/* |y*log(x)| >= 126.  */
		if (ylogx > 0x1.fffffffd1d571p+6 * POWF_SCALE)
			return __math_xflowf(sign_bias, 0x1p-95f);
		if (ylogx <= -150.0 * POWF_SCALE)
			return __math_xflowf(sign_bias, 0x1p-95f);
	}
	return exp2_inline(ylogx, sign_bias);
}
