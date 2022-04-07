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
 * @file      driver_dht11.h
 * @brief     driver dht11 header file
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

#ifndef DRIVER_DHT11_H
#define DRIVER_DHT11_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup dht11_driver dht11 driver function
 * @brief    dht11 driver modules
 * @{
 */

/**
 * @addtogroup dht11_base_driver
 * @{
 */

/**
 * @brief dht11 handle structure definition
 */
typedef struct dht11_handle_s
{
    uint8_t (*bus_init)(void);                              /**< point to a bus_init function address */
    uint8_t (*bus_read)(uint8_t *value);                    /**< point to a bus_read function address */
    uint8_t (*bus_write)(uint8_t value);                    /**< point to a bus_write function address */
    uint8_t (*bus_deinit)(void);                            /**< point to a bus_deinit function address */
    void (*delay_ms)(uint32_t ms);                          /**< point to a delay_ms function address */
    void (*delay_us)(uint32_t us);                          /**< point to a delay_us function address */
    void (*enable_irq)(void);                               /**< point to a enable_irq function address */
    void (*disable_irq)(void);                              /**< point to a disable_irq function address */
    void (*debug_print)(const char *const fmt, ...);        /**< point to a debug_print function address */
    uint8_t inited;                                         /**< inited flag */
} dht11_handle_t;

/**
 * @brief dht11 info structure definition
 */
typedef struct dht11_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} dht11_info_t;

/**
 * @}
 */

/**
 * @defgroup dht11_link_driver dht11 link driver function
 * @brief    dht11 link driver modules
 * @ingroup  dht11_driver
 * @{
 */

/**
 * @brief     initialize dht11_handle_t structure
 * @param[in] HANDLE points to a dht11 handle structure
 * @param[in] STRUCTURE is dht11_handle_t
 * @note      none
 */
#define DRIVER_DHT11_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link bus_init function
 * @param[in] HANDLE points to a dht11 handle structure
 * @param[in] FUC points to a bus_init function address
 * @note      none
 */
#define DRIVER_DHT11_LINK_BUS_INIT(HANDLE, FUC)    (HANDLE)->bus_init = FUC

/**
 * @brief     link bus_deinit function
 * @param[in] HANDLE points to a dht11 handle structure
 * @param[in] FUC points to a bus_deinit function address
 * @note      none
 */
#define DRIVER_DHT11_LINK_BUS_DEINIT(HANDLE, FUC)  (HANDLE)->bus_deinit = FUC

/**
 * @brief     link bus_read function
 * @param[in] HANDLE points to a dht11 handle structure
 * @param[in] FUC points to a bus_read function address
 * @note      none
 */
#define DRIVER_DHT11_LINK_BUS_READ(HANDLE, FUC)    (HANDLE)->bus_read = FUC

/**
 * @brief     link bus_write function
 * @param[in] HANDLE points to a dht11 handle structure
 * @param[in] FUC points to a bus_write function address
 * @note      none
 */
#define DRIVER_DHT11_LINK_BUS_WRITE(HANDLE, FUC)   (HANDLE)->bus_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a dht11 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_DHT11_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link delay_us function
 * @param[in] HANDLE points to a dht11 handle structure
 * @param[in] FUC points to a delay_us function address
 * @note      none
 */
#define DRIVER_DHT11_LINK_DELAY_US(HANDLE, FUC)    (HANDLE)->delay_us = FUC

/**
 * @brief     link enable_irq function
 * @param[in] HANDLE points to a dht11 handle structure
 * @param[in] FUC points to a enable_irq function address
 * @note      none
 */
#define DRIVER_DHT11_LINK_ENABLE_IRQ(HANDLE, FUC)  (HANDLE)->enable_irq = FUC

/**
 * @brief     link disable_irq function
 * @param[in] HANDLE points to a dht11 handle structure
 * @param[in] FUC points to a disable_irq function address
 * @note      none
 */
#define DRIVER_DHT11_LINK_DISABLE_IRQ(HANDLE, FUC) (HANDLE)->disable_irq = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a dht11 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_DHT11_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup dht11_base_driver dht11 base driver function
 * @brief    dht11 base driver modules
 * @ingroup  dht11_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a dht11 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t dht11_info(dht11_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a dht11 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 bus initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 * @note      none
 */
uint8_t dht11_init(dht11_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a dht11 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 bus deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t dht11_deinit(dht11_handle_t *handle);

/**
 * @brief      read the temperature and humidity data
 * @param[in]  *handle points to a dht11 handle structure
 * @param[out] *temperature_raw points to a raw temperature buffer
 * @param[out] *temperature_s points to a converted temperature buffer
 * @param[out] *humidity_raw points to a raw humidity buffer
 * @param[out] *humidity_s points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t dht11_read_temperature_humidity(dht11_handle_t *handle, uint16_t *temperature_raw, float *temperature_s,
                                        uint16_t *humidity_raw, uint8_t *humidity_s);

/**
 * @brief      read the humidity data
 * @param[in]  *handle points to a dht11 handle structure
 * @param[out] *raw points to a raw humidity buffer
 * @param[out] *s points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t dht11_read_humidity(dht11_handle_t *handle, uint16_t *raw, uint8_t *s);

/**
 * @brief      read the temperature data
 * @param[in]  *handle points to a dht11 handle structure
 * @param[out] *raw points to a raw temperature buffer
 * @param[out] *s points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t dht11_read_temperature(dht11_handle_t *handle, uint16_t *raw, float *s);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
