/* FOC transform implementations
 * FOC变换实现
 */
#include "foc.h"
#include <math.h>

#define SQRT3 1.732050808f
#define INV_SQRT3 0.577350269f
#define TWO_THIRDS 0.666666667f

clarke_t clarke_transform(float ia, float ib, float ic) {
    clarke_t out;
    out.alpha = ia;
    out.beta = (ia + 2.0f * ib) * INV_SQRT3;
    return out;
}

park_t park_transform(float alpha, float beta, float theta_el) {
    park_t out;
    float cos_t = cosf(theta_el);
    float sin_t = sinf(theta_el);
    out.d = alpha * cos_t + beta * sin_t;
    out.q = -alpha * sin_t + beta * cos_t;
    return out;
}

clarke_t inverse_park(float vd, float vq, float theta_el) {
    clarke_t out;
    float cos_t = cosf(theta_el);
    float sin_t = sinf(theta_el);
    out.alpha = vd * cos_t - vq * sin_t;
    out.beta = vd * sin_t + vq * cos_t;
    return out;
}

phase_t inverse_clarke(float alpha, float beta) {
    phase_t out;
    out.a = alpha;
    out.b = -0.5f * alpha + SQRT3 / 2.0f * beta;
    out.c = -0.5f * alpha - SQRT3 / 2.0f * beta;
    return out;
}

float electrical_angle(float mech_angle, int pole_pairs) {
    return mech_angle * (float)pole_pairs;
}
