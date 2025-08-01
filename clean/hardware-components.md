# Smart Home IoT Project – Hardware Components Overview

## 1. Core Computing Unit

### BeagleBone Black (or BeagleBone Green)
- **Quantity:** One per room (or per zone)
- **Purpose:** Acts as a controller for connected electrical devices. It handles GPIO operations, runs MQTT clients, and connects to the local or cloud network.
- **Key Features:**
  - GPIO pin support
  - Ethernet or Wi-Fi connectivity
  - Runs a Linux-based OS (such as Debian)
  - USB and serial interfaces for development and debugging

---

## 2. Relay Modules

### 4-Channel or 8-Channel Relay Module
- **Quantity:** One per room (depending on number of devices)
- **Purpose:** Allows the BeagleBone to switch AC-powered devices like lights and fans by using GPIO signals.
- **Specifications:**
  - Compatible with 3.3V or 5V logic
  - Each relay supports up to 250V AC / 10A
  - Opto-isolated relays are recommended for safety and isolation

---

## 3. Electric Loads

### Light Fixtures
- **Quantity:** 2–3 per room
- **Purpose:** Standard AC-powered lighting, controlled via relays

### Ceiling or Table Fans
- **Quantity:** 1–2 per room
- **Purpose:** AC-powered fans, controlled for ON/OFF or speed depending on circuit setup

---

## 4. Fan Speed Control (Optional)

### Triac-Based Fan Regulator or Digital Step Switch
- **Purpose:** Used to control the speed of fans if needed
- **Options:**
  - Analog phase control using TRIAC + Opto-isolator (e.g., MOC3021)
  - Digital control using step-switches or multi-speed relays

Note: Speed control requires additional complexity and safety considerations. ON/OFF control is simpler and safer.

---

## 5. Power Supply

### 5V DC Power Adapter or Buck Converter
- **Purpose:** Powers the BeagleBone and relay modules from a shared AC source
- **Specifications:**
  - Output: 5V
  - Current: Minimum 2A per BeagleBone and attached relays
  - Use isolated and regulated power sources for stability and safety

---

## 6. Network Interface

### Wi-Fi Dongle (if needed)
- **Purpose:** Enables wireless connectivity for BeagleBone units without onboard Wi-Fi

### Router or Network Switch
- **Purpose:** Creates a local network where BeagleBone devices, backend server, and web client can communicate over MQTT and HTTP

---

## 7. Prototyping Tools and Accessories

| Component              | Purpose                                 |
|------------------------|-----------------------------------------|
| Breadboard or PCB      | For temporary or permanent circuits     |
| Jumper Wires (M-M, M-F)| GPIO and power connections              |
| Screw Terminals        | Secure AC connections                   |
| Multimeter             | Voltage and continuity testing          |
| Electrical Tape / Heat Shrink | Insulation for exposed terminals |
| Plastic Enclosures     | Safe housing for BeagleBone and relays  |

---

## 8. Safety Components

- **Fuses or Circuit Breakers:** Protects circuits from overcurrent
- **Opto-Isolated Relays:** Protects the controller from high-voltage surges
- **Grounded Enclosures:** Ensures user and device safety during operation

---

## 9. Hardware Summary Table

| Component                  | Quantity (Per Node) | Notes                                   |
|----------------------------|---------------------|-----------------------------------------|
| BeagleBone Black           | 1                   | Controller and MQTT client              |
| Relay Module (4/8 Channel) | 1                   | Controls multiple AC devices            |
| Light Fixtures             | 2–3                 | Lighting appliances                     |
| AC Fan                     | 1–2                 | Fan control (basic or speed)            |
| 5V Power Adapter (2A+)     | 1                   | For BeagleBone and relay module         |
| Wi-Fi Dongle               | 1                   | Only if BeagleBone lacks Wi-Fi          |
| Fan Regulator Circuit      | 1 (optional)        | For speed control (advanced feature)    |
| Router / Switch            | 1 (shared)          | Local network communication             |
| Jumper Wires               | As needed           | Prototyping and GPIO wiring             |
| Breadboard or PCB          | As needed           | Assembly or permanent setup             |
| Plastic Enclosure          | 1                   | Safety and organization                 |

---
