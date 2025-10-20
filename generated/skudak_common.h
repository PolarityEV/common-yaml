/**
 * @file skudak_common.h
 * @author Bastian de Byl (bastian@polarity.com)
 * @brief I2C protocol constants for VCU communication
 * @version 10.0.0
 * @date 2025-10-19
 *
 * @copyright Copyright (c) 2025 Polarity EV
 *
 * NOTE: This file contains I2C protocol constants only.
 * Error codes have been moved to polarity_errors.h (generated from definitions.yaml)
 *
 * ⚠️ PROTOCOL v10.0 BREAKING CHANGES (2025-10-19):
 * - Dual-address mode: 0x48 (READ commands), 0x49 (WRITE commands)
 * - REMOVED: VCU_I2C_CHARGER_CONTROL (0x0C) and VCU_I2C_DIAGNOSTIC_CONTROL (0x14)
 * - NEW: VCU_I2C_WRITE_CHARGER_CONTROL (0x01 on 0x49) - 12-byte payload
 * - NEW: VCU_I2C_WRITE_DIAGNOSTIC_CONTROL (0x00 on 0x49) - 12-byte payload
 * - ESP32 firmware update REQUIRED
 */

#ifndef SKUDAK_COMMON_H_
#define SKUDAK_COMMON_H_

/**
 * VCU I2C Communication Modes - Protocol v10.0
 *
 * These command codes define the I2C protocol between STM32 VCU (slave) and ESP32 Gateway (master).
 * Protocol specification: docs/I2C_PROTOCOL.md
 *
 * IMPORTANT: STM32 VCU firmware is the source of truth for this protocol.
 * ESP32 and Flutter implementations must match STM32's actual implementation.
 *
 * DUAL-ADDRESS MODE (v10.0):
 * - 0x48 (READ address): Read-only commands (0x01-0x16, excluding 0x0C and 0x14)
 * - 0x49 (WRITE address): Write commands (0x00, 0x01 with 12-byte fixed payload)
 */

/* VCU I2C Info & Status Modes */
#define VCU_I2C_INFO                   (0x01)  ///< VCU version and BMS type (4 bytes: major, minor, patch, bms_type)
#define VCU_I2C_LDU_STATE              (0x02)  ///< LDU state (7 bytes: amperage, voltage, motor temp, dcdc temp, direction)

/* BMS Data Modes */
#define VCU_I2C_BMS                    (0x04)  ///< BMS cell voltage data (Tesla/Volt: 192 bytes, VW: 416 bytes)
#define VCU_I2C_BMS_TEMPS              (0x05)  ///< VW BMS temperature data (48 temps × uint16_t = 96 bytes)
#define VCU_I2C_BMS_MODULE_INFO        (0x06)  ///< VW BMS module presence (16 modules × uint8_t = 16 bytes)

/* VCU Diagnostics & Extended Modes */
// 0x07 - RESERVED (removed v6.2.0: error count now calculated by ESP32 from payload)
#define VCU_I2C_BMS_SUMMARY            (0x08)  ///< BMS voltage summary (10 bytes: min, max, delta, sum voltages)
#define VCU_I2C_SYSTEM_STATUS          (0x09)  ///< System status (8 bytes: VCU state, BMS state, ignition, charging, run, RPM)
#define VCU_I2C_LDU_EXT                (0x0A)  ///< Extended LDU info (4 bytes: heatsink temp, water pump duty)
#define VCU_I2C_BMS_DIAGNOSTICS        (0x0B)  ///< BMS diagnostics - all types (12 bytes: VW=[can_rx, cell_upd, temp_upd], TESLA=[can_rx, cell_upd, reserved], VOLT2=[can1_rx, can3_rx, cell_upd])
#define VCU_I2C_VW_BMS_DEBUG           VCU_I2C_BMS_DIAGNOSTICS  ///< Legacy alias (deprecated, use VCU_I2C_BMS_DIAGNOSTICS)

/* Charger Control & Monitoring Modes */
// 0x0C REMOVED in v10.0 - Use VCU_I2C_WRITE_CHARGER_CONTROL (0x01 on 0x49 address)
#define VCU_I2C_CHARGER1_OBC           (0x0D)  ///< Charger 1 OBC state (CAN2 bus) (READ: 16 bytes: voltage, current, status flags, temperature, timeout)
#define VCU_I2C_CHARGER1_DCDC          (0x0E)  ///< Charger 1 DCDC state (CAN2 bus) (READ: 16 bytes: fault flags, output current, output voltage, output status, temperature, timeout)
#define VCU_I2C_CHARGER2_OBC           (0x0F)  ///< Charger 2 OBC state (CAN3 bus) (READ: 16 bytes: same format as CHARGER1_OBC)
#define VCU_I2C_CHARGER2_DCDC          (0x10)  ///< Charger 2 DCDC state (CAN3 bus) (READ: 16 bytes: same format as CHARGER1_DCDC)

/* Current Sensor Monitoring Modes */
#define VCU_I2C_CURRENT_SENSOR1        (0x11)  ///< Current Sensor 1 state (CAN3 0x3C4) (READ: 16 bytes: current_mA[4], current_A[2], status, sw_ver, timeout, reserved[7]) [Implemented v0.4.0+]
#define VCU_I2C_CURRENT_SENSOR2        (0x12)  ///< Current Sensor 2 state (CAN3 0x3C5) (READ: 16 bytes: reserved for future use)
#define VCU_I2C_CURRENT_SENSOR3        (0x13)  ///< Current Sensor 3 state (CAN3 0x3C6) (READ: 16 bytes: reserved for future use)

/* Diagnostic Control Mode */
// 0x14 REMOVED in v10.0 - Use VCU_I2C_WRITE_DIAGNOSTIC_CONTROL (0x00 on 0x49 address)

/* Error Payload Mode */
#define VCU_I2C_ERR_PAYLOAD            (0x15)  ///< Error payload (128 bytes: 64 errors × uint16_t LE, compact array with 0x0000 terminator) [NEW v6.2.0: single-command protocol, removed 0x07]

/* System Diagnostics Mode */
#define VCU_I2C_SYSTEM_DIAGNOSTICS     (0x16)  ///< FreeRTOS diagnostics (32 bytes: uptime, heap, task count, IDLE CPU%, per-task stats [11 tasks × 2 bytes: CPU%, stack%]) [NEW v6.2+]
                                                ///< **IMPORTANT:** System CPU utilization = 100 - IDLE_CPU% (byte 9). Do NOT sum all task percentages (will always be ~100%)!

/* ============================================================================
 * 0x49 WRITE ADDRESS - Write Commands [NEW v10.0]
 * ============================================================================
 * Fixed 12-byte payload format: [cmd_id][params...][padding]
 * Status response: 1 byte (0x00=success, 0x01=invalid param, 0xFF=unknown)
 */

#define VCU_I2C_WRITE_DIAGNOSTIC_CONTROL  (0x00)  ///< Diagnostic control overrides (0x49 WRITE command 0x00)
                                                   ///< TX1 (WRITE to 0x49): 12 bytes [0x00][flags_LSB][flags_MSB][duty][reserved×8]
                                                   ///< TX2 (READ from 0x49): 1 byte status (0x00=success, 0x01=invalid param)
                                                   ///< Replaces old 0x14 command with fixed 12-byte format

#define VCU_I2C_WRITE_CHARGER_CONTROL     (0x01)  ///< Charger control (0x49 WRITE command 0x01)
                                                   ///< TX1 (WRITE to 0x49): 12 bytes [0x01][enable][voltage%][current][reserved×8]
                                                   ///< TX2 (READ from 0x49): 1 byte status (0x00=success, 0x01=invalid param)
                                                   ///< Replaces old 0x0C command with fixed 12-byte format
                                                   ///< Voltage: 20-100% of 403.2V max (96 cells × 4.2V)

/**
 * For VCU error codes, include polarity_errors.h:
 *
 * #define POLARITY_ENABLE_LEGACY_NAMES  // Optional: enables SKUDAK_ERR_* aliases
 * #include "polarity_errors.h"
 */

#endif /* SKUDAK_COMMON_H_ */
