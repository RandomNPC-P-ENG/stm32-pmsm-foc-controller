/* STM32 PMSM FOC Controller — Main
 * STM32 PMSM FOC控制器 — 主程序
 */
#include "foc.h"
#include "pid.h"
#include "observer.h"
#include "svm.h"
#include "adc.h"
#include <math.h>

// Motor parameters / 电机参数
#define POLE_PAIRS 4
#define V_DC 24.0f

// PI controllers for d-axis and q-axis current / d轴q轴电流PI控制器
static pid_t pid_id, pid_iq;
static smo_t observer;

// Control targets / 控制目标
static float target_id = 0.0f;      // Flux current = 0 (MTPA) / 磁通电流=0（最大转矩电流比）
static float target_iq = 1.0f;      // Torque current / 转矩电流

void foc_init(void) {
    // Init PI controllers / 初始化PI控制器
    pid_init(&pid_id, 0.5f, 10.0f, -V_DC, V_DC);  // d-axis
    pid_init(&pid_iq, 0.5f, 10.0f, -V_DC, V_DC);  // q-axis

    // Init sliding mode observer / 初始化滑模观测器
    smo_init(&observer, 0.5f, 0.1f);

    // Init ADC / 初始化ADC
    adc_init();
}

// FOC control loop (called from ADC interrupt @ 10kHz)
// FOC控制循环（从ADC中断调用，10kHz频率）
void foc_control_loop(void) {
    float dt = 0.0001f;  // 100µs / 10kHz

    // 1. Sample phase currents / 采样相电流
    adc_trigger();
    float ia = adc_get_ia();
    float ib = adc_get_ib();

    // 2. Clarke transform / Clarke变换
    clarke_t clarke = clarke_transform(ia, ib, -(ia + ib));

    // 3. Get electrical angle from observer / 从观测器获取电角度
    smo_update(&observer, 0, 0, clarke.alpha, clarke.beta, dt);
    float theta_e = smo_get_angle(&observer);

    // 4. Park transform / Park变换
    park_t park = park_transform(clarke.alpha, clarke.beta, theta_e);

    // 5. PI current control / PI电流控制
    float vd = pid_update(&pid_id, target_id, park.d, dt);
    float vq = pid_update(&pid_iq, target_iq, park.q, dt);

    // 6. Inverse Park / 反Park变换
    clarke_t v_ab = inverse_park(vd, vq, theta_e);

    // 7. Space Vector Modulation / 空间矢量调制
    svm_duty_t duty = svm_calculate(v_ab.alpha, v_ab.beta, V_DC);

    // 8. Apply PWM / 输出PWM
    // pwm_set_duty(duty.t_a, duty.t_b, duty.t_c);
    (void)duty;
}

int main(void) {
    foc_init();

    while (1) {
        foc_control_loop();
        // Main loop does other tasks (UART, display, etc.)
        // 主循环处理其他任务（UART、显示等）
    }
}
