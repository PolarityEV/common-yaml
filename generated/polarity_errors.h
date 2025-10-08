/**
 * @file polarity_errors.h
 * @brief Polarity Error Code Definitions
 * @version 1.0.0
 *
 * AUTO-GENERATED FILE - DO NOT EDIT MANUALLY
 * Generated: 2025-10-08 19:04:24
 * Source: definitions.yaml
 *
 * This file contains error code definitions for Polarity projects.
 * Compatible with: C (STM32, ESP32), C++
 *
 * To regenerate this file, run:
 *   python generate.py
 *
 * @copyright Copyright (c) 2025 Polarity EV
 */

#ifndef POLARITY_ERRORS_H_
#define POLARITY_ERRORS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup ErrorCodes Error Code Definitions
 * @{
 */

/**
 * @name I2C Errors (100-109)
 * @brief I2C communication errors
 * @{
 */
/** I2C slave transmit failed */
#define POLARITY_ERR_I2C_SLAVE_TX      (100)
/** I2C slave receive failed */
#define POLARITY_ERR_I2C_SLAVE_RX      (101)
/** I2C listen mode activation failed */
#define POLARITY_ERR_I2C_LISTEN        (102)
/** I2C error callback triggered */
#define POLARITY_ERR_I2C_ERR_CBK       (103)
/** I2C slave transmit complete with error */
#define POLARITY_ERR_I2C_SLAVE_TX_CPLT (104)
/** I2C slave receive complete with error */
#define POLARITY_ERR_I2C_SLAVE_RX_CPLT (105)
/** I2C enable failed */
#define POLARITY_ERR_I2C_ENABLE        (109)
/** @} */

/**
 * @name CAN Errors (110-139)
 * @brief CAN bus communication errors
 * @{
 */
/** CAN1 initialization failed */
#define POLARITY_ERR_CAN1_INIT         (110)
/** CAN2 initialization failed */
#define POLARITY_ERR_CAN2_INIT         (111)
/** CAN3 initialization failed */
#define POLARITY_ERR_CAN3_INIT         (112)
/** CAN1 filter configuration failed */
#define POLARITY_ERR_CAN1_FILTER       (113)
/** CAN2 filter configuration failed */
#define POLARITY_ERR_CAN2_FILTER       (114)
/** CAN3 filter configuration failed */
#define POLARITY_ERR_CAN3_FILTER       (115)
/** CAN1 enable/start failed */
#define POLARITY_ERR_CAN1_EN           (116)
/** CAN2 enable/start failed */
#define POLARITY_ERR_CAN2_EN           (117)
/** CAN3 enable/start failed */
#define POLARITY_ERR_CAN3_EN           (118)
/** CAN1 notification activation failed */
#define POLARITY_ERR_CAN1_NOTIFICATION (119)
/** CAN2 notification activation failed */
#define POLARITY_ERR_CAN2_NOTIFICATION (120)
/** CAN3 notification activation failed */
#define POLARITY_ERR_CAN3_NOTIFICATION (121)
/** CAN RX FIFO0 error */
#define POLARITY_ERR_CAN_RX_FIFO0      (130)
/** CAN RX FIFO1 error */
#define POLARITY_ERR_CAN_RX_FIFO1      (131)
/** CAN receive message failed */
#define POLARITY_ERR_CAN_RX_MSG        (132)
/** @} */

/**
 * @name TIM Errors (140-159)
 * @brief Timer peripheral errors
 * @{
 */
/** Timer 1 operation failed */
#define POLARITY_ERR_TIM1              (140)
/** Timer 2 operation failed */
#define POLARITY_ERR_TIM2              (141)
/** Timer 3 operation failed */
#define POLARITY_ERR_TIM3              (142)
/** Timer 4 operation failed */
#define POLARITY_ERR_TIM4              (143)
/** Timer 5 operation failed */
#define POLARITY_ERR_TIM5              (144)
/** Timer 6 operation failed */
#define POLARITY_ERR_TIM6              (145)
/** Timer 7 operation failed */
#define POLARITY_ERR_TIM7              (146)
/** Timer 8 operation failed */
#define POLARITY_ERR_TIM8              (147)
/** Timer 9 operation failed */
#define POLARITY_ERR_TIM9              (148)
/** Timer 10 operation failed */
#define POLARITY_ERR_TIM10             (149)
/** Timer 11 operation failed */
#define POLARITY_ERR_TIM11             (150)
/** Timer 12 operation failed */
#define POLARITY_ERR_TIM12             (151)
/** Timer 13 operation failed */
#define POLARITY_ERR_TIM13             (152)
/** @} */

/**
 * @name UART Errors (160-169)
 * @brief UART serial communication errors
 * @{
 */
/** UART1 operation failed */
#define POLARITY_ERR_UART1             (160)
/** UART2 operation failed */
#define POLARITY_ERR_UART2             (161)
/** @} */

/**
 * @name VCU_GENERAL Errors (200-249)
 * @brief VCU general system errors
 * @{
 */
/** VCU initialization failed */
#define POLARITY_ERR_VCU_INIT          (200)
/** DC-DC converter error */
#define POLARITY_ERR_DCDC              (210)
/** BMS1 communication or fault */
#define POLARITY_ERR_BMS1              (211)
/** BMS2 communication or fault */
#define POLARITY_ERR_BMS2              (212)
/** @} */

/** @} */ // End of ErrorCodes group

/*
 * Backward Compatibility Aliases (DEPRECATED)
 *
 * These aliases maintain compatibility with legacy code using SKUDAK_ERR_* naming.
 * New code should use POLARITY_ERR_* constants.
 *
 * These will be removed in a future version.
 */
#ifdef POLARITY_ENABLE_LEGACY_NAMES
#define SKUDAK_ERR_I2C_SLAVE_TX                 POLARITY_ERR_I2C_SLAVE_TX
#define SKUDAK_ERR_I2C_SLAVE_RX                 POLARITY_ERR_I2C_SLAVE_RX
#define SKUDAK_ERR_I2C_LISTEN                   POLARITY_ERR_I2C_LISTEN
#define SKUDAK_ERR_I2C_ERR_CBK                  POLARITY_ERR_I2C_ERR_CBK
#define SKUDAK_ERR_I2C_SLAVE_TX_CPLT            POLARITY_ERR_I2C_SLAVE_TX_CPLT
#define SKUDAK_ERR_I2C_SLAVE_RX_CPLT            POLARITY_ERR_I2C_SLAVE_RX_CPLT
#define SKUDAK_ERR_I2C_ENABLE                   POLARITY_ERR_I2C_ENABLE
#define SKUDAK_ERR_CAN1_INIT                    POLARITY_ERR_CAN1_INIT
#define SKUDAK_ERR_CAN2_INIT                    POLARITY_ERR_CAN2_INIT
#define SKUDAK_ERR_CAN3_INIT                    POLARITY_ERR_CAN3_INIT
#define SKUDAK_ERR_CAN1_FILTER                  POLARITY_ERR_CAN1_FILTER
#define SKUDAK_ERR_CAN2_FILTER                  POLARITY_ERR_CAN2_FILTER
#define SKUDAK_ERR_CAN3_FILTER                  POLARITY_ERR_CAN3_FILTER
#define SKUDAK_ERR_CAN1_EN                      POLARITY_ERR_CAN1_EN
#define SKUDAK_ERR_CAN2_EN                      POLARITY_ERR_CAN2_EN
#define SKUDAK_ERR_CAN3_EN                      POLARITY_ERR_CAN3_EN
#define SKUDAK_ERR_CAN1_NOTIFICATION            POLARITY_ERR_CAN1_NOTIFICATION
#define SKUDAK_ERR_CAN2_NOTIFICATION            POLARITY_ERR_CAN2_NOTIFICATION
#define SKUDAK_ERR_CAN3_NOTIFICATION            POLARITY_ERR_CAN3_NOTIFICATION
#define SKUDAK_ERR_CAN_RX_FIFO0                 POLARITY_ERR_CAN_RX_FIFO0
#define SKUDAK_ERR_CAN_RX_FIFO1                 POLARITY_ERR_CAN_RX_FIFO1
#define SKUDAK_ERR_CAN_RX_MSG                   POLARITY_ERR_CAN_RX_MSG
#define SKUDAK_ERR_TIM1                         POLARITY_ERR_TIM1
#define SKUDAK_ERR_TIM2                         POLARITY_ERR_TIM2
#define SKUDAK_ERR_TIM3                         POLARITY_ERR_TIM3
#define SKUDAK_ERR_TIM4                         POLARITY_ERR_TIM4
#define SKUDAK_ERR_TIM5                         POLARITY_ERR_TIM5
#define SKUDAK_ERR_TIM6                         POLARITY_ERR_TIM6
#define SKUDAK_ERR_TIM7                         POLARITY_ERR_TIM7
#define SKUDAK_ERR_TIM8                         POLARITY_ERR_TIM8
#define SKUDAK_ERR_TIM9                         POLARITY_ERR_TIM9
#define SKUDAK_ERR_TIM10                        POLARITY_ERR_TIM10
#define SKUDAK_ERR_TIM11                        POLARITY_ERR_TIM11
#define SKUDAK_ERR_TIM12                        POLARITY_ERR_TIM12
#define SKUDAK_ERR_TIM13                        POLARITY_ERR_TIM13
#define SKUDAK_ERR_UART1                        POLARITY_ERR_UART1
#define SKUDAK_ERR_UART2                        POLARITY_ERR_UART2
#define SKUDAK_ERR_VCU_INIT                     POLARITY_ERR_VCU_INIT
#define SKUDAK_ERR_DCDC                         POLARITY_ERR_DCDC
#define SKUDAK_ERR_BMS1                         POLARITY_ERR_BMS1
#define SKUDAK_ERR_BMS2                         POLARITY_ERR_BMS2
#endif /* POLARITY_ENABLE_LEGACY_NAMES */

#ifdef __cplusplus
}
#endif

#endif /* POLARITY_ERRORS_H_ */