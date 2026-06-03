# STM32 PMSM FOC Controller 🔧

Field-Oriented Control (FOC) implementation for Permanent Magnet Synchronous Motors on STM32.

## Features
- Sensorless FOC using sliding mode observer
- Clarke & Park transforms
- PI current controllers (d-axis, q-axis)
- Space Vector Modulation (SVM)
- Speed control with ramp profile
- Over-current protection via ADC
- UART debug interface
- Configurable motor parameters

## Algorithm Flow
```
Ia, Ib, Ic  ──▶  Clarke  ──▶  Park  ──▶  PI Controller  ──▶  Inverse Park
                    (α,β)       (d,q)      (Vd, Vq)           (Vα, Vβ)
                                                                      │
                                                                      ▼
                              SVPWM  ──▶  3-Phase Inverter  ──▶  PMSM
                              (6 PWM)
```

## Hardware
- STM32F4xx (e.g., STM32F446RE)
- 3-phase inverter board (IR2136 / discrete MOSFETs)
- Current sensors (hall effect or shunt resistors)
- PMSM motor (BLDC with sinusoidal BEMF)

## Tech Stack
- **MCU**: STM32F446RE (ARM Cortex-M4, 168MHz, FPU)
- **Language**: C++17 (bare metal, no HAL)
- **Timer**: TIM1 (center-aligned PWM, 20kHz)
- **ADC**: Injected channels for phase current sampling
- **Observer**: Sliding mode for sensorless position estimation

## Build
```bash
# ARM GCC
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../arm-gcc.cmake ..
make -j4
# Flash via ST-Link
st-flash write firmware.bin 0x08000000
```

## Skills Demonstrated
- Advanced C++ (templates, constexpr, RAII)
- Motor control theory (FOC, SVM, observers)
- Power electronics (3-phase inverter)
- ARM Cortex-M4 (registers, interrupts, DMA)
- Control systems (PI regulators, anti-windup)

Built by Isaac © 2026
