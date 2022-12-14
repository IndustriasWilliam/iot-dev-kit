# IoT DevKit v0.1

# Board Features

## Core

- STM32H743IIT6 ARM Microcontroller;
- 32-bit Arm® Cortex®-M7 core with doubleprecision FPU;
- L1 cache: 16 Kbytes of data and 16 Kbytes of instruction cache;
- Frequency up to 480 MHz, MPU, 1027 DMIPS/2.14 DMIPS/MHz (Dhrystone 2.1), and DSP instructions; 
## Memory

- Up to 2 Mbytes of internal Flash memory with readwhile-write support;
- 16MB NOR exernal Flash memory;
- 32MB 16-bit SDRAM;
## Graphics

- HDMI XGA (max resolution) output;
- Chrom-ART graphical hardware Accelerator (DMA2D) to reduce CPU load;
- Hardware JPEG Codec;
## Comunications

- 2.4GHz Transceiver @2Mbits;
- Ethernet (TCPIP, WebServer, UDP, TCP,..., MQTT, examples);
- USB OTG support;
- SDCARD input @ 32GB support;
- IR receiver;

# Applications 

- IoT gateware send data to broker (thingsboard for example) over MQTT or HTTP;
- Smart Home;
- Environment monitor;
- Game console emulator;

# Software dependencies

### [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)

- We'are going to use this IDE for code production;
- Get the latest version;

### [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)

- This tool is potent, and we're going to use it for code generation;
- Apply some configurations, for example, clock and others peripherals;

### [STM32 ST-LINK utility ](https://www.st.com/en/development-tools/stsw-link004.html)

- This tool we're going to use for code download;
- Get the flash loader script into the Flash Loader path, and paste it inside the ST-Link installation path in the External Loader path;

### [TouchGFX](https://www.st.com/en/development-tools/touchgfxdesigner.html)

- Tool for GUI creation;

# IoT DevKit Board components

![alt text](/images/diagram.jpg)


### Serial Wire Debug Conector

1. VDD-3.3V
2. JTMS-SWDIO
3. GND
4. JTCK-SWCLK
5. GND
6. JTDO-TRACESWO
7. NC
8. JTDI
9. GND
10. NRST 