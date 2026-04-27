# Task-3.1: Embedded Systems Implementation Guide

## Project Overview
Task 3.1 is an embedded systems project designed to teach fundamental concepts of microcontroller programming and hardware interfacing using C++. This comprehensive guide covers everything from basic GPIO control to advanced sensor integration.

## What You'll Learn
- Microcontroller fundamentals and architecture
- GPIO (General-Purpose Input/Output) control and configuration
- Digital and analog signal processing
- Sensor interfacing and data acquisition
- Real-time programming concepts and constraints
- Hardware debugging techniques and best practices
- Interrupt-driven programming
- Serial communication protocols

## Hardware Requirements

### Essential Components
- **Microcontroller Unit (MCU):** Arduino Uno, Arduino Nano, Arduino Mega, or ARM-based microcontroller (STM32, SAMD21)
- **Development Board:** Compatible with your chosen microcontroller
- **USB Cable:** Type A to Type B (standard Arduino) or appropriate connector
- **Power Supply:** 5V DC, minimum 1A capacity (USB provides ~500mA)
- **Breadboard:** Standard full-size breadboard (83x55 tie points minimum)
- **Jumper Wires:** 40-60 count pack with male-to-male and male-to-female varieties
- **LEDs:** Pack of assorted colors (Red, Green, Blue, Yellow)
- **Resistors:** Pack with 220Ω (LED current limiting), 10kΩ (pull-up/down), 1kΩ
- **Push Buttons:** Momentary push buttons (normally open) - 5 pack recommended
- **Capacitors:** 0.1µF (ceramic decoupling) - 10 pack

### Sensor Components
- Temperature Sensor: DHT22 or LM35
- Distance Sensor: HC-SR04 Ultrasonic
- Motion Sensor: PIR motion detector
- Light Sensor: LDR (Light Dependent Resistor) or BH1750

### Optional Components
- **Digital Multimeter:** For voltage, current, and continuity testing
- **Logic Analyzer:** For signal timing analysis (e.g., Saleae)
- **Oscilloscope:** For detailed waveform analysis
- **Wire Stripper & Crimper:** For better connections
- **Helping Hands Tool:** Holds components while you work
- **Solder & Soldering Iron:** For permanent connections (if moving beyond breadboard)

## Software Requirements
- **C++ Compiler:** GCC for ARM (arm-none-eabi-gcc) or host compiler
- **IDE:** Arduino IDE, PlatformIO, Atmel Studio, or Visual Studio Code
- **Libraries:** 
  - Arduino core library (included)
  - DHT sensor library (for temperature/humidity)
  - HC-SR04 library (optional, can use GPIO directly)
- **Serial Monitor:** Built into Arduino IDE or separate terminal
- **Drivers:** CH340 driver for clone microcontroller boards (if needed)

## Installation & Setup

### Step 1: Install Development Environment
1. Download Arduino IDE from https://www.arduino.cc/en/software
2. Install on your operating system (Windows, Mac, or Linux)
3. Launch Arduino IDE and complete initial setup

### Step 2: Install Board Support
1. Open Arduino IDE
2. Go to File → Preferences
3. Find "Additional Boards Manager URLs" field
4. Add board URL if needed (for non-standard boards)
5. Go to Tools → Board Manager
6. Search and install your microcontroller board package
7. Select Tools → Board → Your board type

### Step 3: Install Required Libraries
1. Go to Sketch → Include Library → Manage Libraries
2. Search for "DHT" → Install "DHT sensor library" by Adafruit
3. Search for "HC-SR04" → Install preferred library
4. Search for "Adafruit Unified Sensor" → Install

### Step 4: Verify Connection
1. Connect microcontroller via USB cable
2. Go to Tools → Port → Select your COM port
3. Go to Tools → Board → Verify selection matches your hardware
4. Sketch → Verify to ensure compilation works

## Hardware Connection Guide

### Basic GPIO Pin Configuration
```
Arduino Pin Mapping (Arduino Uno example):
Digital Pins: 0-13 (0-1 reserved for serial communication)
Analog Pins: A0-A5 (can also read digital values)
PWM Pins: 3, 5, 6, 9, 10, 11 (for analog output simulation)
Power Pins: 5V, 3.3V, GND
```

### LED Circuit (Basic Output)
```
LED Schematic:
[GPIO Pin]—[220Ω Resistor]—[LED Anode]
                            [LED Cathode]—[GND]

Wiring Steps:
1. Connect GPIO pin (e.g., Pin 13) to 220Ω resistor
2. Connect resistor to longer LED leg (anode/+)
3. Connect shorter LED leg (cathode/-) to GND
4. LEDs turn on when GPIO is HIGH, off when LOW
```

### Push Button Circuit (Basic Input)
```
Button with Pull-Down Resistor:
[5V]—[Button]—[10kΩ Resistor]—[GPIO Pin]—[GND]

Operation:
- When button pressed: GPIO reads HIGH (5V)
- When button released: GPIO reads LOW (GND through resistor)
- 10kΩ resistor prevents floating voltage
```

### Temperature Sensor (DHT22) Connection
```
DHT22 Module Pinout:
Pin 1 (VCC): 5V power
Pin 2 (DATA): GPIO pin with pull-up resistor
Pin 3 (NC): Not connected
Pin 4 (GND): Ground

Wiring:
[5V]———[DHT22 Pin 1 (VCC)]
        [DHT22 Pin 2 (DATA)]——[10kΩ]——[GPIO Pin 5]
                                       [GND]
[GND]———[DHT22 Pin 4 (GND)]
```

### Ultrasonic Distance Sensor (HC-SR04)
```
HC-SR04 Pinout:
VCC: 5V power
TRIG: Trigger pulse input (GPIO output)
ECHO: Echo pulse output (GPIO input)
GND: Ground

Wiring:
[5V]———[HC-SR04 VCC]
[GPIO Pin 7]———[HC-SR04 TRIG]
[GPIO Pin 8]———[HC-SR04 ECHO]
[GND]———[HC-SR04 GND]

Operation:
1. Send 10µs pulse to TRIG
2. Measure duration of ECHO pulse
3. Distance = (duration * speed of sound) / 2
```

## Code Examples

### Example 1: LED Blink (Basic GPIO Output)
```cpp
int ledPin = 13;  // Define LED pin

void setup() {
  pinMode(ledPin, OUTPUT);  // Set pin as output
  Serial.begin(9600);        // Initialize serial
}

void loop() {
  digitalWrite(ledPin, HIGH);  // Turn LED on
  Serial.println("LED ON");
  delay(1000);                 // Wait 1 second
  
  digitalWrite(ledPin, LOW);   // Turn LED off
  Serial.println("LED OFF");
  delay(1000);                 // Wait 1 second
}
```

### Example 2: Button Input with LED Control
```cpp
int buttonPin = 2;
int ledPin = 13;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);  // Read button
  
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);  // Turn on LED
    Serial.println("Button Pressed - LED ON");
  } else {
    digitalWrite(ledPin, LOW);   // Turn off LED
    Serial.println("Button Released - LED OFF");
  }
  
  delay(50);  // Debounce delay
}
```

### Example 3: Analog Input (Light Sensor)
```cpp
int lightSensorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(lightSensorPin);  // Read 0-1023
  float voltage = (lightValue / 1023.0) * 5.0;  // Convert to voltage
  
  Serial.print("Light Value: ");
  Serial.print(lightValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");
  
  delay(500);  // Read every 500ms
}
```

### Example 4: Serial Communication
```cpp
void setup() {
  Serial.begin(9600);  // Initialize serial at 9600 baud
  Serial.println("Microcontroller Started!");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();  // Read character from serial
    
    if (command == '1') {
      Serial.println("Received command 1");
    } else if (command == '2') {
      Serial.println("Received command 2");
    }
  }
}
```

### Example 5: PWM Output (Brightness Control)
```cpp
int pwmPin = 9;  // PWM-capable pin

void setup() {
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  // Fade LED from off to on
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(pwmPin, brightness);  // 0-255 brightness levels
    delay(50);
  }
  
  // Fade from on to off
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(pwmPin, brightness);
    delay(50);
  }
}
```

## Compilation and Upload Process

### Using Arduino IDE
1. **Write/Open Code:** File → Open or write in editor
2. **Verify Compilation:** Sketch → Verify/Compile (Ctrl+R)
3. **Fix Errors:** Address any compilation errors
4. **Select Board:** Tools → Board → Your board type
5. **Select Port:** Tools → Port → COM port
6. **Upload:** Sketch → Upload (Ctrl+U)
7. **Wait:** Upload completes (usually 5-10 seconds)
8. **Monitor:** Tools → Serial Monitor (Ctrl+Shift+M)

### Using PlatformIO in VS Code
1. Install VS Code and PlatformIO extension
2. Create new PlatformIO project
3. Select board and framework (Arduino)
4. Edit platformio.ini with correct settings
5. Write code in src/main.cpp
6. Click PlatformIO: Build (or Ctrl+Alt+B)
7. Click PlatformIO: Upload (or Ctrl+Alt+U)
8. Click PlatformIO: Serial Monitor (or Ctrl+Alt+S)

## Testing Procedures

### Connectivity Test
1. Connect microcontroller via USB
2. Arduino IDE should recognize COM port
3. Go to Tools → Get Board Info
4. Verify board and port information displays

### Basic LED Test
1. Upload LED blink example code
2. Observe LED blinking on/off every second
3. Verify Serial Monitor shows "LED ON/OFF" messages
4. Timing should be approximately 1 second intervals

### Button Input Test
1. Upload button example code
2. Press button - LED should light
3. Release button - LED should turn off
4. Serial Monitor should show state changes

### Sensor Reading Test
1. Connect sensor following pinout diagram
2. Upload appropriate sensor code
3. Open Serial Monitor
4. Verify sensor values appear and change
5. Compare values with expected ranges

### Full System Integration Test
- All GPIO pins function correctly
- Sensors read accurate values
- Timing is precise and responsive
- No compilation warnings or errors
- Power consumption within limits

## Troubleshooting Guide

### Upload Problems
| Issue | Solution |
|-------|----------|
| "Port not recognized" | Install CH340 drivers; try different USB cable |
| "Upload timeout" | Select correct board type; check baud rate |
| "Avrdude not found" | Reinstall Arduino IDE; check PATH settings |
| "Board not responding" | Check USB connection; verify power supply |

### GPIO/Hardware Issues
| Issue | Solution |
|-------|----------|
| LED not lighting | Check polarity; verify resistor; test with multimeter |
| Button not responding | Check connections; verify INPUT mode; test continuity |
| Sensor reading 0 or max | Check power connections; verify pin configuration |
| Erratic readings | Add decoupling capacitors; check ground connections |

### Software/Compilation Issues
| Issue | Solution |
|-------|----------|
| "Cannot find header file" | Install required libraries via Library Manager |
| "Undefined reference" | Check library installation; verify include statements |
| Serial garbage output | Verify baud rate (usually 9600); check USB cable |
| Code compiles but doesn't run | Check power supply; verify bootloader presence |

### Debugging Tips
1. Use Serial.println() for variable monitoring
2. Add timing verification with millis()
3. Test components individually before integration
4. Use multimeter to verify voltages
5. Check ground connections first
6. Add LED indicators for status debugging
7. Use logic analyzer to verify signal timing

## Verification Checklist
- [ ] Microcontroller powers on successfully
- [ ] USB connection recognized by IDE
- [ ] Code compiles without errors
- [ ] LED responds to digitalWrite commands
- [ ] Button input detected and logged
- [ ] Serial communication works at correct baud rate
- [ ] All components properly connected per diagrams
- [ ] Power supply provides stable voltage
- [ ] No loose wires or cold solder joints
- [ ] Timing measurements are accurate

## Next Steps for Learning
1. **Basic Level:** Master LED control and button input
2. **Intermediate:** Add sensor reading and data processing
3. **Advanced:** Implement interrupts and real-time constraints
4. **Expert:** Build complete systems with wireless connectivity
5. **Professional:** Design custom PCBs and production-ready code

## Additional Resources
- [Arduino Official Documentation](https://www.arduino.cc/reference/en/)
- [Arduino Getting Started](https://www.arduino.cc/en/Guide)
- [Microcontroller Datasheets](https://www.microchip.com/)
- [Electronics Tutorials](https://www.electronics-tutorials.ws/)
- [PlatformIO Documentation](https://docs.platformio.org/)

## Safety Considerations
- Never apply voltages exceeding 5.5V to microcontroller pins
- Always use appropriate current-limiting resistors for LEDs
- Ensure proper power supply with adequate current capacity
- Handle electrostatic discharge carefully
- Do not work on live circuits
- Test continuity of wires before powering on

---

For additional support or questions, refer to the community forums or contact the project maintainer.