# STM8_SDCC_delay_ms_delay_us

Implementing functions to generate reliable delays (ms and us delays)

STM8 Microcontroller Bare metal programming (SDCC C Compiler)


SMT8S103F3 MCU

Internal High Speed Clock (HSI 16MHz)


Reliable for delay equal to or greater than 5us only.

Terminal:
sdcc -mstm8 --std-c99 01_Led_delay.c
stm8flash -c stlinkv2 -p stm8s103f3 -w 01_Led_delay.ihx
