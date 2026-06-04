#pragma once
// ADC for phase current sensing / ADC相电流采样

void adc_init(void);
void adc_trigger(void);
float adc_get_ia(void);  // Phase A current / A相电流
float adc_get_ib(void);  // Phase B current / B相电流
float adc_get_vdc(void); // DC bus voltage / 直流母线电压
