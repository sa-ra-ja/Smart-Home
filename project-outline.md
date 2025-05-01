# Project Outline: Smart Home IoT System (Lights & Fans Control)

The Smart Home IoT System is a practical solution for managing lights and fans in a home setting. It uses BeagleBone boards as device nodes to control appliances through GPIO, with the option to include a local gateway for centralized communication. The system integrates MQTT and REST protocols for reliable and flexible communication, while a React-based web client offers a user-friendly interface for real-time control and monitoring. Its modular and scalable design allows for easy expansion, security, and energy-efficient operation, making it well-suited for modern home automation needs.

## System Architecture

- Device Nodes: Use multiple BeagleBone boards (e.g. Black, Green Wireless or Industrial) as endpoints. Each node controls a set of lights/fans via its GPIO (through relays or motor drivers). Boards run Linux and connect to the home network (Ethernet or Wi-Fi).

- Local Gateway/Server: Optionally designate one board or a local server as a gateway. This runs services like an MQTT broker (Mosquitto) and the web backend. For example, the BeagleBone Green Gateway has both Ethernet and 802.11 b/g/n Wi-Fi built-in, making it ideal for a central hub. All device nodes publish and subscribe through this gateway.

- Networking: Boards join the LAN (static IPs or DHCP). They can communicate via TCP/IP over Ethernet or Wi-Fi. Use a publish/subscribe or request/response model: e.g., MQTT topics for device telemetry/commands, or REST API calls for direct control. MQTT is lightweight and bidirectional (a single TCP connection can carry many messages both ways), whereas HTTP REST involves one request per action. In practice, a hybrid model works well: IoT devices use MQTT for quick messaging, and the web client uses HTTP or WebSockets for the UI.

[![High Level System Architecture](https://mermaid.ink/img/pako:eNqFkm1v2jAQx7-Kda8DnR3yQFRNIkHVpJVKA6RJS_rCTa6JR2JnjsPGEN99hlCVUlW7V_77fuc7390eclUgRFBq3lZkPc8ksdb1T8PFd3wiSS1QmsFxtBlNl8hzc3LO2vZxcKEsMnkVHvN8Y-_JCvUW9esTMU3vat5tbh5s9vHP7gw8XhAsXXxbr0ms1QY1WajuVy-MUZcIJaPRZ0t-nH_VcG3IF9UgeUDzW-nNa3hC0xh5WWOsJJIRuRdbIUuyVKq5SJKwt1SMhb4i3LfEV2HyCuX7rswouT0VTAcds0En15pdafflhWT48Zym96KsTHdzx2VHtoKTJdZ8151zJmzA2H8wd8DcjzFwoEHdcFHYFdkfwzIwFTaYQWSPBbcNhUweLMd7o1Y7mUNkdI8OaNWXFUTPvO6s6tuCG5wLbufSvCAtlz9sLy8kRHv4A1EYjKfTMJy4ged5IZ0wB3YQTbxxGIS-606CIPBDGhwc-HuK_zQOPDZl1GPU913f90LHLvSx6HMtdgqoE9VLAxFlgQNYCKP0Ytj9XMlnUcLhH9KI5sA?type=png)](https://mermaid.live/edit#pako:eNqFkm1v2jAQx7-Kda8DnR3yQFRNIkHVpJVKA6RJS_rCTa6JR2JnjsPGEN99hlCVUlW7V_77fuc7390eclUgRFBq3lZkPc8ksdb1T8PFd3wiSS1QmsFxtBlNl8hzc3LO2vZxcKEsMnkVHvN8Y-_JCvUW9esTMU3vat5tbh5s9vHP7gw8XhAsXXxbr0ms1QY1WajuVy-MUZcIJaPRZ0t-nH_VcG3IF9UgeUDzW-nNa3hC0xh5WWOsJJIRuRdbIUuyVKq5SJKwt1SMhb4i3LfEV2HyCuX7rswouT0VTAcds0En15pdafflhWT48Zym96KsTHdzx2VHtoKTJdZ8151zJmzA2H8wd8DcjzFwoEHdcFHYFdkfwzIwFTaYQWSPBbcNhUweLMd7o1Y7mUNkdI8OaNWXFUTPvO6s6tuCG5wLbufSvCAtlz9sLy8kRHv4A1EYjKfTMJy4ged5IZ0wB3YQTbxxGIS-606CIPBDGhwc-HuK_zQOPDZl1GPU913f90LHLvSx6HMtdgqoE9VLAxFlgQNYCKP0Ytj9XMlnUcLhH9KI5sA)

## Hardware Specifications (Lights & Fans)

- Relays: Use relay modules to switch high-voltage loads. For example, the official BeagleBone Relay Cape provides 4 relays rated 15 A @ 24 VDC / 12 A @ 250 VAC – sufficient for most household lights and small fans. Each relay coil is driven by a GPIO pin. Relays must be opto-isolated or MOSFET-driven to protect the BeagleBone’s 3.3 V logic.

- Fans (AC): Standard ceiling or pedestal fans are AC motors. Control their on/off (and dimming) via triac-based circuits or AC motor controllers. For example, an optotriac (like MOC302x) plus a power triac can form an AC dimmer for variable speed. Ensure zero-cross detection if needed for smooth speed control. Use snubber networks on triacs to handle inductive loads. Each fan’s speed level can be varied by phase-angle control.

- GPIO Usage: Assign one GPIO per relay/triac control. For example, BBB pin P9_14 corresponds to GPIO50 on the AM335x processor (used in sample code). Use the BeagleBone’s headers (P8/P9) according to pinout tables. Many boards can handle up to ~65 digital GPIO pins; plan port usage accordingly.

- Power Supply: Provide a stable 5 V DC supply (e.g. 2 A or more per board). Use a separate regulated supply for relays/fans if they run on 12 V/24 V. Add decoupling capacitors on power lines. Protect circuits with fuses or breakers. For fans, consider using a separate high-current supply if needed.

[![](https://mermaid.ink/img/pako:eNp9UFtPgzAU_ivNed4md4QHkxXii9NEN1-EPVQ4AgHapcB0LvvvdjAzNhP71O_W7_TsIREpgg-ZZJucrMKYE3Wa7n0gXhuUA3U884hK8amo9cAhT2N-lViIhFVkiXI7TtKIsqRU_pNC7ivWlDdPqnx9dgXR4_NqRVRJ-W_HixA1CXFbJNic06EeUWRZhVRwJItiW_Cst44aQmPsoZjKK90c6w9Fm-TI_04yJ9PpHaEDoD0IBhD0INQvkHGBzJjDBGqUNStStfr9UY2hzbHGGHx1TZksY4j5QflY14rljifgt7LDCUjRZTn4H6xqFOo2KWsxLJhaTP1r2TD-pr41guDv4Qt8S5tZtu44jmYbumfr9gR24OvuzDU8z7Mc09As17EPE_ju89rMvnU1z_Rsy9B169ZSgUwehz7NolaCMhAdb9UzpnH4ASfsreE?type=png)](https://mermaid.live/edit#pako:eNp9UFtPgzAU_ivNed4md4QHkxXii9NEN1-EPVQ4AgHapcB0LvvvdjAzNhP71O_W7_TsIREpgg-ZZJucrMKYE3Wa7n0gXhuUA3U884hK8amo9cAhT2N-lViIhFVkiXI7TtKIsqRU_pNC7ivWlDdPqnx9dgXR4_NqRVRJ-W_HixA1CXFbJNic06EeUWRZhVRwJItiW_Cst44aQmPsoZjKK90c6w9Fm-TI_04yJ9PpHaEDoD0IBhD0INQvkHGBzJjDBGqUNStStfr9UY2hzbHGGHx1TZksY4j5QflY14rljifgt7LDCUjRZTn4H6xqFOo2KWsxLJhaTP1r2TD-pr41guDv4Qt8S5tZtu44jmYbumfr9gR24OvuzDU8z7Mc09As17EPE_ju89rMvnU1z_Rsy9B169ZSgUwehz7NolaCMhAdb9UzpnH4ASfsreE)

## Software Structure on BeagleBone

- Low-Level I/O (C): Write C modules or daemons for direct GPIO control. The BeagleBone has libraries like iolib which simplify GPIO usage (e.g., init, set direction, then pin_high()/pin_low() to drive pins). Using C (or PRU real-time cores) is ideal for timing-sensitive tasks (e.g. generating PWM for speed). Linux also exposes GPIO via sysfs (e.g. echo 67 > /sys/class/gpio/export to enable GPIO67), so C programs can open /sys/class/gpio/gpioX/value to read/write.

- Higher-Level Logic (Python): Use Python for network communication and high-level control. For instance, a Python script can subscribe to MQTT topics or run a REST client/server to handle commands and schedule tasks. The BeagleBone home automation literature suggests using Python to interface components and enable remote control. Python libraries like Adafruit_BBIO.GPIO or python-periphery simplify GPIO handling. Structure software as separate processes: e.g., one thread reading sensors and publishing state, another listening for incoming commands.

- Modularity: Organize code into modules: e.g., a C module for each device driver (lights, fans), and a Python “middleware” layer to coordinate actions. Use inter-process communication (MQTT, sockets, or shared files) between C and Python if needed.

[![](https://mermaid.ink/img/pako:eNptVFtv2jAY_SuWpUqbljKWMELyMImCNFUqGx10k6a8mPgj8UjszBc6hvjvtZOgmoo8RPH5Lud8F-eIc0EBp_jmBj0pQDNiX5SRQpIabYVEueBaiqpivECqJlKjUtTWBfYsB5XxNs4ZFyBrwijKK6LUvM_wjihkFOQuqzJNI2w8U6hiNdNA32fc9844sk-LOC0SHTvEPR8eRMG4d_7J4LlXgZQm2ijPuBZFUYGlKUqtPm4J941T-scojSyKVANAO9Mp4z7_L9jMKgZcX4j4AZxaXZSociOIpJ5pQXaApst7JOGvAaV9xgemNHCkhUu7EvkONDINJRrUVfI7Yl04XYHcv-nC1OjSimK5jXWNlRfiKnKw86prwqlybIvH9dpzaPM5jR721MpA87urQuZtf7_ZDblQsTIblUu2AUeiRcNyv9pZtzHo6_L-uwcvzaZiqmyHBW_Y2mnf3n7x2p46sE_7ijqfy-6kaAWu3HPdAdqCzktQPtFliEviVfaaodO9Z8TrnOd4jbyv6kznBeMA192VsLer7V6G7fBqyHBqPymRuwxn_GT9iNFideA5TrU0EGApTFHidEsqZU_dpvR35OzSEP5bCP-I0yP-h9NwMhmMkyQZDYdJmIQBPlhsOBh9TuJwEkfJZBRF4_gU4P9t-HAwiWOLxVE8HoZhFCUBLqTT3EtpN34mDNc4_ZRYK1CmhVx0fw3bsy0r8OkFQtpX4A?type=png)](https://mermaid.live/edit#pako:eNptVFtv2jAY_SuWpUqbljKWMELyMImCNFUqGx10k6a8mPgj8UjszBc6hvjvtZOgmoo8RPH5Lud8F-eIc0EBp_jmBj0pQDNiX5SRQpIabYVEueBaiqpivECqJlKjUtTWBfYsB5XxNs4ZFyBrwijKK6LUvM_wjihkFOQuqzJNI2w8U6hiNdNA32fc9844sk-LOC0SHTvEPR8eRMG4d_7J4LlXgZQm2ijPuBZFUYGlKUqtPm4J941T-scojSyKVANAO9Mp4z7_L9jMKgZcX4j4AZxaXZSociOIpJ5pQXaApst7JOGvAaV9xgemNHCkhUu7EvkONDINJRrUVfI7Yl04XYHcv-nC1OjSimK5jXWNlRfiKnKw86prwqlybIvH9dpzaPM5jR721MpA87urQuZtf7_ZDblQsTIblUu2AUeiRcNyv9pZtzHo6_L-uwcvzaZiqmyHBW_Y2mnf3n7x2p46sE_7ijqfy-6kaAWu3HPdAdqCzktQPtFliEviVfaaodO9Z8TrnOd4jbyv6kznBeMA192VsLer7V6G7fBqyHBqPymRuwxn_GT9iNFideA5TrU0EGApTFHidEsqZU_dpvR35OzSEP5bCP-I0yP-h9NwMhmMkyQZDYdJmIQBPlhsOBh9TuJwEkfJZBRF4_gU4P9t-HAwiWOLxVE8HoZhFCUBLqTT3EtpN34mDNc4_ZRYK1CmhVx0fw3bsy0r8OkFQtpX4A)

## Communication Protocols

- MQTT: Implement an MQTT broker (e.g. Mosquitto) on the gateway. Each node runs an MQTT client (Python’s paho-mqtt or similar) that publishes its device states (e.g. home/livingroom/light1 = ON) and subscribes to control topics (e.g. home/livingroom/light1/set). MQTT is ideal for IoT because after the initial TCP connection, messages (tiny binary payloads) flow in both directions efficiently. Use “last will/retain” features to handle offline status.

- HTTP/REST: Alternatively (or additionally), expose RESTful APIs on the server. Devices could host small Flask/Express servers for pull-style control, or the central server can call devices. HTTP is simpler for web integration but has higher overhead per request. If used, define endpoints like GET /lights/1/status or POST /lights/1/on.

- WebSockets (Socket.IO): For real-time updates to the browser, use WebSockets. For example, the backend (Flask-SocketIO or Node+socket.io) can emit events whenever a device state changes, and the React client listens for instant updates. This avoids polling.

- Network Layer: All communication runs over TCP/IP on the local LAN (or over SSL/TLS if remote). Use QoS 0 or 1 for MQTT (QoS 2 is usually unnecessary). VLAN or subnet devices if security requires.
[![](https://mermaid.ink/img/pako:eNqNkk1v4jAQhv_KyKdUAkJICGBpOaTRtpVKYfkQUsXFDbMhSmKzjrNbFvHfd9wEaSV6aA6OR37emdfjObNE7ZFxVuGvGmWCcSZSLcqdBPqOQpssyY5CGtiAqGBToQYn0uoPbe5uoa2FtvgG90WGFDtLFIn5BIwsGIkkR7kH53shqtx9ISefoDOLzn6s10B1c9S3RPyRDEVaYKQkgvOc_c5kCkulSkrYCDbd6XTLrbEkhx17ztKDgbncseZ4S8cRh8V8tQZXHDO3sIDruarVRwTMeGNkUb8VWXUA56BKJNJW01SsEXluhQa6U5i_tNeZdUkct-IYSUBtnGFViRQbIm6Ah8XTHB6fHh7BWddagpKwxEKc7q7U103cGqDrrYwwCPVxT7_rtZq-0KOtFD2Hobw2aZvkW5ODdViJuhTZnkblbJU7Zg5Y4o5x2u6Fzm0jL8SJ2qjVSSaMG11jh2lVpwfGf4qioqgp3Q7ZFaFHfCXj_4WMn9k7437QC_wwGAd-MJjQ6nfYifGx3-sPg2AQBuFoOBxNBpcO-_uh7_fGHoHhaBJ6k4E_CocdlmpruvVC04b6XtXSMO71_cs_0qDtFg?type=png)](https://mermaid.live/edit#pako:eNqNkk1v4jAQhv_KyKdUAkJICGBpOaTRtpVKYfkQUsXFDbMhSmKzjrNbFvHfd9wEaSV6aA6OR37emdfjObNE7ZFxVuGvGmWCcSZSLcqdBPqOQpssyY5CGtiAqGBToQYn0uoPbe5uoa2FtvgG90WGFDtLFIn5BIwsGIkkR7kH53shqtx9ISefoDOLzn6s10B1c9S3RPyRDEVaYKQkgvOc_c5kCkulSkrYCDbd6XTLrbEkhx17ztKDgbncseZ4S8cRh8V8tQZXHDO3sIDruarVRwTMeGNkUb8VWXUA56BKJNJW01SsEXluhQa6U5i_tNeZdUkct-IYSUBtnGFViRQbIm6Ah8XTHB6fHh7BWddagpKwxEKc7q7U103cGqDrrYwwCPVxT7_rtZq-0KOtFD2Hobw2aZvkW5ODdViJuhTZnkblbJU7Zg5Y4o5x2u6Fzm0jL8SJ2qjVSSaMG11jh2lVpwfGf4qioqgp3Q7ZFaFHfCXj_4WMn9k7437QC_wwGAd-MJjQ6nfYifGx3-sPg2AQBuFoOBxNBpcO-_uh7_fGHoHhaBJ6k4E_CocdlmpruvVC04b6XtXSMO71_cs_0qDtFg)


## Backend Server Design

- Framework: Choose Flask (Python) or Node.js/Express. For Flask, routes can be defined to handle device queries and actions. For example, a simple Flask app registers @app.route('/api/light/<id>/toggle') to toggle a relay. Flask can also serve the React frontend or act as a proxy. For Node.js, use Express for REST and include socket.io for WebSocket.

- Device API: Design REST endpoints (e.g., /api/devices, /api/light/<id>, /api/fan/<id>/speed) that the React client will call. The server acts as a mediator: on a control request, it publishes an MQTT command or directly signals the BeagleBone node. It also maintains current device state (in memory or a lightweight DB) to respond to status queries.

- Real-Time Updates: Integrate an MQTT subscriber in the backend: whenever a node publishes a state change, the server updates its records and pushes the update to connected clients via WebSocket. This keeps the UI in sync with devices.

- Security: Implement authentication (e.g., JSON Web Tokens) on APIs. Use HTTPS (TLS) for all HTTP connections (see Security below).

- Persistence: Optionally use a database (like SQLite or MongoDB) to log events or store configurations. Ensure the backend service restarts on boot and recovers gracefully.

## Web Client (React)

- Structure: Build a single-page app (e.g. using Create React App). Use React Router if multiple views are needed (e.g., dashboard, device lists, settings).

- Components: Create components like DeviceCard (showing a light or fan), Switch, Slider (for fan speed), and StatusPanel. Each device’s on/off state can be toggled by a button, and fan speeds by a slider input. Use state/hooks or Redux to manage application state. (For example, one open-source home automation UI uses Axios for API calls and Redux for state management.)

- Data Fetching: Use Axios or Fetch to call backend REST endpoints for initial status and actions. For example, axios.get('/api/devices') to load all devices, and axios.post('/api/light/1/toggle') to switch a light.

- Real-Time UI: Connect to the backend via WebSocket (or MQTT over WebSocket) so the UI updates immediately on external changes (e.g., if a device is toggled physically). For instance, when an MQTT message arrives at the server, it can emit a socket.emit('statusUpdate') to the React app.

- Visualization: Display device statuses clearly. Use text/icons (FontAwesome) or images: e.g., a lightbulb icon that lights up when on. Show numeric values (fan speed, temperature if any). Consider using a UI library (Material-UI, Ant Design) for polished controls. Add responsive design for mobile/tablet use.

- User Interaction: Ensure the interface allows control: toggles for lights, sliders for fan levels. Provide feedback on actions (e.g., spinner while waiting). Handle error cases (device offline).

- Figure: Example of a simple web dashboard displaying device status. A React-based UI would similarly show real-time states (e.g. “GPIO input Status”) and allow user controls on switches/sliders.

## Security Considerations

- Transport Encryption: All web traffic should use HTTPS (TLS). As AWS notes, HTTPS provides encryption to prevent eavesdropping or tampering. Obtain SSL certificates (e.g. Let’s Encrypt) and configure the server to redirect HTTP to HTTPS. For MQTT, enable TLS (using TLS v1.2+) on the broker so data is encrypted on the wire.

- Authentication: Protect all APIs with authentication. Use token-based auth (JWT) or API keys. For example, require clients to login and include a bearer token in requests. On the BeagleBone side, secure MQTT with username/password or X.509 certificates (mutual TLS is ideal). Do not leave open ports; disable default accounts.

- Network Security: Place IoT devices on a separate network segment or VLAN. Only allow the gateway or server to communicate outside (firewall rules). Disable unused services on the BeagleBones (e.g., SSH only if needed).

- Software Updates: Keep the OS and packages updated. Regularly update the firmware/software on devices. Remove any default passwords and close unnecessary ports.

- Data Validation: Sanitize and validate all inputs (avoid injection attacks). Rate-limit API calls if exposed outside.

## Power Management, Scalability, and Expansion

- Power: Ensure stable power to all nodes. Use quality power supplies (5 V/2–3 A per board). Add surge protection for mains circuits. For critical loads (e.g. security lights), consider battery backup or UPS. Include fuses or breakers on high-voltage lines.

- Energy Efficiency: Implement features like turning off fans/lights after inactivity. Monitor current draw with sensors (ACS712) if needed, and consider environmental controls.

- Scalability: Design the system to add more nodes easily. Since communication is via MQTT topics or REST APIs, adding a new room (with its own BeagleBone) involves writing code/config for that node and updating topics/endpoints. The MQTT broker and server can handle many clients; scale vertically (better CPU) or horizontally (multiple brokers) if needed. The architecture supports adding sensors (temperature, motion) or actuators (blinds, plugs) by simply subscribing/publishing new topics.

- Modular Expansion: Use a modular codebase so new device types (e.g. RGB lights, security sensors) can be plugged in. On hardware, expansion capes for BeagleBone (e.g., ADC cape, motor cape) can be integrated.

- Future Enhancements: Plan for integrations like voice control (bridge commands from Alexa/Google Home via MQTT), or cloud logging. One could containerize the backend (Docker) for easy deployment. Overall, ensure the bus (MQTT broker) and network are not single points of failure, and design for more devices by following IoT best practices.