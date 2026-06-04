#pragma space
// Space Vector Modulation / 空间矢量调制

typedef struct {
    float t_a, t_b, t_c;  // Phase duty cycles / 各相占空比
} svm_duty_t;

svm_duty_t svm_calculate(float v_alpha, float v_beta, float v_dc);
