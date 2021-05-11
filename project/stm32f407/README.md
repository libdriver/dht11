### 1. chip

#### 1.1 chip info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

data pin: PA8.

### 2. shell

#### 2.1 shell parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. dht11 

#### 3.1 command Instruction

​          dht11 is a basic command which can test all dht11 driver function:

​           -h        show dht11 help 

​           -i         show dht11 chip and driver information.

​           -p       show dht11 pin connections of the current board.

​           -t read <times>        run dht11 read test. times means test times. 

​           -c read <times>        run dht11 read function. times means test times.

#### 3.2 command example

```shell
dht11 -i

dht11: chip is AoSong DHT11.
dht11: manufacturer is Aosong.
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
dht11 -t read 3

dht11: chip is AoSong DHT11.
dht11: manufacturer is Aosong.
dht11: interface is GPIO.
dht11: driver version is 2.0.
dht11: min supply voltage is 3.3V.
dht11: max supply voltage is 5.5V.
dht11: max current is 1.00mA.
dht11: max temperature is 60.0C.
dht11: min temperature is -20.0C.
dht11: start read test.
dth11: temperature: 27.4C.
dth11: humidity: 9%.
dth11: temperature: 27.4C.
dth11: humidity: 9%.
dth11: temperature: 27.4C.
dth11: humidity: 9%.
dht11: finish read test.
```

```shell
dht11 -c read 3

dht11: 1/3.
dht11: temperature is 27.30C.
dht11: humidity is 9%.
dht11: 2/3.
dht11: temperature is 27.40C.
dht11: humidity is 9%.
dht11: 3/3.
dht11: temperature is 27.40C.
dht11: humidity is 9%.
```

```shell
dht11 -h

dht11 -h
	show dht11 help.
dht11 -i
	show dht11 chip and driver information.
dht11 -p
	show dht11 pin connections of the current board.
dht11 -t read <times>
	run dht11 read test.times means test times.
dht11 -c read <times>
	run dht11 read function.times means test times.
```

