# STM32 PMSM FOC Controller 🔧

Field-Oriented Control (FOC) implementation for Permanent Magnet Synchronous Motors on STM32.

基于 STM32 的永磁同步电机（PMSM）磁场定向控制（FOC）实现。

---

## Features / 功能特性

- **Sensorless FOC** — Sliding mode observer for rotor position / 无传感器FOC — 滑模观测器估计转子位置
- **Clarke & Park transforms** — ABC → αβ → dq / Clarke和Park变换
- **PI current controllers** — d-axis (flux) and q-axis (torque) / PI电流控制器 — d轴（磁通）和q轴（转矩）
- **Space Vector Modulation (SVM)** — Optimized PWM / 空间矢量调制 — 优化PWM
- **Speed control** — With ramp profile / 速度控制 — 带斜坡曲线
- **Over-current protection** — ADC-based / 过流保护 — 基于ADC

---

## Algorithm Flow / 算法流程

```
Ia, Ib, Ic ──▶ Clarke ──▶ Park ──▶ PI Controller ──▶ Inv Park ──▶ SVM ──▶ PWM
               (α,β)      (d,q)    (Vd, Vq)          (Vα, Vβ)    duty
                                  ▲
                                  │
                           SMO ───┘ θ_est
                        (滑模观测器)
```

---

## Project Structure / 项目结构

```
stm32-pmsm-foc-controller/
├── include/
│   ├── foc.h          # Transform functions / 变换函数
│   ├── pid.h          # PI controller / PI控制器
│   ├── observer.h     # Sliding mode observer / 滑模观测器
│   ├── svm.h          # Space Vector Modulation / 空间矢量调制
│   └── adc.h          # ADC current sensing / ADC电流采样
├── src/
│   ├── main.c         # Main loop / 主循环
│   ├── foc.c          # FOC transforms / FOC变换
│   ├── pid.c          # PI implementation / PI实现
│   ├── observer.c     # SMO implementation / 滑模观测器实现
│   ├── svm.c          # SVM implementation / SVM实现
│   └── adc.c          # ADC driver / ADC驱动
└── Makefile
```

## Quick Start / 快速开始
```bash
make && make flash
```

## License / 许可证
MIT License

## Author / 作者
Isaac — Diploma in Electronic Engineering, TAR UMT
用 ❤️ 构建，用于学习电机控制
