### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

DATA Pin: DATA GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(dht11 REQUIRED)
```

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
./dht11 -i

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
./dht11 -p

dht11: DATA pin connected to GPIO17(BCM).
```

```shell
./dht11 -t read --times=3

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
dht11: temperature: 28.2C.
dht11: humidity: 10%.
dht11: temperature: 28.2C.
dht11: humidity: 10%.
dht11: temperature: 28.4C.
dht11: humidity: 10%.
dht11: finish read test.
```

```shell
./dht11 -e read --times=3

dht11: 1/3.
dht11: temperature is 28.40C.
dht11: humidity is 10%.
dht11: 2/3.
dht11: temperature is 28.40C.
dht11: humidity is 10%.
dht11: 3/3.
dht11: temperature is 28.40C.
dht11: humidity is 10%.
```

```shell
./dht11 -h

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

