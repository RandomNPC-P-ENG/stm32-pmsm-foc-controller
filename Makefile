# STM32 PMSM FOC build / FOC固件构建
CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -Wall -Iinclude
LDFLAGS = -T linker.ld -nostartfiles -lm

TARGET = foc
SRCS = src/main.c src/foc.c src/pid.c src/observer.c src/svm.c src/adc.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET).bin
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
$(TARGET).bin: $(TARGET).elf
	arm-none-eabi-objcopy -O binary $< $@
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x08000000
clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin
