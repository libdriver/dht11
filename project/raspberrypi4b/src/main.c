/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
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
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     dht11 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t dht11(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* running times */
            case 1 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (dht11_read_test(times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float temperature;
        uint8_t humidity;
        
        /* init */
        res = dht11_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 2000ms */
            dht11_interface_delay_ms(2000);
            
            /* read data */
            res = dht11_basic_read((float *)&temperature, (uint8_t *)&humidity);
            if (res != 0)
            {
                (void)dht11_basic_deinit();
                
                return 1;
            }
            
            /* output */
            dht11_interface_debug_print("dht11: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            dht11_interface_debug_print("dht11: temperature is %0.2fC.\n", temperature);
            dht11_interface_debug_print("dht11: humidity is %d%%.\n", humidity); 
        }
        
        /* deinit */
        (void)dht11_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        dht11_interface_debug_print("Usage:\n");
        dht11_interface_debug_print("  dht11 (-i | --information)\n");
        dht11_interface_debug_print("  dht11 (-h | --help)\n");
        dht11_interface_debug_print("  dht11 (-p | --port)\n");
        dht11_interface_debug_print("  dht11 (-t read | --test=read) [--times=<num>]\n");
        dht11_interface_debug_print("  dht11 (-e read | --example=read) [--times=<num>]\n");
        dht11_interface_debug_print("\n");
        dht11_interface_debug_print("Options:\n");
        dht11_interface_debug_print("  -e <read>, --example=<read>     Run the driver example.\n");
        dht11_interface_debug_print("  -h, --help                      Show the help.\n");
        dht11_interface_debug_print("  -i, --information               Show the chip information.\n");
        dht11_interface_debug_print("  -p, --port                      Display the pin connections of the current board.\n");
        dht11_interface_debug_print("  -t <read>, --test=<read>        Run the driver test.\n");
        dht11_interface_debug_print("      --times=<num>               Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
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
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        dht11_interface_debug_print("dht11: DATA pin connected to GPIO17(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = dht11(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        dht11_interface_debug_print("dht11: run failed.\n");
    }
    else if (res == 5)
    {
        dht11_interface_debug_print("dht11: param is invalid.\n");
    }
    else
    {
        dht11_interface_debug_print("dht11: unknown status code.\n");
    }

    return 0;
}
