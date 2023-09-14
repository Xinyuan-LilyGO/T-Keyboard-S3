<!--
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-09-11 16:13:14
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-14 13:35:00
 * @License: GPL 3.0
-->
<h1 align = "center">T-Keyboard-S3</h1>

<p> 
  <a href="https://code.visualstudio.com/"> <img src="badges/VisualStudioCode_badge.png" height="25px" alt="VisualStudioCode_badge" /> </a>
  <a href="https://platformio.org/"> <img src="badges/PlatformIO_badge.png" height="25px" alt="PlatformIO_badge" /> </a>
  <a href="https://hangzhang.org/"> <img src="badges/Arduino_badge.png" height="25px" alt="Arduino_badge"></a>
</p> 

## **[English](./README.md) | 中文**

## 版本迭代:
| Version                               | Update date                       |
| :-------------------------------: | :-------------------------------: |
| T-Keyboard-S3_V1.0            | 2023-09-04                         |

## 购买链接

| Product                         | Link                    |
| :---------------------------: | :-------------------: |
| T-Keyboard-S3_V1.0       | [暂未售卖]()       |

## 目录
- [描述](#描述)
- [预览](#预览)
- [模块](#模块)
- [快速开始](#快速开始)
- [引脚总览](#引脚总览)
- [常见问题](#常见问题)
- [项目](#项目)
- [资料](#资料)
- [依赖库](#依赖库)

## 描述

T-Keyboard-S3是一款基于ESP32­ S3­ WROOM­ 1模块所开发的智能按键控制器，他与往常的控制器不同，在按键的上方有一块0.85英寸128x128RGB像素的LCD屏幕，他与底板主控板通过一根FPC排线所连接，兼容Arduino_GFX、TFT_eSPI、lvgl等库编程。四个按键兼容普通热插拔机械键盘轴，可任意更换轴的类型（具体轴的属性在接下来的介绍会提到）。  

T-Keyboard-S3可做有线USB与WIN10电脑进行连接使之成为一个迷你的有线键盘，也可以通过蓝牙无线连接，作为一个蓝牙键盘来使用。

T-Keyboard-S3有丰富的扩展IO口，可扩展三个方向的模块，其中默认配置为前方扬声器、左边旋转编码器、下方五向方向按键，你也可以连接其他的模块，更多有趣的功能待你发现。


## 预览

### PCB板

<details><summary><b>T-Keyboard-S3</b></summary>

### T-Keyboard-S3 正面
<center>
    <img src="image/1.png" alt="example">
</center>

### T-Keyboard-S3 反面
<center>
    <img src="image/2.png" alt="example">
</center>

</details>


<details><summary><b>T-Keyboard-S3_FPC</b></summary>

### T-Keyboard-S3_FPC 正反面
<center>
    <img src="image/3.png" alt="example">
</center>

</details>

### 渲染图


## 模块

### 1. ESP32­ S3­ WROOM­ 1

* 芯片：ESP32-S3R8
* PSRAM：无
* FLASH：16M
* 其他说明：更多资料请访问[乐鑫官方ESP32­ S3­ WROOM­ 1数据手册](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf)

### 2. 四块128x128像素LCD显示屏幕

* 驱动：GC9107
* 兼容库：Arduino_GFX、TFT_eSPI、lvgl
* 使用总线通信协议：标准SPI
* 其他说明：四块屏幕的RST、DC、MOSI、SCLK、BL引脚各共用一条总线，初始化复位时候四块屏幕一起复位，选择不同CS线即可控制不同的屏幕刷新数据

### 3. 热插拔按键

* 规格：选用的热插拔连接器是Kailh公司的连接器，两引脚间距是6.35MM，满足间距为6.35mm的热插拔针脚按键都可适用
* PCB连接：默认KEY1->KEY3引脚未连接上拉电阻，但有预留一个上拉电阻位置，下拉使能低电平作为判断信号，KEY4复用为BOOT-0作为系统上电模式选择，默认有一个10K上拉电阻，同样以低电平作为判断信号，软件内必须配置其引脚为内部上拉才能稳定使用
* 其他说明：因为要连接屏幕，所以请务必选择中间有开孔的热插拔按键，间距应该大于排线宽度7MM以上

### 4. 固定孔螺丝

* 规格：PCB上的开孔直径为2.5MM，在选择螺丝固定的时候请选择2.5MM以下的


## 快速开始

### PlatformIO
1. 安装[VisualStudioCode](https://code.visualstudio.com/Download)，根据你的系统类型选择安装。

2. 打开VisualStudioCode软件侧边栏的“扩展”（或者使用<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>X</kbd>打开扩展），搜索“PlatformIO IDE”扩展并下载。

3. 在安装扩展的期间，你可以前往GitHub下载程序，你可以通过点击带绿色字样的“<> Code”下载主分支程序，也通过侧边栏下载“Releases”版本程序。

4. 扩展安装完成后，打开侧边栏的资源管理器（或者使用<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>E</kbd>打开），点击“打开文件夹”，找到刚刚你下载的项目代码（整个文件夹），点击“添加”，此时项目文件就添加到你的工作区了。

5. 打开项目文件中的“platformio.ini”（添加文件夹成功后PlatformIO会自动打开对应文件夹的“platformio.ini”）,在“[platformio]”目录下取消注释选择你需要烧录的示例程序（以“default_envs = xxx”为标头），然后点击左下角的“<kbd>[√](image/4.png)</kbd>”进行编译，如果编译无误，将单片机连接电脑，点击左下角“<kbd>[→](image/5.png)</kbd>”即可进行烧录。

### Arduino
1. 安装[Arduino](https://www.arduino.cc/en/software)，根据你的系统类型选择安装。

2. 打开项目文件夹的“example”目录，选择示例项目文件夹，打开以“.ino”结尾的文件即可打开Arduino IDE项目工作区。

3. 打开右上角“工具”菜单栏->选择“开发板”->“开发板管理器”，找到或者搜索“esp32”，下载作者名为“Espressif Systems”的开发板文件。接着返回“开发板”菜单栏，选择“ESP32 Arduino”开发板下的开发板类型，选择的开发板类型由“platformio.ini”文件中以[env]目录下的“board = xxx”标头为准，如果没有对应的开发板，则需要自己手动添加项目文件夹下“board”目录下的开发板。

4. 打开菜单栏“[文件](image/6.png)”->“[首选项](image/6.png)”，找到“[项目文件夹位置](image/7.png)”这一栏，将项目目录下的“libraries”文件夹里的所有库文件连带文件夹复制粘贴到这个目录下的“libraries”里边。

5. 在 "工具 "菜单中选择正确的设置，如下表所示。

| Setting                               | Value                                 |
| :-------------------------------: | :-------------------------------: |
| USB Mode                           | Hardware CDC and JTAG     |
| USB CDC On Boot                | Enabled                             |
| USB Firmware MSC On Boot | Disabled                             |
| USB DFU On Boot                | Disabled                             |
| CPU Frequency                   | 240MHz (WiFi)                    |
| Flash Mode                         | QIO 80MHz                         |
| Flash Size                           | 16MB (128Mb)                     |
| Core Debug Level                | None                                 |
| Arduino Runs On                  | Core 1                               |
| Events Run On                     | Core 1                               |

6. 选择正确的端口。

7. 点击右上角“<kbd>[√](image/8.png)</kbd>”进行编译，如果编译无误，将单片机连接电脑，点击右上角“<kbd>[→](image/9.png)</kbd>”即可进行烧录。

### firmware烧录
1. 打开项目文件“tools”找到ESP32烧录工具，打开。

2. 选择正确的烧录芯片以及烧录方式点击“OK”，如图所示根据步骤1->2->3->4->5即可烧录程序，如果烧录不成功，请按住“BOOT-0”键再下载烧录。

3. 烧录文件在项目文件根目录“[firmware](./firmware/)”文件下，里面有对firmware文件版本的说明，选择合适的版本下载即可。

<center>
    <img src="image/10.png" alt="example">
    <img src="image/11.png" alt="example">
</center>


## 引脚总览

| 显示屏引脚       | ESP32S3引脚      |
| :------------------: | :------------------:|
| DC                     | IO45                  |
| SCLK                  | IO47                  |
| MOSI                  | IO48                  |
| MISO                  | -1                      |
| RST                    | IO38                  |
| BL                      | IO39                  |
| CS1                    | IO12                  |
| CS2                    | IO13                  |
| CS3                    | IO14                  |
| CS4                    | IO21                  |

| 按键引脚           | ESP32S3引脚      |
| :------------------: | :------------------:|
| KEY1                  | IO10                  |
| KEY2                  | IO9                    |
| KEY3                  | IO46                  |
| KEY4                  | IO3                    |

| 其他引脚           | ESP32S3引脚      |
| :------------------: | :------------------:|
| WS2812B_Data    | IO11                 |

## 常见问题

* Q. 看了以上教程我还是不会搭建编程环境怎么办？
* A. 如果看了以上教程还不懂如何搭建环境的可以参考[LilyGo-Document](https://github.com/Xinyuan-LilyGO/LilyGo-Document)文档说明来搭建。

<br />

* Q. 为什么打开Arduino IDE时他会提醒我是否要升级库文件？我应该升级还是不升级？
* A. 选择不升级库文件，不同版本的库文件可能不会相互兼容所以不建议升级库文件。

<br />

* Q. 为什么我的板子上“Uart”接口没有输出串口数据，是不是坏了用不了啊？
* A. 因为项目文件默认配置将USB接口作为Uart0串口输出作为调试，“Uart”接口连接的是Uart0，不经配置自然是不会输出任何数据的。<br />PlatformIO用户请打开项目文件“platformio.ini”，将“build_flags = xxx”下的选项“-DARDUINO_USB_CDC_ON_BOOT=true”修改成“-DARDUINO_USB_CDC_ON_BOOT=false”即可正常使用外部“Uart”接口。<br />Arduino用户打开菜单“工具”栏，选择USB CDC On Boot: “Disabled”即可正常使用外部“Uart”接口。

<br />

* Q. 我应该如何开启外部PSRAM呢？
* A. PlatformIO用户请打开项目文件“platformio.ini”，将“build_flags = xxx”下的选项“-D BOARD_HAS_PSRAM”取消注释即可，注意，如果设备上无外接PSRAM，烧录后就会报错。<br />Arduino用户打开菜单“工具”栏，选择PSRAM: “QSPI PSRAM”即可正常使用外部PSRAM。

<br />

* Q. 为什么我的板子一直烧录失败呢？
* A. 请按住“BOOT-0”按键重新下载程序。

## 项目
* [SCH_T-Keyboard-S3_V1.0](./Project/SCH_T-Keyboard-S3_V1.0.pdf)

## 资料
* [ESP32-S3-WROOM-1-N16R2](./information/ESP32-S3-WROOM-1-N16R2.pdf)
* [WS2812B-2020](./information/WS2812B-2020.pdf)


## 依赖库
* [Arduino_GFX-1.3.6](https://github.com/moononournation/Arduino_GFX)
* [FastLED-3.6.0](https://github.com/FastLED/FastLED)
* [lvgl](https://github.com/lvgl/lvgl)
* [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)