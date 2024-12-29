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
 * @file      driver_dht11.c
 * @brief     driver dht11 source file
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

#include "driver_dht11.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                "ASAIR DHT11"         /**< chip name */
#define MANUFACTURER_NAME        "ASAIR"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN       3.3f                  /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX       5.5f                  /**< chip max supply voltage */
#define MAX_CURRENT              1.0f                  /**< chip max current */
#define TEMPERATURE_MIN          -20.0f                /**< chip min operating temperature */
#define TEMPERATURE_MAX          60.0f                 /**< chip max operating temperature */
#define DRIVER_VERSION           2000                  /**< driver version */

/**
 * @brief     reset the chip
 * @param[in] *handle pointer to a dht11 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 no response
 * @note      none
 */
static uint8_t a_dht11_reset(dht11_handle_t *handle)
{
    uint8_t retry = 0;
    uint8_t res;
    uint8_t value;
    
    res = handle->bus_write(0);                                      /* set low */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("dht11: bus write 0 failed.\n");         /* write failed */
        
        return 1;                                                    /* return error */
    }
    handle->delay_ms(20);                                            /* wait 20ms */
    handle->disable_irq();                                           /* disable interrupt */
    res = handle->bus_write(1);                                      /* set high */
    if (res != 0)                                                    /* check result */
    {
        handle->enable_irq();                                        /* enable interrupt */
        handle->debug_print("dht11: bus write 1 failed.\n");         /* write failed */
        
        return 1;                                                    /* return error */
    }
    handle->delay_us(30);                                            /* wait 20-40us */
    res = handle->bus_read((uint8_t *)&value);                       /* read 1 bit */
    if (res != 0)                                                    /* check result */
    {
        handle->enable_irq();                                        /* enable interrupt */
        handle->debug_print("dht11: bus read failed.\n");            /* read failed */
        
        return 1;                                                    /* return error */
    }
    while ((value != 0) && (retry < 100))                            /* wait 40-80us */
    {
        res = handle->bus_read((uint8_t *)&value);                   /* read 1 bit */
        if (res != 0)                                                /* check result */
        {
            handle->enable_irq();                                    /* enable interrupt */
            handle->debug_print("dht11: bus read failed.\n");        /* read failed */
            
            return 1;                                                /* return error */
        }
        retry++;                                                     /* retry times++ */
        handle->delay_us(1);                                         /* delay 1us */
    }
    if (retry >= 100)                                                /* if retry times is over 100 times */
    {
        handle->enable_irq();                                        /* enable interrupt */
        handle->debug_print("dht11: bus no response.\n");            /* no response */
        
        return 1;                                                    /* return error */
    }
    else
    {
        retry = 0;                                                   /* reset retry times */
    }
    res = handle->bus_read((uint8_t *)&value);                       /* read 1 bit */
    if (res != 0)                                                    /* check result */
    {
        handle->enable_irq();                                        /* enable interrupt */
        handle->debug_print("dht11: bus read failed.\n");            /* read failed */
        
        return 1;                                                    /* return error */
    }
    while ((!value) && (retry < 100))                                /* wait for 40-80us */
    {
        res = handle->bus_read((uint8_t *)&value);                   /* read 1 bit */
        if (res != 0)                                                /* check result */
        {
            handle->enable_irq();                                    /* enable interrupt */
            handle->debug_print("dht11: bus read failed.\n");        /* read failed */
            
            return 1;                                                /* return error */
        }
        retry++;                                                     /* retry times++ */
        handle->delay_us(1);                                         /* delay 1 us */
    }
    if (retry >= 100)                                                /* if retry times is over 100 times */
    { 
        handle->enable_irq();                                        /* enable interrupt */
        handle->debug_print("dht11: bus no response.\n");            /* no response */
        
        return 1;                                                    /* return error */
    }
    handle->enable_irq();                                            /* enable interrupt */
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      read one bit
 * @param[in]  *handle pointer to a dht11 handle structure
 * @param[out] *value pointer to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_dht11_read_bit(dht11_handle_t *handle, uint8_t *value)
{
    uint8_t retry = 0;
    uint8_t res;
    
    res = handle->bus_read((uint8_t *)value);                        /* read 1 bit */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("dht11: bus read failed.\n");            /* read failed */
        
        return 1;                                                    /* return error */
    }
    while (((*value) != 0) && (retry < 100))                         /* wait 100us */
    {
        res = handle->bus_read((uint8_t *)value);                    /* read 1 bit */
        if (res != 0)                                                /* check result */
        {
            handle->debug_print("dht11: bus read failed.\n");        /* read failed */
            
            return 1;                                                /* return error */
        }
        retry++;                                                     /* retry times++ */
        handle->delay_us(1);                                         /* delay 1 us */
    }
    retry = 0;                                                       /* reset retry times */
    res = handle->bus_read((uint8_t *)value);                        /* read 1 bit */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("dht11: bus read failed.\n");            /* read failed */
        
        return 1;                                                    /* return error */
    }
    while ((!(*value)) && (retry < 100))                             /* wait 100us */
    {
        res = handle->bus_read((uint8_t *)value);                    /* read 1 bit */
        if (res != 0)                                                /* check result */
        {
            handle->debug_print("dht11: bus read failed.\n");        /* read failed */
            
            return 1;                                                /* return error */
        }
        retry++;                                                     /* retry times++ */
        handle->delay_us(1);                                         /* wait 1 us */
    }
    handle->delay_us(40);                                            /* wait 40us */
    res = handle->bus_read((uint8_t *)value);                        /* read 1 bit */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("dht11: bus read failed.\n");            /* read failed */
        
        return 1;                                                    /* return error */
    }
    else
    {
        return 0;                                                    /* success return 0 */
    }
}

/**
 * @brief      read one byte
 * @param[in]  *handle pointer to a dht11 handle structure
 * @param[out] *byte pointer to a byte buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_dht11_read_byte(dht11_handle_t *handle, uint8_t *byte)
{
    uint8_t i;
    uint8_t res;
    uint8_t value;
    
    *byte = 0;                                                       /* set byte 0 */
    for (i = 0; i < 8; i++)                                          /* read 8 bits */
    {
        *byte <<= 1;                                                 /* left shift 1 bit */
        res = a_dht11_read_bit(handle, (uint8_t *)&value);           /* read 1 bit */
        if (res != 0)                                                /* check result */
        {
            handle->debug_print("dht11: bus read failed.\n");        /* read failed */
            
            return 1;                                                /* return error */
        }
        *byte |= value;                                              /* set LSB */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      read the humidity data
 * @param[in]  *handle pointer to a dht11 handle structure
 * @param[out] *raw pointer to a raw humidity buffer
 * @param[out] *s pointer to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t dht11_read_humidity(dht11_handle_t *handle, uint16_t *raw, uint8_t *s)
{
    uint8_t buf[5];
    uint8_t i;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    if (a_dht11_reset(handle) == 0)                                       /* reset the chip */
    {
        handle->disable_irq();                                            /* disable interrupt */
        for (i = 0; i < 5; i++)                                           /* read 5 bytes */
        {
            if (a_dht11_read_byte(handle, (uint8_t *)&buf[i]) != 0)       /* read each byte */
            {
                handle->enable_irq();                                     /* enable interrupt */
                handle->debug_print("dht11: read byte failed.\n");        /* read failed */
                
                return 1;                                                 /* return error */
            }
        }
        handle->enable_irq();                                             /* enable interrupt */
        if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])                /* calculate checksum */
        {
            *raw = (uint16_t)buf[0] << 8 | buf[1];                        /* get raw data */
            *s = buf[0];                                                  /* convert raw data to real data */
            
            return 0;                                                     /* success return 0 */
        }
        else
        {
            handle->debug_print("dht11: data check failed.\n");           /* checksum error */
            
            return 1;                                                     /* return error */
        }
    }
    else
    {
        handle->debug_print("dht11: reset failed.\n");                    /* reset failed */
        
        return 1;                                                         /* return error */
    }
}

/**
 * @brief      read the temperature and humidity data
 * @param[in]  *handle pointer to a dht11 handle structure
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_s pointer to a converted temperature buffer
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_s pointer to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t dht11_read_temperature_humidity(dht11_handle_t *handle, uint16_t *temperature_raw, float *temperature_s,
                                        uint16_t *humidity_raw, uint8_t *humidity_s)
{
    uint8_t buf[5];
    uint8_t i;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (a_dht11_reset(handle) == 0)                                             /* reset the chip */
    {
        handle->disable_irq();                                                  /* disable interrupt */
        for (i = 0; i < 5; i++)                                                 /* read 5 bytes */
        {
            if (a_dht11_read_byte(handle, (uint8_t *)&buf[i]) != 0)             /* read each byte */
            {
                handle->enable_irq();                                           /* enable interrupt */
                handle->debug_print("dht11: read byte failed.\n");              /* read failed */
                
                return 1;                                                       /* return error */
            }
        }
        handle->enable_irq();                                                   /* enable interrupt */
        if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])                      /* calculate checksum */
        {
            if (buf[3] > 127)                                                   /* if temperature is below zero */
            {
                *temperature_raw = (uint16_t)buf[2] << 8 | buf[3];              /* get temperature raw data */
                *temperature_s= (float)(-(buf[2] * 10 + 
                                 (buf[3] & ~(1<<7)))) / 10.0f;                  /* convert temperature raw data to temperature real data */
            }
            else
            {
                *temperature_raw = (uint16_t)buf[2] << 8 | buf[3];              /* get temperature raw data */
                *temperature_s= (float)(buf[2]*10 + buf[3]) / 10.0f;            /* convert temperature raw data to temperature real data */
            }
            *humidity_raw = (uint16_t)buf[0] << 8 | buf[1];                     /* get humidity raw */
            *humidity_s = buf[0];                                               /* convert humidity raw data to real data */
            
            return 0;                                                           /* success return 0 */
        }
        else
        {
            handle->debug_print("dht11: data check failed.\n");                 /* checksum error */
            
            return 1;                                                           /* return error */
        }
    }
    else
    {
        handle->debug_print("dht11: reset failed.\n");                          /* reset failed */
        
        return 1;                                                               /* return error */
    }
}

/**
 * @brief      read the temperature data
 * @param[in]  *handle pointer to a dht11 handle structure
 * @param[out] *raw pointer to a raw temperature buffer
 * @param[out] *s pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t dht11_read_temperature(dht11_handle_t *handle, uint16_t *raw, float *s)
{
    uint8_t buf[5];
    uint8_t i;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    if (a_dht11_reset(handle) == 0)                                       /* reset the chip */
    {
        handle->disable_irq();                                            /* disable interrupt */
        for (i = 0; i < 5; i++)                                           /* read 5 bytes */
        {
            if (a_dht11_read_byte(handle, (uint8_t *)&buf[i]) != 0)       /* read each byte */
            {
                handle->enable_irq();                                     /* enable interrupt */
                handle->debug_print("dht11: read byte failed.\n");        /* read failed */
                
                return 1;                                                 /* return error */
            }
        }
        handle->enable_irq();                                             /* enable interrupt */
        if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])                /* calculate checksum */
        {
            if (buf[3] > 127)                                             /* if temperature is below zero */
            {
                *raw = (uint16_t)buf[2] << 8 | buf[3];                    /* get temperature raw data */
                *s= (float)(-(buf[2] * 10 + (buf[3] & ~(1<<7)))) / 10.0f; /* convert temperature raw data to temperature real data */
            }
            else
            {
                *raw = (uint16_t)buf[2] << 8 | buf[3];                    /* get temperature raw data */
                *s= (float)(buf[2] * 10 + buf[3]) / 10.0f;                /* convert temperature raw data to temperature real data */
            }
            
            return 0;                                                     /* success return 0 */
        }
        else
        {
            handle->debug_print("dht11: data check failed.\n");           /* checksum error */
            
            return 1;                                                     /* return error */
        }
    }
    else
    {
        handle->debug_print("dht11: reset failed.\n");                    /* reset failed */
        
        return 1;                                                         /* return error */
    }
}

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a dht11 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 bus initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 * @note      none
 */
uint8_t dht11_init(dht11_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                 /* check debug_print */
    {
        return 3;                                                    /* return error */
    }
    if (handle->bus_init == NULL)                                    /* check bus_init */
    {
        handle->debug_print("dht11: bus_init is null.\n");           /* bus_init is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->bus_deinit == NULL)                                  /* check bus_deinit */
    {
        handle->debug_print("dht11: bus_deinit is null.\n");         /* bus_deinit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->bus_read == NULL)                                    /* check bus_read */
    {
        handle->debug_print("dht11: bus_read is null.\n");           /* bus_read is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->bus_write == NULL)                                   /* check bus_write */
    {
        handle->debug_print("dht11: bus_write is null.\n");          /* bus_write is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                    /* check delay_ms */
    {
        handle->debug_print("dht11: delay_ms is null.\n");           /* delay_ms is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->delay_us == NULL)                                    /* check delay_us */
    {
        handle->debug_print("dht11: delay_us is null.\n");           /* delay_us is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->enable_irq == NULL)                                  /* check enable_irq */
    {
        handle->debug_print("dht11: enable_irq is null.\n");         /* enable_irq is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->disable_irq == NULL)                                 /* check disable_irq */
    {
        handle->debug_print("dht11: disable_irq is null.\n");        /* disable_irq is null */
        
        return 3;                                                    /* return error */
    }
    
    if (handle->bus_init() != 0)                                     /* initialize bus */
    {
        handle->debug_print("dht11: bus init failed.\n");            /* bus init failed */
        
        return 1;                                                    /* return error */
    }
    if (a_dht11_reset(handle) != 0)                                  /* reset the chip */
    {
        handle->debug_print("dht11: reset failed.\n");               /* reset failed */
        (void)handle->bus_deinit();                                  /* close bus */
        
        return 4;                                                    /* return error */
    }
    handle->inited = 1;                                              /* flag finish initialization */
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a dht11 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 bus deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t dht11_deinit(dht11_handle_t *handle)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }
    
    if (handle->bus_deinit() != 0)                             /* close bus */
    {
        handle->debug_print("dht11: deinit failed.\n");        /* deinit failed */
        
        return 1;                                              /* return error */
    }   
    handle->inited = 0;                                        /* flag close */
    
    return 0;                                                  /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a dht11 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t dht11_info(dht11_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(dht11_info_t));                          /* initialize dht11 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "GPIO", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
