/******************************************************************************
* File Name:   bt_utils.h
*
* Description: This file is the public interface of bt_utils.c
*
* Related Document: See README.md
*
*******************************************************************************
* Copyright 2021-2022, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
 * Include guard
 ******************************************************************************/
#ifndef BT_UTILS_H_
#define BT_UTILS_H_

/*******************************************************************************
 * Header file includes
 ******************************************************************************/
#include "mtb_kvstore.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define FLASH_MEMORY_START     0x200
#define FLASH_MEMORY_END       0x800

/*******************************************************************************
 * Function Prototype
 ******************************************************************************/
cy_rslt_t flash_memory_init(void);
uint32_t flash_memory_write(uint16_t config_item_id, uint32_t len, uint8_t* buf);
uint32_t flash_memory_read(uint16_t config_item_id, uint32_t len, uint8_t* buf);
uint32_t flash_memory_delete(uint16_t config_item_id);
uint32_t flash_memory_reset(void);

extern mtb_kvstore_t kv_store_obj;

#endif /* BT_UTILS_H_ */
