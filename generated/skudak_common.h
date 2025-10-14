/**
 * @file skudak_common.h
 * @author Bastian de Byl (bastian@polarity.com)
 * @brief I2C protocol constants for VCU communication
 * @version 1.4.0
 * @date 2025-10-13
 *
 * @copyright Copyright (c) 2025 Polarity EV
 *
 * NOTE: This file contains I2C protocol constants only.
 * Error codes have been moved to polarity_errors.h (generated from definitions.yaml)
 */

#ifndef SKUDAK_COMMON_H_
#define SKUDAK_COMMON_H_

/**
 * VCU I2C Communication Modes
 *
 * These command codes define the I2C protocol between STM32 VCU (slave) and ESP32 Gateway (master).
 * Protocol specification: docs/I2C_PROTOCOL.md
 *
 * IMPORTANT: STM32 VCU firmware is the source of truth for this protocol.
 * ESP32 and Flutter implementations must match STM32's actual implementation.
 */

/* VCU I2C Info & Status Modes */
#define VCU_I2C_INFO                   (0x01)  ///< VCU version and BMS type (4 bytes: major, minor, patch, bms_type)
#define VCU_I2C_LDU_STATE              (0x02)  ///< LDU state (7 bytes: amperage, voltage, motor temp, dcdc temp, direction)

/* BMS Data Modes */
#define VCU_I2C_BMS                    (0x04)  ///< BMS cell voltage data (Tesla/Volt: 192 bytes, VW: 416 bytes)
#define VCU_I2C_BMS_TEMPS              (0x05)  ///< VW BMS temperature data (48 temps × uint16_t = 96 bytes)
#define VCU_I2C_BMS_MODULE_INFO        (0x06)  ///< VW BMS module presence (16 modules × uint8_t = 16 bytes)

/* VCU Diagnostics & Extended Modes */
#define VCU_I2C_ERR_CODES_V2           (0x07)  ///< Error codes v2 (1-32 bytes: error count + error code array)
#define VCU_I2C_BMS_SUMMARY            (0x08)  ///< BMS voltage summary (10 bytes: min, max, delta, sum voltages)
#define VCU_I2C_SYSTEM_STATUS          (0x09)  ///< System status (8 bytes: VCU state, BMS state, ignition, charging, run, RPM)
#define VCU_I2C_LDU_EXT                (0x0A)  ///< Extended LDU info (4 bytes: heatsink temp, water pump duty)
#define VCU_I2C_BMS_DIAGNOSTICS        (0x0B)  ///< BMS diagnostics - all types (12 bytes: VW=[can_rx, cell_upd, temp_upd], TESLA=[can_rx, cell_upd, reserved], VOLT2=[can1_rx, can3_rx, cell_upd])
#define VCU_I2C_VW_BMS_DEBUG           VCU_I2C_BMS_DIAGNOSTICS  ///< Legacy alias (deprecated, use VCU_I2C_BMS_DIAGNOSTICS)

/* Charger Control & Monitoring Modes */
#define VCU_I2C_CHARGER_CONTROL        (0x0C)  ///< Charger control (WRITE: 6 bytes total [command + 5 data]; RESPONSE: 1 byte: 0=OK, 1=Error) [Implemented v0.3.1+]
#define VCU_I2C_CHARGER1_OBC           (0x0D)  ///< Charger 1 OBC state (CAN1 bus) (READ: 16 bytes: voltage, current, status flags, temperature, timeout)
#define VCU_I2C_CHARGER1_DCDC          (0x0E)  ///< Charger 1 DCDC state (CAN1 bus) (READ: 16 bytes: fault flags, output current, output voltage, output status, temperature, timeout)
#define VCU_I2C_CHARGER2_OBC           (0x0F)  ///< Charger 2 OBC state (CAN3 bus) (READ: 16 bytes: same format as CHARGER1_OBC)
#define VCU_I2C_CHARGER2_DCDC          (0x10)  ///< Charger 2 DCDC state (CAN3 bus) (READ: 16 bytes: same format as CHARGER1_DCDC)

/**
 * For VCU error codes, include polarity_errors.h:
 *
 * #define POLARITY_ENABLE_LEGACY_NAMES  // Optional: enables SKUDAK_ERR_* aliases
 * #include "polarity_errors.h"
 */

#endif /* SKUDAK_COMMON_H_ */
