/**
 * Copyright (C) LibDriver 2015-2021 All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-03-12
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/12  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_dht11_basic.h"
#include "driver_dht11_read_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     dht11 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t dht11(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            dht11_info_t info;
            
            /* print dht11 information */
            dht11_info(&info);
            dht11_interface_debug_print("dht11: chip is %s.\n", info.chip_name);
            dht11_interface_debug_print("dht11: manufacturer is %s.\n", info.manufacturer_name);
            dht11_interface_debug_print("dht11: interface is %s.\n", info.interface);
            dht11_interface_debug_print("dht11: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            dht11_interface_debug_print("dht11: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            dht11_interface_debug_print("dht11: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            dht11_interface_debug_print("dht11: max current is %0.2fmA.\n", info.max_current_ma);
            dht11_interface_debug_print("dht11: max temperature is %0.1fC.\n", info.temperature_max);
            dht11_interface_debug_print("dht11: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            dht11_interface_debug_print("dht11: DATA pin connected to GPIOA PIN8.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            help:
            
            dht11_interface_debug_print("dht11 -h\n\tshow dht11 help.\n");
            dht11_interface_debug_print("dht11 -i\n\tshow dht11 chip and driver information.\n");
            dht11_interface_debug_print("dht11 -p\n\tshow dht11 pin connections of the current board.\n");
            dht11_interface_debug_print("dht11 -t read <times>\n\trun dht11 read test.times means test times.\n");
            dht11_interface_debug_print("dht11 -c read <times>\n\trun dht11 read function.times means test times.\n");
            
            return 0;
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                /* run read test */
                if (dht11_read_test(atoi(argv[3])))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run common */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* basic read */
            if (strcmp("read", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times;
                volatile uint32_t i;
                volatile float temperature;
                volatile uint8_t humidity;
                
                res = dht11_basic_init();
                if (res)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i=0; i<times; i++)
                {
                    dht11_interface_delay_ms(2000);
                    res = dht11_basic_read((float *)&temperature, (uint8_t *)&humidity);
                    if (res)
                    {
                        dht11_basic_deinit();
                        
                        return 1;
                    }
                    dht11_interface_debug_print("dht11: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    dht11_interface_debug_print("dht11: temperature is %0.2fC.\n", temperature);
                    dht11_interface_debug_print("dht11: humidity is %d%%.\n", humidity); 
                }
                dht11_basic_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    volatile uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register dht11 fuction */
    shell_init();
    shell_register("dht11", dht11);
    uart1_print("dht11: welcome to libdriver dht11.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("dht11: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("dht11: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("dht11: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("dht11: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("dht11: param is invalid.\n");
            }
            else
            {
                uart1_print("dht11: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
