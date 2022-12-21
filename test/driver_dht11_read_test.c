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
 * @file      driver_dht11_read_test.c
 * @brief     driver dht11 read test source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-12
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/12  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/11/19  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_dht11_read_test.h"

static dht11_handle_t gs_handle;        /**< dht11 handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 * @note      none
 */
uint8_t dht11_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    uint16_t temperature_raw;
    uint16_t humidity_raw;
    float temperature;
    uint8_t humidity;
    dht11_info_t info;
   
    /* link interface function */
    DRIVER_DHT11_LINK_INIT(&gs_handle, dht11_handle_t);
    DRIVER_DHT11_LINK_BUS_INIT(&gs_handle, dht11_interface_init);
    DRIVER_DHT11_LINK_BUS_DEINIT(&gs_handle, dht11_interface_deinit);
    DRIVER_DHT11_LINK_BUS_READ(&gs_handle, dht11_interface_read);
    DRIVER_DHT11_LINK_BUS_WRITE(&gs_handle, dht11_interface_write);
    DRIVER_DHT11_LINK_DELAY_MS(&gs_handle, dht11_interface_delay_ms);
    DRIVER_DHT11_LINK_DELAY_US(&gs_handle, dht11_interface_delay_us);
    DRIVER_DHT11_LINK_ENABLE_IRQ(&gs_handle, dht11_interface_enable_irq);
    DRIVER_DHT11_LINK_DISABLE_IRQ(&gs_handle, dht11_interface_disable_irq);
    DRIVER_DHT11_LINK_DEBUG_PRINT(&gs_handle, dht11_interface_debug_print);

    /* get dht11 information */
    res = dht11_info(&info);
    if (res != 0)
    {
        dht11_interface_debug_print("dht11: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print dht11 information */
        dht11_interface_debug_print("dht11: chip is %s.\n", info.chip_name);
        dht11_interface_debug_print("dht11: manufacturer is %s.\n", info.manufacturer_name);
        dht11_interface_debug_print("dht11: interface is %s.\n", info.interface);
        dht11_interface_debug_print("dht11: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        dht11_interface_debug_print("dht11: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        dht11_interface_debug_print("dht11: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        dht11_interface_debug_print("dht11: max current is %0.2fmA.\n", info.max_current_ma);
        dht11_interface_debug_print("dht11: max temperature is %0.1fC.\n", info.temperature_max);
        dht11_interface_debug_print("dht11: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start basic read test */
    dht11_interface_debug_print("dht11: start read test.\n");
    
    /* dht11 init */
    res = dht11_init(&gs_handle);
    if (res != 0)
    {
        dht11_interface_debug_print("dht11: init failed.\n");
       
        return 1;
    }
    
    /* delay 2000 ms for read */
    dht11_interface_delay_ms(2000);
    for (i = 0; i < times; i++)
    {
        /* read temperature and humidity */
        res = dht11_read_temperature_humidity(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature, (uint16_t *)&humidity_raw, (uint8_t *)&humidity);
        if (res != 0)
        {
            dht11_interface_debug_print("dht11: read failed.\n");
            (void)dht11_deinit(&gs_handle);
           
            return 1;
        }
    
        /* print result */
        dht11_interface_debug_print("dht11: temperature: %.01fC.\n", temperature);
        dht11_interface_debug_print("dht11: humidity: %d%%.\n", humidity);

        /* delay 2000 ms*/
        dht11_interface_delay_ms(2000);
    }

    /* finish basic read test and exit */
    dht11_interface_debug_print("dht11: finish read test.\n");
    (void)dht11_deinit(&gs_handle);
    
    return 0;
}
