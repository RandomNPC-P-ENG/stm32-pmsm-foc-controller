/* PI controller implementation
 * PI控制器实现
 */
#include "pid.h"

void pid_init(pid_t* pid, float kp, float ki, float min, float max) {
    pid->kp = kp;
    pid->ki = ki;
    pid->integral = 0;
    pid->out_min = min;
    pid->out_max = max;
    pid->prev_error = 0;
}

float pid_update(pid_t* pid, float setpoint, float measurement, float dt) {
    float error = setpoint - measurement;

    // Proportional / 比例
    float p_term = pid->kp * error;

    // Integral with anti-windup / 积分（带抗饱和）
    pid->integral += error * dt;
    float i_term = pid->ki * pid->integral;

    // Output with saturation / 输出限幅
    float output = p_term + i_term;
    if (output > pid->out_max) {
        output = pid->out_max;
        pid->integral -= error * dt;  // Anti-windup
    } else if (output < pid->out_min) {
        output = pid->out_min;
        pid->integral -= error * dt;
    }

    pid->prev_error = error;
    return output;
}

void pid_reset(pid_t* pid) {
    pid->integral = 0;
    pid->prev_error = 0;
}
