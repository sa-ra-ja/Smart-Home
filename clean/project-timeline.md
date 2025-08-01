# Smart Home IoT Project Timeline 

This document outlines the development plan for our smart home embedded systems project. The focus is on controlling lights and fans using IoT-enabled BeagleBone devices, with a React-based web client for user interaction.

---
[![](https://mermaid.ink/img/pako:eNptlP9q2zAQx1_lEHR_OcWx88Pxn2sILSwQlpaxkX9U--polSUjy22zUtg79A33JDtHTqwmPRKQdff9SHc66ZVlOkeWsoIrazcKyKywEmFdcmPhWpcIN_oWVkb_xszCrShRCoUuNOcWF9qU3AL8JBssl4P53Pn4i6gPvoscLu43yjlq4gitYCW5UkIV8AXWaJvKeQ8LHb1HSznpnjBoxxV5A4jCaDwI6TcMYJg7_TU3-TM36JjgWUr_bef1tFGv_cqzR1Q5zLEWhTrVAjfZ1hPGTvgxqTk-odRViaqrJk2IDGEhTOm2Zdu6Hpl7e-icHnxE47NdHdEdpSfcuxgPMO4BC6OVbQnrR5RotfqYlttCF-MRJn1huiSuKMZoCd90IbJTQuacHmB6Vtl_f9871A2tVhje1qxHiH7SwyQ95phJR7m7Oc-kEZ52dq4dHOpJ2ai20zwtr0TmZnvGMOwZ35FLSzcA7qq29Wv4pJLPeF9rWsFHeP1JJ2ebGhaIOay4QvnZYZDTU3sdSgmvtBT1Fk6tV1f7AE__aaPeYm3d5ftheDU4XL9FIyWsd7XF8hhyugAl7ic38mosFJcw11nTdun-IM_Uuc488diJWcBKpLdC5PQWvbawDbNbLHHDUhrm3Dxu2Ea9URxvrF7vVMZSaxoMmNFNsWXpA5c1fTX7g5kLTn1UHkIqrn5p7X-y9JW9sHSaXI6iSTyKomg2nkynUcB2LB1OJ5fhJJ6M4uksTJJkFL0F7M8eMLwcxxQXJrNwFsZxQveUFabddbcZaiw0V7pRlqVJEgcMc2G1WbpXdv_Yvv0H7UGAqg?type=png)](https://mermaid.live/edit#pako:eNptlP9q2zAQx1_lEHR_OcWx88Pxn2sILSwQlpaxkX9U--polSUjy22zUtg79A33JDtHTqwmPRKQdff9SHc66ZVlOkeWsoIrazcKyKywEmFdcmPhWpcIN_oWVkb_xszCrShRCoUuNOcWF9qU3AL8JBssl4P53Pn4i6gPvoscLu43yjlq4gitYCW5UkIV8AXWaJvKeQ8LHb1HSznpnjBoxxV5A4jCaDwI6TcMYJg7_TU3-TM36JjgWUr_bef1tFGv_cqzR1Q5zLEWhTrVAjfZ1hPGTvgxqTk-odRViaqrJk2IDGEhTOm2Zdu6Hpl7e-icHnxE47NdHdEdpSfcuxgPMO4BC6OVbQnrR5RotfqYlttCF-MRJn1huiSuKMZoCd90IbJTQuacHmB6Vtl_f9871A2tVhje1qxHiH7SwyQ95phJR7m7Oc-kEZ52dq4dHOpJ2ai20zwtr0TmZnvGMOwZ35FLSzcA7qq29Wv4pJLPeF9rWsFHeP1JJ2ebGhaIOay4QvnZYZDTU3sdSgmvtBT1Fk6tV1f7AE__aaPeYm3d5ftheDU4XL9FIyWsd7XF8hhyugAl7ic38mosFJcw11nTdun-IM_Uuc488diJWcBKpLdC5PQWvbawDbNbLHHDUhrm3Dxu2Ea9URxvrF7vVMZSaxoMmNFNsWXpA5c1fTX7g5kLTn1UHkIqrn5p7X-y9JW9sHSaXI6iSTyKomg2nkynUcB2LB1OJ5fhJJ6M4uksTJJkFL0F7M8eMLwcxxQXJrNwFsZxQveUFabddbcZaiw0V7pRlqVJEgcMc2G1WbpXdv_Yvv0H7UGAqg)
---

## Phase 1: Foundation (Days 1–5)

This phase focuses on  preparing hardware and defining the system’s architecture.

  - **Project Planning**
We finalize the project scope, assign responsibilities, and agree on the core technologies: React for the frontend, Flask/Node for the backend, BeagleBone for device control, and MQTT for communication.

  - **Hardware Setup**
Our team prepares the BeagleBone boards, connects relay modules, and verifies basic GPIO operations for controlling lights and fans.

  - **Backend Architecture Design**
We design the backend architecture, define REST API endpoints, MQTT topic structure, and outline the data flow between components.

  - **Device Firmware Development Start**
Initial development begins on the BeagleBone firmware using C or Python. This includes subscribing to MQTT topics and wiring GPIO outputs to physical relays.

  - **Backend Development Start**
The server-side application is initialized. We implement the API layer and integrate MQTT publishers and subscribers to control and monitor devices.

---

## Phase 2: Building the Experience (Days 6–10)

In this phase, we build interactive controls and connect all core components.

  - **Frontend Skeleton**
We draft a React web application, setting up routing, navigation, and a clean dashboard layout with header and sidebar navigation.

  - **Device Control Logic**
Firmware is expanded to include full control logic. Each BeagleBone reliably responds to MQTT commands and confirms GPIO actions with state feedback.

  - **Backend–Device Integration**
We conduct tests from the backend to the devices via MQTT. Device toggles, status updates, and relay actions are verified end-to-end.

  - **Frontend Device UI Components**
Our interface gains interactive `DeviceCard` components — each with a toggle for lights and a speed slider for fans, ready to reflect device state.
  - **Connect Frontend to Backend**
The frontend is wired to the backend APIs. Actions from the web client trigger MQTT commands, and device states are fetched and displayed accordingly.

---

## Phase 3: Realtime Updates, Testing, and Documentation (Days 11–15)

This final phase focuses on enhancing the user experience, enabling real-time updates, and ensuring stability for demo and deployment.

  - **Realtime Update Integration**
We implement WebSocket or MQTT-over-WebSocket integration to push live device status updates to the frontend dashboard without polling.

  - **Logging Panel & Status Feed**
A log panel is introduced to display system activity such as “Light 1 ON” or “Fan speed set to 3,” improving observability and debugging.

  - **UI Polish & Responsiveness**
Styling and UI refinements are applied to ensure a clean, responsive design across devices. We enhance error handling and edge-case behavior.

  - **Full System Testing**
We test the entire system, simulating real-world usage scenarios, checking room-by-room controls, and validating real-time updates.

  - **Final Review & Documentation**
We review the full codebase, write clear documentation and setup guides, and prepares all deliverables for presentation or submission.

---
