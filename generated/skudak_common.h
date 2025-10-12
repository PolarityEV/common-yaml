/**
 * @file skudak_common.h
 * @author Bastian de Byl (bastian@polarity.com)
 * @brief I2C protocol constants for VCU communication
 * @version 1.2.0
 * @date 2025-10-11
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
#define VCU_I2C_VW_BMS_DEBUG           (0x0B)  ///< VW BMS diagnostics (12 bytes: CAN RX count, cell update count, temp update count)

/**
 * For VCU error codes, include polarity_errors.h:
 *
 * #define POLARITY_ENABLE_LEGACY_NAMES  // Optional: enables SKUDAK_ERR_* aliases
 * #include "polarity_errors.h"
 */

#endif /* SKUDAK_COMMON_H_ */
