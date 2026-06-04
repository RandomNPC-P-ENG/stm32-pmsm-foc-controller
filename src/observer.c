/* Sliding Mode Observer implementation
 * 滑模观测器实现
 */
#include "observer.h"
#include <math.h>

void smo_init(smo_t* obs, float k_slide, float k_filter) {
    obs->alpha_est = 0;
    obs->beta_est = 0;
    obs->z_alpha = 0;
    obs->z_beta = 0;
    obs->k_slide = k_slide;
    obs->k_filter = k_filter;
    obs->theta_est = 0;
}

void smo_update(smo_t* obs, float v_alpha, float v_beta,
                float i_alpha, float i_beta, float dt) {
    // Motor parameters (simplified) / 电机参数（简化）
    float Rs = 0.5f;   // Stator resistance / 定子电阻
    float Ls = 0.005f; // Stator inductance / 定子电感

    // Current observer / 电流观测器
    float di_alpha = (v_alpha - Rs * i_alpha - obs->z_alpha) / Ls;
    float di_beta = (v_beta - Rs * i_beta - obs->z_beta) / Ls;
    float i_alpha_est = i_alpha + di_alpha * dt;
    float i_beta_est = i_beta + di_beta * dt;

    // Current error / 电流误差
    float err_alpha = i_alpha - i_alpha_est;
    float err_beta = i_beta - i_beta_est;

    // Sliding function / 滑模函数
    obs->z_alpha = obs->k_slide * (err_alpha > 0 ? 1.0f : -1.0f);
    obs->z_beta = obs->k_slide * (err_beta > 0 ? 1.0f : -1.0f);

    // Low-pass filter to extract back-EMF / 低通滤波提取反电动势
    obs->alpha_est += obs->k_filter * (obs->z_alpha - obs->alpha_est);
    obs->beta_est += obs->k_filter * (obs->z_beta - obs->beta_est);

    // Estimated angle / 估计角度
    obs->theta_est = atan2f(-obs->alpha_est, obs->beta_est);
}

float smo_get_angle(smo_t* obs) {
    return obs->theta_est;
}

float smo_get_speed(smo_t* obs) {
    // Simplified speed estimation / 简化速度估计
    return sqrtf(obs->alpha_est * obs->alpha_est + obs->beta_est * obs->beta_est);
}
