/**
 * @file common.h
 * @author Bastian de Byl (bastian@skudakrennsport.com)
 * @brief This is a header file containing common versions of the C-based
 * firmware source code at Skudak Rennsport
 * @version 0.1
 * @date 2023-06-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SKUDAK_COMMON_H_
#define SKUDAK_COMMON_H_

/**
 * VCU I2C Communication Modes 0-99
 */
/* VCU I2C Info & Status Modes */
#define VCU_I2C_INFO                   (0)   ///< VCU information (version, BMS type, etc.)
#define VCU_I2C_ERR_CODES              (1)   ///< Error codes
#define VCU_I2C_LDU_STATE              (10)  ///< LDU state

/* BMS Data Modes */
#define VCU_I2C_BMS                    (20)  ///< BMS cell voltage data (Tesla/Volt: 192 bytes, VW: 416 bytes)
#define VCU_I2C_BMS_TEMPS              (21)  ///< VW BMS temperature data (48 temps × uint16_t = 96 bytes)
#define VCU_I2C_BMS_MODULE_INFO        (22)  ///< VW BMS module presence (16 modules × uint8_t = 16 bytes)

/**
 * VCU Eerrors 100-254
 */
/* I2C Errors 100-109 */
#define SKUDAK_ERR_I2C_SLAVE_TX      (100)
#define SKUDAK_ERR_I2C_SLAVE_RX      (101)
#define SKUDAK_ERR_I2C_LISTEN        (102)
#define SKUDAK_ERR_I2C_ERR_CBK       (103)
#define SKUDAK_ERR_I2C_SLAVE_TX_CPLT (104)
#define SKUDAK_ERR_I2C_SLAVE_RX_CPLT (105)
// RESERVED 106-108
#define SKUDAK_ERR_I2C_ENABLE        (109)

/* CAN Errors 110-139 */
#define SKUDAK_ERR_CAN1_INIT         (110)
#define SKUDAK_ERR_CAN2_INIT         (111)
#define SKUDAK_ERR_CAN3_INIT         (112)
#define SKUDAK_ERR_CAN1_FILTER       (113)
#define SKUDAK_ERR_CAN2_FILTER       (114)
#define SKUDAK_ERR_CAN3_FILTER       (115)
#define SKUDAK_ERR_CAN1_EN           (116)
#define SKUDAK_ERR_CAN2_EN           (117)
#define SKUDAK_ERR_CAN3_EN           (118)
#define SKUDAK_ERR_CAN1_NOTIFICATION (119)
#define SKUDAK_ERR_CAN2_NOTIFICATION (120)
#define SKUDAK_ERR_CAN3_NOTIFICATION (121)
// RESERVED 122-129
#define SKUDAK_ERR_CAN_RX_FIFO0      (130)
#define SKUDAK_ERR_CAN_RX_FIFO1      (131)
#define SKUDAK_ERR_CAN_RX_MSG        (132)

/* TIM Errors 140-159 */
#define SKUDAK_ERR_TIM1              (140)
#define SKUDAK_ERR_TIM2              (141)
#define SKUDAK_ERR_TIM3              (142)
#define SKUDAK_ERR_TIM4              (143)
#define SKUDAK_ERR_TIM5              (144)
#define SKUDAK_ERR_TIM6              (145)
#define SKUDAK_ERR_TIM7              (146)
#define SKUDAK_ERR_TIM8              (147)
#define SKUDAK_ERR_TIM9              (148)
#define SKUDAK_ERR_TIM10             (149)
#define SKUDAK_ERR_TIM11             (150)
#define SKUDAK_ERR_TIM12             (151)
#define SKUDAK_ERR_TIM13             (152)
// RESERVED 152-159

/* UART Errors 160-169 */
#define SKUDAK_ERR_UART1             (160)
#define SKUDAK_ERR_UART2             (161)
// RESERVED 162-169

/* VCU General Errors 200-249 */
#define SKUDAK_ERR_VCU_INIT          (200)
// RESERVED 201-209
#define SKUDAK_ERR_DCDC              (210)
#define SKUDAK_ERR_BMS1              (211)
#define SKUDAK_ERR_BMS2              (212)

#endif // SKUDAK_COMMON_H_
