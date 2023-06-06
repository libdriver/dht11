### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

DATA Pin: PA8.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. DHT11 

#### 3.1 Command Instruction

1. Show dht11 chip and driver information.

   ```shell
   dht11 (-i | --information)
   ```
2. Show dht11 help.

   ```shell
   dht11 (-h | --help)
   ```

3. Show dht11 pin connections of the current board.

   ```shell
   dht11 (-p | --port)
   ```

4. Run dht11 read test, num means test times. 

   ```shell
   dht11 (-t read | --test=read) [--times=<num>]
   ```

5. Run dht11 read function, num means test times.

   ```shell
   dht11 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
dht11 -i

dht11: chip is ASAIR DHT11.
dht11: manufacturer is ASAIR.
dht11: interface is GPIO.
dht11: driver version is 2.0.
dht11: min supply voltage is 3.3V.
dht11: max supply voltage is 5.5V.
dht11: max current is 1.00mA.
dht11: max temperature is 60.0C.
dht11: min temperature is -20.0C.
```

```shell
dht11 -p

dht11: DATA pin connected to GPIOA PIN8.
```

```shell
dht11 -t read --times=3

dht11: chip is ASAIR DHT11.
dht11: manufacturer is ASAIR.
dht11: interface is GPIO.
dht11: driver version is 2.0.
dht11: min supply voltage is 3.3V.
dht11: max supply voltage is 5.5V.
dht11: max current is 1.00mA.
dht11: max temperature is 60.0C.
dht11: min temperature is -20.0C.
dht11: start read test.
dht11: temperature: 25.9C.
dht11: humidity: 32%.
dht11: temperature: 25.9C.
dht11: humidity: 30%.
dht11: temperature: 26.0C.
dht11: humidity: 29%.
dht11: finish read test.
```

```shell
dht11 -e read --times=3

dht11: 1/3.
dht11: temperature is 25.80C.
dht11: humidity is 18%.
dht11: 2/3.
dht11: temperature is 25.80C.
dht11: humidity is 17%.
dht11: 3/3.
dht11: temperature is 25.70C.
dht11: humidity is 17%.
```

```shell
dht11 -h

Usage:
  dht11 (-i | --information)
  dht11 (-h | --help)
  dht11 (-p | --port)
  dht11 (-t read | --test=read) [--times=<num>]
  dht11 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>     Run the driver example.
  -h, --help                      Show the help.
  -i, --information               Show the chip information.
  -p, --port                      Display the pin connections of the current board.
  -t <read>, --test=<read>        Run the driver test.
      --times=<num>               Set the running times.([default: 3])
```

