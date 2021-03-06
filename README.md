Mbed
======================

Build Instructions
------------------

Build the docker image for OpenOCD.
/openocd
```bash
  docker build -t local/openocd .
```

Build the docker image for Mbed Dev.
/dev
```bash
  docker build -t local/iotdev .
```

Docker rnning under VMware under ubuntu 16.04
Mapping folder from Windows machine tot Docker VM.


OPENOCD:
run bash in conteiner
docker run -it --rm --privileged -v /dev/bus/usb:/dev/bus/usb local/openocd bash
OpenOCD config : "/usr/local/share/openocd/scripts"

Run OPenOCD as server
openocd -c "telnet_port 4444" -f "interface/stlink-v2.cfg" -f "/usr/local/share/openocd/scripts/board/stlink-v2.cfg"


Flash from OpenOCD

Got to source: /usr/src/mbed/mbed-projects/test_spi/BUILD/ALI_F103Cx/GCC_ARM
Flash:
openocd -f "interface/stlink-v2.cfg" -f board/st_mapple_f103rb.cfg -c "init" -c "reset init" -c "flash write_image erase test_spi.elf" -c "reset" -c "shutdown"


MBED OS CLI:

docker run -it --rm -v /mnt/hgfs/docker/mbed:/usr/src/mbed local/iotdev bash
Go to source: /usr/src/mbed/mbed-projects/test_spi/
Compile: mbed compile --profile mbed-os/tools/profiles/debug.json

TEST after flash
Connect to Osciloscope AD9833
Connect USB-UART or Bluetooth UART to Serial Port RX1 TX1

For set Freq: freq 200000
It set 200Khz. sinus default.


MBED OS change.

SPI - 16bit Fix.

mbed-os/targets/TARGET_STM/

stm_spi_api.c  - change

//size = (handle->Init.DataSize == SPI_DATASIZE_16BIT) ? 2 : 1;
size = 1;

mbed_rtx.h - added
#elif defined(TARGET_STM32F103CB)
#ifndef INITIAL_SP
#define INITIAL_SP (0x20005000UL)
#endif
#ifndef OS_TASKCNT
#define OS_TASKCNT 6
#endif
#ifndef OS_MAINSTKSIZE
#define OS_MAINSTKSIZE 128
#endif
#ifndef OS_CLOCK
#define OS_CLOCK 72000000
#endif



TARGET

mbed-os/targets/targets.json - added

"ALI_F103Cx": {
"supported_form_factors": ["ARDUINO", "MORPHO"],
"core": "Cortex-M3",
"default_toolchain": "ARM",
"extra_labels": ["STM", "STM32F1", "STM32F103CB"],
"supported_toolchains": ["GCC_ARM"],
"inherits": ["Target"],
"macros": ["TRANSACTION_QUEUE_SIZE_SPI=2"],
"device_has": ["ANALOGIN", "I2C", "I2CSLAVE", "I2C_ASYNCH", "INTERRUPTIN", "PORTIN", "PORTINOUT", "PORTOUT", "PWMOUT", "SERIAL", "SERIAL_FC", "SERIAL_ASYNCH", "SLEEP", "SPI", "SPISLAVE", "SPI_ASYNCH", "STDIO_MESSAGES"],
"release_versions": ["2", "5"],
"device_name": "STM32F103CB"
},

Mbed-os/targets/TARGET_STM/TARGET_STM32F1 - added

Folder : TARGET_ALI_F103Cx - board.
for CB - work from the box.
For C8 - flash over Stlink flasher.
