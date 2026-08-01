# STM32 PMSM FOC Motor Controller | STM32 永磁同步电机 FOC 控制器

Field-Oriented Control (FOC) firmware for STM32 microcontrollers driving PMSM motors.

基于 STM32 的永磁同步电机磁场定向控制（FOC）固件。

---

## Features | 功能

- **Clarke/Park Transform** — abc → αβ → dq coordinate transformation
- **Space Vector Modulation (SVM)** — Efficient PWM generation
- **Sensorless Observer** — Sliding Mode Observer (SMO) for speed estimation
- **PI Controllers** — Speed loop and current loop with anti-windup
- **Over-current Protection** — Hardware and software protection

## Hardware | 硬件

- MCU: STM32F4xx (Cortex-M4F)
- Driver: 3-phase inverter (6x MOSFET/IGBT)
- Motor: PMSM (BLDC compatible)

## Build | 编译

```bash
make
```

## Flash | 烧录

```bash
st-flash write build/foc_controller.bin 0x08000000
```

## Project Structure | 项目结构

```
include/    # Header files (foc.h, observer.h, svm.h)
src/        # Source code (main.c, foc.c, observer.c, svm.c)
linker.ld   # Linker script
Makefile    # Build system
```

## License

MIT
