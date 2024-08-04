[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver DHT11

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/dht11/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

DHT11 digital temperature and humidity sensor is a temperature and humidity composite sensor with calibrated digital signal output. It uses special digital module acquisition technology and temperature and humidity sensing technology to ensure that the product has high reliability and excellent long-term stability. The sensor consists of a capacitive humidity sensor and a NTC temperature sensor, and is connected with a high-performance 8-bit MCU. The sensor has the advantages of low cost, long-term stability, relative humidity and temperature measurement, excellent quality, ultra fast response, strong anti-interference ability, ultra long signal transmission distance, digital signal output and accurate calibration. It is used in HVAC, dehumidifier, agriculture, cold chain storage, test and detection equipment, consumer goods, automobile, automatic control, data recorder, weather station, household appliances, humidity regulator, medical treatment, and other related humidity detection and control.

LibDriver DHT11 is the full function driver of DHT11 launched by LibDriver.It provides the function of reading temperature and relative humidity. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver DHT11 source files.

/interface includes LibDriver DHT11 onewire platform independent template.

/test includes LibDriver DHT11 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver DHT11 sample code.

/doc includes LibDriver DHT11 offline document.

/datasheet includes DHT11 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface onewire platform independent template and finish your platform onewire driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_dht11_basic.h"

uint8_t res;
uint8_t i;
float temperature;
uint8_t humidity;

res = dht11_basic_init();
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    dht11_interface_delay_ms(2000);
    res = dht11_basic_read((float *)&temperature, (uint8_t *)&humidity);
    if (res != 0)
    {
        (void)dht11_basic_deinit();

        return 1;
    }
    dht11_interface_debug_print("dht11: temperature is %0.2fC.\n", temperature);
    dht11_interface_debug_print("dht11: humidity is %d%%.\n", humidity); 
    
    ...
        
}

...

(void)dht11_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/dht11/index.html](https://www.libdriver.com/docs/dht11/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.