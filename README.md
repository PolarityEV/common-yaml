# Polarity Error Definitions

**Single source of truth for error codes across all Polarity platforms**

## ⚠️ IMPORTANT: Headers Are Generated - NOT Committed!

**The C headers (`polarity_errors.h`, `skudak_common.h`) are NOT committed to this repository.**

You MUST generate them before building:

```bash
pip3 install pyyaml jinja2
python3 generate.py
```

This ensures headers always match `definitions.yaml` and prevents version control conflicts with generated code.

---

This directory contains the code generation system for Polarity error codes. From a single YAML definition file, we generate language-specific error code files for:
- **C** (STM32, ESP32)
- **Dart** (Flutter mobile app)

## Quick Start

### Prerequisites

```bash
pip install pyyaml jinja2
```

### Generate Error Code Files

```bash
python3 generate.py
```

This creates:
- `generated/polarity_errors.h` - C header file
- `generated/polarity_errors.dart` - Dart class file

## Directory Structure

```
common/
├── definitions.yaml          # Single source of truth
├── generate.py              # Code generation script
├── templates/
│   ├── c_header.j2         # C template
│   └── dart.j2             # Dart template
├── generated/
│   ├── polarity_errors.h   # Generated C header
│   └── polarity_errors.dart # Generated Dart file
├── polarity_errors.h       # Copy for use in project
└── README.md               # This file
```

## Usage by Platform

### C (STM32/ESP32)

**Option 1: With Backward Compatibility (Recommended for transition)**

```c
#define POLARITY_ENABLE_LEGACY_NAMES  // Enable SKUDAK_ERR_* aliases
#include "polarity_errors.h"

// Use legacy names during transition
VCU_PushError(&vcu, SKUDAK_ERR_CAN1_INIT);

// Or use new names
VCU_PushError(&vcu, POLARITY_ERR_CAN1_INIT);
```

**Option 2: New Code (Recommended for new code)**

```c
#include "polarity_errors.h"

// Use new POLARITY_ERR_* names
VCU_PushError(&vcu, POLARITY_ERR_CAN1_INIT);
VCU_PushError(&vcu, POLARITY_ERR_I2C_SLAVE_TX);
```

### Dart (Flutter)

```dart
import 'package:your_app/polarity_errors.dart';

// Use constants
int errorCode = PolarityErrors.can1Init;

// Get human-readable description
String description = PolarityErrors.getDescription(errorCode);
// Returns: "CAN1 initialization failed"

// Get formatted error message
String message = PolarityErrors.formatError(errorCode);
// Returns: "[CAN] CAN1 initialization failed (Code: 110)"

// Check severity
bool isCritical = PolarityErrors.isCritical(errorCode);
String severity = PolarityErrors.getSeverity(errorCode);

// Get category
String category = PolarityErrors.getCategory(errorCode);
```

## Adding New Error Codes

1. **Edit `definitions.yaml`**:

```yaml
categories:
  UART:
    range: [160, 169]
    description: "UART serial communication errors"
    errors:
      - name: "UART3"
        code: 162
        description: "UART3 operation failed"
        severity: "error"
```

2. **Regenerate files**:

```bash
python3 generate.py
```

3. **Copy to project** (if not already part of build process):

```bash
cp generated/polarity_errors.h .
# For Flutter project:
# cp generated/polarity_errors.dart /path/to/flutter/lib/
```

4. **Update legacy mapping** (if backward compatibility needed):

```yaml
legacy_mapping:
  SKUDAK_ERR_UART3: POLARITY_ERR_UART3
```

## Error Code Categories (v2.1.0)

The error code system is organized into 6 distinct categories based on **functional domain**, not numerical ranges:

| Category  | Code Range | Description | Key Principle |
|-----------|------------|-------------|---------------|
| **CAN** | 0x0008-0x001D, 0x0044, 0x0049, 0x004E, 0x0053 | CAN bus peripheral and communication errors | "Is the CAN bus infrastructure broken?" |
| **VCU** | 0x0001-0x0007, 0x001E-0x0030 | STM32 peripherals and system errors (I2C, TIM, UART) | "Is an STM32 peripheral failing?" |
| **BMS** | 0x0031-0x0041 | BMS communication timeouts and battery pack faults | "Is the battery data bad or unavailable?" |
| **CHARGER** | 0x0042-0x0058 (excl. TX_FAIL) | Charger hardware faults and safety gates | "Is charging hardware faulty or unsafe?" |
| **MOTOR** | 0x0059-0x006C | Motor controller and LDU errors (stm32-sine) | "Is the motor controller reporting a fault?" |
| **SENSOR** | 0x006D-0x007B | Current sensor data errors | "Are sensor readings invalid or out of range?" |

### Category Design Philosophy

**CAN vs Data Errors:** The most important distinction is between:
- **CAN category:** HAL peripheral failures (e.g., `HAL_CAN_Init()` failed, FIFO overflow, message retrieval error)
- **Device categories (BMS/CHARGER/SENSOR):** Application-level faults reported *over* functional CAN (e.g., BMS timeout, charger hardware fault, sensor out of range)

**Example:**
- `POLARITY_ERR_CAN1_INIT` → CAN category (CAN peripheral won't initialize)
- `POLARITY_ERR_BMS1_TIMEOUT` → BMS category (BMS not sending CAN messages, but CAN bus is functional)
- `POLARITY_ERR_CHARGER1_TX_FAIL` → CAN category (HAL_CAN_AddTxMessage failed)
- `POLARITY_ERR_CHARGER1_OBC_FAULT` → CHARGER category (OBC reported hardware fault in its data frame)

## Motor/LDU Error Details

**Source**: stm32-sine motor controller firmware (temporary)
**CAN Broadcast**: ID 0x108 (10 Hz)
**Integration**: VCU receives via CAN1, exposes via I2C 0x0B

Motor errors originate from the Tesla LDU (Large Drive Unit) running stm32-sine firmware. These errors are broadcast over CAN and relayed through the VCU to the ESP32 and ultimately the Flutter mobile app.

### Error Flow

```
LDU Motor → CAN 0x108 → STM32 VCU → I2C 0x0B → ESP32 → BLE → Flutter App
```

### Motor Error Types

Motor errors are classified by their severity type from stm32-sine:

- **ERROR_STOP** (Critical): Motor shuts down immediately
  - Examples: Overcurrent (250), Emergency stop (254), Desaturation (256)

- **ERROR_DERATE** (Warning): Motor power limited to prevent damage
  - Examples: Heatsink overtemp (260), Current limit (261), Motor overtemp (267)

- **ERROR_DISPLAY** (Info): Informational, motor continues operation
  - Examples: Throttle sensor fault (251), Encoder warning (258)

### Using Motor Errors in Flutter

```dart
import 'package:your_app/polarity_errors.dart';

// Example: Display motor error with source and action
int errorCode = 250; // MOTOR_OVERCURRENT

String source = PolarityErrors.getSource(errorCode);
// "LDU_MOTOR"

String description = PolarityErrors.getDescription(errorCode);
// "Motor phase overcurrent detected"

String action = PolarityErrors.getAction(errorCode);
// "Motor will shut down immediately"

String severity = PolarityErrors.getSeverity(errorCode);
// "critical"

// Full UI display
showErrorDialog(
  title: '[$source] Error $errorCode',
  message: description,
  action: action,
  icon: PolarityErrors.getSeverityIcon(errorCode),  // 'error'
  color: PolarityErrors.getSeverityColor(errorCode), // 'red'
);

// Or use the combined helper:
String fullInfo = PolarityErrors.getFullErrorInfo(errorCode);
// Returns formatted multi-line string with all info
```

### Source Identification

The app can now distinguish error origins for context-aware handling:

- **STM32_VCU**: VCU firmware errors (100-249)
- **LDU_MOTOR**: Motor controller errors (250-269)
- **ESP32_GATEWAY**: ESP32 errors (future: 300+)

This enables targeted diagnostics and user guidance based on the error source.

## Severity Levels

- **`critical`**: System-critical errors (initialization failures, hardware faults)
- **`error`**: Standard errors (communication failures, configuration errors)
- **`warning`**: Non-critical issues (message queue warnings)

## Integration with Other Repositories

### STM32 Project (this repository)
- Copy `polarity_errors.h` to `common/` directory
- Include with: `#include "polarity_errors.h"`

### ESP32 (ESP-IDF) Project
- Copy `polarity_errors.h` to `components/common/include/`
- Add to CMakeLists.txt:
  ```cmake
  idf_component_register(
      INCLUDE_DIRS "include"
      SRCS "..."
  )
  ```

### Flutter Project
- Copy `polarity_errors.dart` to `lib/models/` or `lib/constants/`
- Import with: `import 'package:your_app/models/polarity_errors.dart';`

## Migration from Old System

### Phase 1: Enable Backward Compatibility (Current)
- Keep using SKUDAK_ERR_* names
- Define `POLARITY_ENABLE_LEGACY_NAMES` before including header
- No code changes required

### Phase 2: Gradual Migration (Optional)
- Update error handling code to use POLARITY_ERR_* names
- Keep legacy support enabled for other files

### Phase 3: Complete Migration (Future)
- Remove `POLARITY_ENABLE_LEGACY_NAMES` define
- All code uses POLARITY_ERR_* names
- Remove legacy mapping from definitions.yaml

## Build Integration (Optional)

### Makefile Integration

Add to your Makefile:

```makefile
# Generate error codes before build
polarity_errors.h: common/definitions.yaml
	cd common && python3 generate.py
	cp common/generated/polarity_errors.h common/

build: polarity_errors.h
	# ... rest of build
```

### CI/CD Integration

Add to your CI pipeline:

```yaml
- name: Generate Error Codes
  run: |
    cd common
    pip install pyyaml jinja2
    python3 generate.py
    cp generated/polarity_errors.h .
```

## Benefits Over Git Submodules

✅ **Single source of truth** - One YAML file defines all errors
✅ **No submodule hassles** - No git submodule sync issues
✅ **Multi-language support** - Works in C, Dart, and extensible to others
✅ **Rich metadata** - Descriptions, severity, categories
✅ **Easy to maintain** - Simple YAML editing
✅ **Build-time generation** - Can be part of automated build
✅ **Documentation** - Auto-generates human-readable descriptions

## Debug Error Codes (0x8000-0xFFFF)

### Overview
Debug error codes (MSB=1) provide detailed diagnostic information for development and troubleshooting without cluttering production error logs. They can be toggled at runtime via UART DEBUG_CONTROL command.

### Filtering Mechanism
- **Range:** 0x8000-0xFFFF (bit 15 set for easy filtering)
- **Default State:** Enabled (ON) for development
- **Filter Check:** `if (errorCode >= 0x8000 && !g_ErrorBufferConfig.DebugErrorsEnabled)`
- **Control:** UART command `VCU_CMD_DEBUG_CONTROL` (0x0C/0x8C)
- **Implementation:** Filtering happens at `ErrorBuffer_Push()` - debug errors are silently discarded when disabled

### Current Debug Error Codes

#### 12V Battery Tender Debug (0x8000-0x8006)
Detailed interlock diagnostics for troubleshooting 12V tender failures:

- `0x8000`: `DEBUG_VOLT12_TENDER_IGNITION_ON` - Ignition is ON (blocking tender)
- `0x8001`: `DEBUG_VOLT12_TENDER_HV_CHARGING` - HV charging active (blocking tender)
- `0x8002`: `DEBUG_VOLT12_TENDER_CHARGEPORT_TIMEOUT` - Charge port timeout
- `0x8003`: `DEBUG_VOLT12_TENDER_CHARGEPORT_NOT_DETECTED` - Charge port not detected
- `0x8004`: `DEBUG_VOLT12_TENDER_DCDC_NULL` - DCDC pointer is NULL
- `0x8005`: `DEBUG_VOLT12_TENDER_DCDC_NOT_DETECTED` - DCDC not detected on CAN
- `0x8006`: `DEBUG_VOLT12_TENDER_VOLTAGE_ABOVE_THRESHOLD` - Voltage healthy, no charge needed

### Adding New Debug Errors
1. Choose code in 0x8000-0xFFFF range (reserve ranges by module)
2. Add to `definitions.yaml` under `DEBUG:` category with `severity: "debug"`
3. Regenerate headers: `cd common && python3 generate.py`
4. Use like normal errors: `VCU_PushError(vcu, POLARITY_ERR_DEBUG_...)`
5. Debug errors automatically filtered when `g_ErrorBufferConfig.DebugErrorsEnabled = 0`

### Reserved Debug Error Ranges
- `0x8000-0x8FFF`: VCU subsystems (12V tender, GPOD, etc.)
- `0x9000-0x9FFF`: Charging system debug
- `0xA000-0xAFFF`: Motor/LDU debug
- `0xB000-0xBFFF`: BMS debug
- `0xC000-0xFFFF`: Reserved for future modules

## Troubleshooting

**Q: Getting "Module not found" errors?**
A: Install dependencies: `pip install pyyaml jinja2`

**Q: Legacy names not working?**
A: Make sure `POLARITY_ENABLE_LEGACY_NAMES` is defined *before* the include:
```c
#define POLARITY_ENABLE_LEGACY_NAMES
#include "polarity_errors.h"
```

**Q: Want to add a new language?**
A: Create a new template in `templates/` and add a generation function in `generate.py`

**Q: Debug errors not appearing?**
A: Check `g_ErrorBufferConfig.DebugErrorsEnabled` is set to `1`, or enable via UART DEBUG_CONTROL command (0x0C)

## Support

For issues or questions:
- Check existing error codes in `definitions.yaml`
- Review generated files in `generated/`
- Contact firmware team lead

## Version History

- **v2.1.0** (2025-10-14) - Error category reorganization for clarity
  - **NEW:** CAN category for pure CAN bus/peripheral errors
  - **NEW:** BMS category for BMS data and sensor errors
  - **UPDATED:** VCU category now focuses on STM32 peripherals (I2C, TIM, UART, system)
  - **UPDATED:** CHARGER category excludes TX_FAIL errors (moved to CAN)
  - **BREAKING:** Category labels changed (error code values unchanged)
  - Clarified distinction: "CAN bus broken?" vs "Data/sensor bad?"
  - No source code changes required

- **v2.0.0** (2025-10-09) - 16-bit error code system
  - Migrated from 8-bit to 16-bit error codes
  - All error codes renumbered sequentially from 0x0001
  - Hexadecimal format for all codes

- **v1.0.0** (2025-10-08) - Initial release with C and Dart support
  - Converted from SKUDAK naming to POLARITY
  - Added backward compatibility
  - Implemented code generation system
