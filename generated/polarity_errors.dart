// polarity_errors.dart
//
// Polarity Error Code Definitions
// Version: 1.0.0
//
// AUTO-GENERATED FILE - DO NOT EDIT MANUALLY
// Generated: 2025-10-08 19:04:24
// Source: definitions.yaml
//
// This file contains error code definitions for Polarity Flutter/Dart projects.
//
// To regenerate this file, run:
//   python generate.py
//
// Copyright (c) 2025 Polarity EV

/// Error code definitions for Polarity VCU
///
/// This class provides constants for all VCU error codes with
/// human-readable descriptions for display in the UI.
class PolarityErrors {
  // Private constructor to prevent instantiation
  PolarityErrors._();

  // ========================================================================
  // I2C Errors
  // I2C communication errors
  // ========================================================================

  /// I2C slave transmit failed
  static const int i2cSlaveTx = 100;
  /// I2C slave receive failed
  static const int i2cSlaveRx = 101;
  /// I2C listen mode activation failed
  static const int i2cListen = 102;
  /// I2C error callback triggered
  static const int i2cErrCbk = 103;
  /// I2C slave transmit complete with error
  static const int i2cSlaveTxCplt = 104;
  /// I2C slave receive complete with error
  static const int i2cSlaveRxCplt = 105;
  /// I2C enable failed
  static const int i2cEnable = 109;
  // ========================================================================
  // CAN Errors
  // CAN bus communication errors
  // ========================================================================

  /// CAN1 initialization failed
  static const int can1Init = 110;
  /// CAN2 initialization failed
  static const int can2Init = 111;
  /// CAN3 initialization failed
  static const int can3Init = 112;
  /// CAN1 filter configuration failed
  static const int can1Filter = 113;
  /// CAN2 filter configuration failed
  static const int can2Filter = 114;
  /// CAN3 filter configuration failed
  static const int can3Filter = 115;
  /// CAN1 enable/start failed
  static const int can1En = 116;
  /// CAN2 enable/start failed
  static const int can2En = 117;
  /// CAN3 enable/start failed
  static const int can3En = 118;
  /// CAN1 notification activation failed
  static const int can1Notification = 119;
  /// CAN2 notification activation failed
  static const int can2Notification = 120;
  /// CAN3 notification activation failed
  static const int can3Notification = 121;
  /// CAN RX FIFO0 error
  static const int canRxFifo0 = 130;
  /// CAN RX FIFO1 error
  static const int canRxFifo1 = 131;
  /// CAN receive message failed
  static const int canRxMsg = 132;
  // ========================================================================
  // TIM Errors
  // Timer peripheral errors
  // ========================================================================

  /// Timer 1 operation failed
  static const int tim1 = 140;
  /// Timer 2 operation failed
  static const int tim2 = 141;
  /// Timer 3 operation failed
  static const int tim3 = 142;
  /// Timer 4 operation failed
  static const int tim4 = 143;
  /// Timer 5 operation failed
  static const int tim5 = 144;
  /// Timer 6 operation failed
  static const int tim6 = 145;
  /// Timer 7 operation failed
  static const int tim7 = 146;
  /// Timer 8 operation failed
  static const int tim8 = 147;
  /// Timer 9 operation failed
  static const int tim9 = 148;
  /// Timer 10 operation failed
  static const int tim10 = 149;
  /// Timer 11 operation failed
  static const int tim11 = 150;
  /// Timer 12 operation failed
  static const int tim12 = 151;
  /// Timer 13 operation failed
  static const int tim13 = 152;
  // ========================================================================
  // UART Errors
  // UART serial communication errors
  // ========================================================================

  /// UART1 operation failed
  static const int uart1 = 160;
  /// UART2 operation failed
  static const int uart2 = 161;
  // ========================================================================
  // VCU_GENERAL Errors
  // VCU general system errors
  // ========================================================================

  /// VCU initialization failed
  static const int vcuInit = 200;
  /// DC-DC converter error
  static const int dcdc = 210;
  /// BMS1 communication or fault
  static const int bms1 = 211;
  /// BMS2 communication or fault
  static const int bms2 = 212;
  // ========================================================================
  // Error Descriptions
  // ========================================================================

  /// Map of error codes to human-readable descriptions
  static const Map<int, String> descriptions = {
    100: 'I2C slave transmit failed',
    101: 'I2C slave receive failed',
    102: 'I2C listen mode activation failed',
    103: 'I2C error callback triggered',
    104: 'I2C slave transmit complete with error',
    105: 'I2C slave receive complete with error',
    109: 'I2C enable failed',
    110: 'CAN1 initialization failed',
    111: 'CAN2 initialization failed',
    112: 'CAN3 initialization failed',
    113: 'CAN1 filter configuration failed',
    114: 'CAN2 filter configuration failed',
    115: 'CAN3 filter configuration failed',
    116: 'CAN1 enable/start failed',
    117: 'CAN2 enable/start failed',
    118: 'CAN3 enable/start failed',
    119: 'CAN1 notification activation failed',
    120: 'CAN2 notification activation failed',
    121: 'CAN3 notification activation failed',
    130: 'CAN RX FIFO0 error',
    131: 'CAN RX FIFO1 error',
    132: 'CAN receive message failed',
    140: 'Timer 1 operation failed',
    141: 'Timer 2 operation failed',
    142: 'Timer 3 operation failed',
    143: 'Timer 4 operation failed',
    144: 'Timer 5 operation failed',
    145: 'Timer 6 operation failed',
    146: 'Timer 7 operation failed',
    147: 'Timer 8 operation failed',
    148: 'Timer 9 operation failed',
    149: 'Timer 10 operation failed',
    150: 'Timer 11 operation failed',
    151: 'Timer 12 operation failed',
    152: 'Timer 13 operation failed',
    160: 'UART1 operation failed',
    161: 'UART2 operation failed',
    200: 'VCU initialization failed',
    210: 'DC-DC converter error',
    211: 'BMS1 communication or fault',
    212: 'BMS2 communication or fault',
  };

  /// Map of error codes to severity levels
  static const Map<int, String> severities = {
    100: 'error',
    101: 'error',
    102: 'error',
    103: 'error',
    104: 'error',
    105: 'error',
    109: 'error',
    110: 'critical',
    111: 'critical',
    112: 'critical',
    113: 'error',
    114: 'error',
    115: 'error',
    116: 'critical',
    117: 'critical',
    118: 'critical',
    119: 'error',
    120: 'error',
    121: 'error',
    130: 'warning',
    131: 'warning',
    132: 'error',
    140: 'error',
    141: 'error',
    142: 'error',
    143: 'error',
    144: 'error',
    145: 'error',
    146: 'error',
    147: 'error',
    148: 'error',
    149: 'error',
    150: 'error',
    151: 'error',
    152: 'error',
    160: 'error',
    161: 'error',
    200: 'critical',
    210: 'critical',
    211: 'critical',
    212: 'critical',
  };

  /// Map of error codes to category names
  static const Map<int, String> categories = {
    100: 'I2C',
    101: 'I2C',
    102: 'I2C',
    103: 'I2C',
    104: 'I2C',
    105: 'I2C',
    109: 'I2C',
    110: 'CAN',
    111: 'CAN',
    112: 'CAN',
    113: 'CAN',
    114: 'CAN',
    115: 'CAN',
    116: 'CAN',
    117: 'CAN',
    118: 'CAN',
    119: 'CAN',
    120: 'CAN',
    121: 'CAN',
    130: 'CAN',
    131: 'CAN',
    132: 'CAN',
    140: 'TIM',
    141: 'TIM',
    142: 'TIM',
    143: 'TIM',
    144: 'TIM',
    145: 'TIM',
    146: 'TIM',
    147: 'TIM',
    148: 'TIM',
    149: 'TIM',
    150: 'TIM',
    151: 'TIM',
    152: 'TIM',
    160: 'UART',
    161: 'UART',
    200: 'VCU_GENERAL',
    210: 'VCU_GENERAL',
    211: 'VCU_GENERAL',
    212: 'VCU_GENERAL',
  };

  // ========================================================================
  // Helper Methods
  // ========================================================================

  /// Get human-readable description for an error code
  ///
  /// Returns the description if found, otherwise returns a default message.
  ///
  /// Example:
  /// ```dart
  /// String message = PolarityErrors.getDescription(100);
  /// // Returns: "I2C slave transmit failed"
  /// ```
  static String getDescription(int errorCode) {
    return descriptions[errorCode] ?? 'Unknown error ($errorCode)';
  }

  /// Get severity level for an error code
  ///
  /// Returns: 'critical', 'error', or 'warning'
  static String getSeverity(int errorCode) {
    return severities[errorCode] ?? 'unknown';
  }

  /// Get category name for an error code
  ///
  /// Returns the category (e.g., 'I2C', 'CAN', 'TIM')
  static String getCategory(int errorCode) {
    return categories[errorCode] ?? 'UNKNOWN';
  }

  /// Check if an error code is critical
  static bool isCritical(int errorCode) {
    return getSeverity(errorCode) == 'critical';
  }

  /// Check if an error code is valid
  static bool isValid(int errorCode) {
    return descriptions.containsKey(errorCode);
  }

  /// Get a formatted error message
  ///
  /// Example:
  /// ```dart
  /// String message = PolarityErrors.formatError(100);
  /// // Returns: "[I2C] I2C slave transmit failed (Code: 100)"
  /// ```
  static String formatError(int errorCode) {
    if (!isValid(errorCode)) {
      return 'Unknown error code: $errorCode';
    }

    final category = getCategory(errorCode);
    final description = getDescription(errorCode);
    return '[$category] $description (Code: $errorCode)';
  }
}