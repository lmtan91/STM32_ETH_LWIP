TARGET:=httpserver_netconn
# TODO change to your ARM gcc toolchain path
TOOLCHAIN_ROOT:=/opt/gcc-arm-none-eabi-4_7-2014q2
TOOLCHAIN_PATH:=$(TOOLCHAIN_ROOT)/bin
TOOLCHAIN_PREFIX:=arm-none-eabi

# Optimization level, can be [0, 1, 2, 3, s].
OPTLVL:=0
DBG:=-g3

FREERTOS:=$(CURDIR)/../../FreeRTOS
STARTUP:=$(CURDIR)/../../hardware
PROJECT:=$(CURDIR)
STM32EVAL:=$(CURDIR)/../../Utilities/STM32_EVAL
ETHDRIVER:=$(CURDIR)/../../Libraries/STM32F4x7_ETH_Driver
LWIP:=$(CURDIR)/../../Utilities/lwip_v1.3.2
STM32F4_STDPERIPH_DRIVER:=$(CURDIR)/../../Libraries/STM32F4xx_StdPeriph_Driver
CMSIS:=$(CURDIR)/../../Libraries/CMSIS

LINKER_SCRIPT:=$(CURDIR)/../../Utilities/stm32_flash.ld

#INCLUDE=-I$(CURDIR)/hardware
INCLUDE+=-I$(FREERTOS)/include
#INCLUDE+=-I$(FREERTOS)/portable/GCC/ARM_CM4F
INCLUDE+=-I$(FREERTOS)/portable/GCC/ARM_CM4F
INCLUDE+=-I$(CMSIS)/Device/ST/STM32F4xx/Include
INCLUDE+=-I$(CMSIS)/Include
INCLUDE+=-I$(STM32F4_STDPERIPH_DRIVER)/inc
INCLUDE+=-I$(CURDIR)/config
INCLUDE+=-I$(PROJECT)/inc
INCLUDE+=-I$(STM32EVAL)/STM3240_41_G_EVAL
INCLUDE+=-I$(STM32EVAL)/Common
INCLUDE+=-I$(ETHDRIVER)/inc
INCLUDE+=-I$(LWIP)/src/include
INCLUDE+=-I$(LWIP)/src/include/ipv4
INCLUDE+=-I$(LWIP)/src/include/lwip
INCLUDE+=-I$(LWIP)/port/STM32F4x7
INCLUDE+=-I$(LWIP)/port/STM32F4x7/FreeRTOS

BUILD_DIR = $(CURDIR)/build
BIN_DIR = $(CURDIR)/binary

# vpath is used so object files are written to the current directory instead
# of the same directory as their source files
vpath %.c $(STM32F4_STDPERIPH_DRIVER)/src \
          $(CURDIR)/../../Libraries/retargetStdioMessage $(STARTUP) $(FREERTOS) \
          $(FREERTOS)/portable/MemMang $(FREERTOS)/portable/GCC/ARM_CM4F \
          $(PROJECT)/src $(ETHDRIVER)/src \
          $(LWIP)/port/STM32F4x7/FreeRTOS \
          $(STM32EVAL)/STM3240_41_G_EVAL \
          $(LWIP)/src/api \
          $(LWIP)/src/core \
          $(LWIP)/src/netif \
          $(LWIP)/src/core/ipv4

vpath %.s $(STARTUP)
ASRC=startup_stm32f4xx.s

# Project Source Files
SRC+=stm32f4xx_it.c
SRC+=system_stm32f4xx.c
SRC+=main.c
SRC+=stm32f4x7_eth_bsp.c
SRC+=netconf.c
SRC+=httpserver-netconn.c
SRC+=fs.c
SRC+=fsdata.c
SRC+=serial_debug.c

# retarget sddio printf to USART1
SRC+=retargetio.c

# STM_EVAL
SRC+=stm324xg_eval.c
SRC+=stm324xg_eval_lcd.c

# Ethernet driver
SRC+=stm32f4x7_eth.c

# lwip
SRC+=ethernetif.c
SRC+=tcpip.c
SRC+=inet.c
SRC+=netif.c
SRC+=api_lib.c
SRC+=netbuf.c
SRC+=sys_arch.c
SRC+=pbuf.c
SRC+=etharp.c
SRC+=sys.c
SRC+=dhcp.c
SRC+=autoip.c
SRC+=ip.c
SRC+=memp.c
SRC+=mem.c
SRC+=init.c
SRC+=tcp.c
SRC+=tcp_in.c
SRC+=tcp_out.c
SRC+=api_msg.c
SRC+=ip_addr.c
SRC+=udp.c
SRC+=raw.c
SRC+=icmp.c
SRC+=inet_chksum.c

# FreeRTOS Source Files
SRC+=port.c
SRC+=list.c
SRC+=queue.c
SRC+=tasks.c
#SRC+=event_groups.c
#SRC+=timers.c
SRC+=heap_4.c
#SRC+=heap_2.c

# Standard Peripheral Source Files
SRC+=misc.c
SRC+=stm32f4xx_dcmi.c
#SRC+=stm32f4xx_hash.c
SRC+=stm32f4xx_rtc.c
SRC+=stm32f4xx_adc.c
SRC+=stm32f4xx_dma.c
#SRC+=stm32f4xx_hash_md5.c
#SRC+=stm32f4xx_sai.c
SRC+=stm32f4xx_can.c
#SRC+=stm32f4xx_dma2d.c
#SRC+=stm32f4xx_hash_sha1.c
SRC+=stm32f4xx_sdio.c
#SRC+=stm32f4xx_cec.c
#SRC+=stm32f4xx_dsi.c
SRC+=stm32f4xx_i2c.c
#SRC+=stm32f4xx_spdifrx.c
SRC+=stm32f4xx_crc.c
SRC+=stm32f4xx_exti.c
SRC+=stm32f4xx_iwdg.c
SRC+=stm32f4xx_spi.c
#SRC+=stm32f4xx_cryp.c
SRC+=stm32f4xx_flash.c
#SRC+=stm32f4xx_lptim.c
SRC+=stm32f4xx_syscfg.c
#SRC+=stm32f4xx_cryp_aes.c
#SRC+=stm32f4xx_flash_ramfunc.c
#SRC+=stm32f4xx_ltdc.c
SRC+=stm32f4xx_tim.c
#SRC+=stm32f4xx_cryp_des.c
#SRC+=stm32f4xx_fmc.c
SRC+=stm32f4xx_pwr.c
SRC+=stm32f4xx_usart.c
#SRC+=stm32f4xx_cryp_tdes.c
#SRC+=stm32f4xx_fmpi2c.c
#SRC+=stm32f4xx_qspi.c
SRC+=stm32f4xx_wwdg.c
SRC+=stm32f4xx_dac.c
SRC+=stm32f4xx_fsmc.c
SRC+=stm32f4xx_rcc.c
SRC+=stm32f4xx_dbgmcu.c
SRC+=stm32f4xx_gpio.c
SRC+=stm32f4xx_rng.c

CDEFS=-DUSE_STDPERIPH_DRIVER
CDEFS+=-DSTM32F4XX
CDEFS+=-DUSE_STM324xG_EVAL
#CDEFS+=-DSTM32F40_41xxx
CDEFS+=-DHSE_VALUE=8000000
CDEFS+=-D__FPU_PRESENT=1
CDEFS+=-D__FPU_USED=1
CDEFS+=-DARM_MATH_CM4
CDEFS+=-DUSE_DHCP
CDEFS+=-DUSE_LCD
CDEFS+=-DSERIAL_DEBUG

MCUFLAGS=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -finline-functions -Wdouble-promotion -std=gnu99
COMMONFLAGS=-O$(OPTLVL) $(DBG) -Wall -ffunction-sections -fdata-sections
CFLAGS=$(COMMONFLAGS) $(MCUFLAGS) $(INCLUDE) $(CDEFS)

LDLIBS=-lm -lc -lgcc
LDFLAGS=$(MCUFLAGS) -u _scanf_float -u _printf_float -fno-exceptions -Wl,--gc-sections,-T$(LINKER_SCRIPT),-Map,$(BIN_DIR)/$(TARGET).map

CC=$(TOOLCHAIN_PREFIX)-gcc
LD=$(TOOLCHAIN_PREFIX)-gcc
OBJCOPY=$(TOOLCHAIN_PREFIX)-objcopy
AS=$(TOOLCHAIN_PREFIX)-as
AR=$(TOOLCHAIN_PREFIX)-ar
GDB=$(TOOLCHAIN_PREFIX)-gdb

OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/%.o: %.c
	@echo [CC] $(notdir $<)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $< -c -o $@

all: $(OBJ)
	@mkdir -p $(BIN_DIR)
	@echo [AS] $(ASRC)
	@$(AS) -o $(ASRC:%.s=$(BUILD_DIR)/%.o) $(STARTUP)/$(ASRC)
	@echo [LD] $(TARGET).elf
	@$(CC) -o $(BIN_DIR)/$(TARGET).elf $(LDFLAGS) $(OBJ) $(ASRC:%.s=$(BUILD_DIR)/%.o) $(LDLIBS)
	@echo [HEX] $(TARGET).hex
	@$(OBJCOPY) -O ihex $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).hex
	@echo [BIN] $(TARGET).bin
	@$(OBJCOPY) -O binary $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).bin

.PHONY: clean

clean:
	@echo [RM] OBJ
	@rm -f $(OBJ)
	@rm -f $(ASRC:%.s=$(BUILD_DIR)/%.o)
	@echo [RM] BIN
	@rm -f $(BIN_DIR)/$(TARGET).elf
	@rm -f $(BIN_DIR)/$(TARGET).hex
	@rm -f $(BIN_DIR)/$(TARGET).bin

flash:
	@st-flash write $(BIN_DIR)/$(TARGET).bin 0x8000000
