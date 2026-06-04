#pragma once
// Sliding Mode Observer for sensorless FOC
// 滑模观测器（用于无传感器FOC）

typedef struct {
    float alpha_est, beta_est;  // Estimated back-EMF / 估计反电动势
    float z_alpha, z_beta;      // Switching function / 切换函数
    float k_slide;              // Sliding gain / 滑模增益
    float k_filter;             // Low-pass filter gain / 低通滤波增益
    float theta_est;            // Estimated angle / 估计角度
} smo_t;

void smo_init(smo_t* obs, float k_slide, float k_filter);
void smo_update(smo_t* obs, float v_alpha, float v_beta, float i_alpha, float i_beta, float dt);
float smo_get_angle(smo_t* obs);
float smo_get_speed(smo_t* obs);
