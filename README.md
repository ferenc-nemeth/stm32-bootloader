# stm32-bootloader
UART bootloader for STM32 microcontroller.

### Table of contents
- [Introduction](#introduction)
- [How it works](#how-it-works)
  - [Overall](#overall)
  - [Memory map](#memory-map)
  - [Code](#code)
- [How to use it](#how-to-use-it)
  - [Embedded](#embedded)
  - [PC](#pc)
  - [Porting](#porting)
- [References](#references)

### Introduction
A bootloader for STM32F100 (STM32VLDISCOVERY board) [[1]](#references) with UART and Xmodem protocol [[2]](#references)[[3]](#references).
The software is created with Atollic trueSTUDIO and the drivers are generated with CubeMX.

Main features:
- UART & Xmodem protocol
- CRC16 checksum
- Supports 128 and 1024 bytes data length

### How it works
#### Overall
The bootloader was developed for STM32VLDISCOVERY board, the only extra thing needed is an USB-UART module on PA10 (RX) and PA9 (TX) pins.

<img src="https://raw.githubusercontent.com/ferenc-nemeth/stm32-bootloader/master/Design/stm32f100-pinout.png" > <br>
*Figure 1. Pinout of the system.*

After start-up, the system sends a welcome message through UART and checks if the user button is pressed. If it is pressed, then it stays in booatloader mode, turns on the green (PC9) LED and waits for a new binary file. If the button isn't pressed, then it jumps to the user application.

<img src="https://raw.githubusercontent.com/ferenc-nemeth/stm32-bootloader/master/Design/bootloader.png" > <br>
*Figure 2. Brief overview of the workflow of the system.*

The Xmodem protocol is clearly explained in the [references](#references).

#### Memory map
The bootloader starts from 0x08000000 and the user application starts from 0x08008000.

<img src="https://raw.githubusercontent.com/ferenc-nemeth/stm32-bootloader/master/Design/memory_map.png" > <br>
*Figure 3. The organization of the memory.*

#### Code
Every important code is inside the Src and Inc folders. main.c holds the button check, xmodem.c and .h hold the communication portocol, uart.c and .h are a layer between Xmodem and the generated HAL code, flash.c and .h have the writing/erasing/jumping related functions. Everything else is provided by ST.
The code is fully commented, so it should be easy to understand.

### How to use it
#### Embedded
To use the bootloader, just get the softwares mentioned in the [Introduction](#introduction) and flash it. 

I included an example binary file called "blinky_test.bin" in the root folder. It blinks the blue (PC8) LED on the board.
To make your own binary, you have to modify the memory location in the linker script (STM32F100RB_FLASH.ld):
```
FLASH (rx)      : ORIGIN = 0x8008000,
```
And the vector table offset in system_stm32f1xx.c
```
#define VECT_TAB_OFFSET  0x00008000U
```
Last step is you have to generate a \*.bin file:
```
arm-atollic-eabi-objcopy -O binary "input.elf" "output.bin"
```

#### PC
To update the firmware, you need a terminal software, that supports Xmodem. I recommend PuTTY [[4]](#references) or Tera Term [[5]](#references).

Configure them in the following way:
- Baud rate: 115200
- Data bits: 8
- Parity: none
- Stop bits: 1

In PuTTY: select *Files Transfer* >> *Xmodem* (or *Xmodem 1K*) >> *Send* and then open the binary file.

<img src="https://raw.githubusercontent.com/ferenc-nemeth/stm32-bootloader/master/Design/terminal-putty.png" > <br>
*Figure 4. PuTTY.*

In Tera Term: select *File* >> *Transfer* >> *Xmodem* >> *Send* and then open the binary file.
<img src="https://raw.githubusercontent.com/ferenc-nemeth/stm32-bootloader/master/Design/terminal-teraterm.png" > <br>
*Figure 5. Tera Term.*

In case everything was fine, then the output should be the same:
```
================================
UART Bootloader
https://github.com/ferenc-nemeth
================================

Please send a new binary file with Xmodem protocol to update the firmware.
CCCCCCC
Firmware updated!
Jumping to user application...
```

#### Porting
I included the *.ioc file, so the drivers can be regenerated for any ST microntroller (if it has similar memory structure).
If you have a non-ST microntroller, then the xmodem protocol can be reused, but nothing else.

### References
[1] [ST - Discovery kit with STM32F100RB MCU](https://www.st.com/en/evaluation-tools/stm32vldiscovery.html)<br>
[2] [Xmodem protocol with CRC](https://web.mit.edu/6.115/www/amulet/xmodem.htm)<br>
[3] [Chuck Forsberg - XMODEM/YMODEM PROTOCOL REFERENCE](http://www.blunk-electronic.de/train-z/pdf/xymodem.pdf)<br>
[4] [PuTTY](https://putty.org/)<br>
[5] [Tera Term](https://ttssh2.osdn.jp/)<br>

