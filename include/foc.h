#pragma once
// FOC algorithm — Clarke, Park, Inverse transforms
// FOC算法 — Clarke变换、Park变换、反变换

#include <math.h>

typedef struct {
    float alpha, beta;   // Clarke output
} clarke_t;

typedef struct {
    float d, q;          // Park output (d=flux, q=torque)
} park_t;

typedef struct {
    float a, b, c;       // 3-phase output
} phase_t;

// Clarke transform: Ia,Ib,Ic → Iα,Iβ
clarke_t clarke_transform(float ia, float ib, float ic);

// Park transform: Iα,Iβ → Id,Iq
park_t park_transform(float alpha, float beta, float theta_el);

// Inverse Park: Vd,Vq → Vα,Vβ
clarke_t inverse_park(float vd, float vq, float theta_el);

// Inverse Clarke + SVM: Vα,Vβ → duty cycles
phase_t inverse_clarke(float alpha, float beta);

// Electrical angle from rotor position
float electrical_angle(float mech_angle, int pole_pairs);
