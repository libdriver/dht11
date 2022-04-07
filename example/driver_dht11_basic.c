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
 * @file      driver_dht11_basic.c
 * @brief     driver dht11 basic source file
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

#include "driver_dht11_basic.h"

static dht11_handle_t gs_handle;        /**< dht11 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t dht11_basic_init(void)
{
    uint8_t res;
    
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
    
    /* dht11 init */
    res = dht11_init(&gs_handle);
    if (res != 0)
    {
        dht11_interface_debug_print("dht11: init failed.\n");
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *temperature points to a converted temperature buffer
 * @param[out] *humidity points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t dht11_basic_read(float *temperature, uint8_t *humidity)
{
    uint16_t temperature_raw;
    uint16_t humidity_raw;
    
    /* read temperature and humidity */
    if (dht11_read_temperature_humidity(&gs_handle, (uint16_t *)&temperature_raw, temperature, 
                                       (uint16_t *)&humidity_raw, humidity) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t dht11_basic_deinit(void)
{
    /* deinit dht11 and close bus */
    if (dht11_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
