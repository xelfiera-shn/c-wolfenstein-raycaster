#ifndef WR_MATH_H
#define WR_MATH_H

#define WR_PI 3.1415927f

#define WR_MIN(a, b) ((a) < (b) ? (a) : (b))
#define WR_MAX(a, b) ((a) > (b) ? (a) : (b))
#define WR_CLAMP(val, lo, hi) (((val) < (lo)) ? (lo) : ((val) > (hi)) ? (hi) : (val))
#define WR_SIGN(val) ((val) >= 0 ? 1 : -1)

#endif // WR_MATH_H
