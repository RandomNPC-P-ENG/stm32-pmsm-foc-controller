/* Space Vector Modulation / 空间矢量调制 */
#include "svm.h"
#include <math.h>

svm_duty_t svm_calculate(float v_alpha, float v_beta, float v_dc) {
    svm_duty_t duty;

    // Transform to 3-phase / 反变换到三相
    float va = v_alpha;
    float vb = -0.5f * v_alpha + 0.866f * v_beta;
    float vc = -0.5f * v_alpha - 0.866f * v_beta;

    // Normalize to DC bus / 归一化到直流母线
    float v_max = fmaxf(fmaxf(va, vb), vc);
    float v_min = fminf(fminf(va, vb), vc);
    float v_offset = -(v_max + v_min) / 2.0f;  // Center-offset SVM

    duty.t_a = (va + v_offset) / v_dc + 0.5f;
    duty.t_b = (vb + v_offset) / v_dc + 0.5f;
    duty.t_c = (vc + v_offset) / v_dc + 0.5f;

    // Clamp / 限幅
    if (duty.t_a < 0) duty.t_a = 0; if (duty.t_a > 1) duty.t_a = 1;
    if (duty.t_b < 0) duty.t_b = 0; if (duty.t_b > 1) duty.t_b = 1;
    if (duty.t_c < 0) duty.t_c = 0; if (duty.t_c > 1) duty.t_c = 1;

    return duty;
}
