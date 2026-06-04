#pragma once
// PI controller for FOC current loops
// PI控制器（用于FOC电流环）

typedef struct {
    float kp, ki;       // Proportional, Integral gains / 比例、积分增益
    float integral;     // Integral accumulator / 积分累加器
    float out_min, out_max; // Output limits / 输出限幅
    float prev_error;   // Previous error / 上次误差
} pid_t;

void pid_init(pid_t* pid, float kp, float ki, float min, float max);
float pid_update(pid_t* pid, float setpoint, float measurement, float dt);
void pid_reset(pid_t* pid);
