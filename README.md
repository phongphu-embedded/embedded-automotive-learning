# Embedded Automotive Learning Journey

**Author:** Nguyen Phong Phu  
**Goal:** Junior Embedded Software Engineer — Automotive  
**Target:** Bosch Vietnam, Continental, VinFast  

---

## About Me
- Final year student, Automotive Engineering, HUTECH University (GPA: 3.55)
- Thesis: Arduino-based lifting system control  
- Background: Math & Physics tutor — strong logical thinking foundation

---

## Learning Roadmap

| Phase | Topics | Status |
|-------|--------|--------|
| Phase 1 | C Programming Basics | ✅ Completed |
| Phase 2 | STM32 Bare-metal | 🔄 Coming soon |
| Phase 3 | CAN Bus | 🔄 Coming soon |
| Phase 4 | FreeRTOS | 🔄 Coming soon |
| Phase 5 | AUTOSAR Classic | 🔄 Coming soon |

---

## Phase 1 — C Programming Basics

> All code follows **MISRA C** coding standards

### Day 1 — Variables & Data Types
**Concepts:** Variable declaration, data types (int/float/char),
printf formatting  
**File:** `phase1-C-basics/day01-variables/ngay1.c`

### Day 2 — Operators & Conditions
**Concepts:** Arithmetic operators, comparison, boolean logic, if/else  
**Project:** ECU Fault Detector — monitors temperature,
battery voltage, headlight status  
**File:** `phase1-C-basics/day02-conditions/ecu_fault_detector.c`

### Day 3 — Loops
**Concepts:** for/while/do-while, break/continue, infinite loop  
**Projects:**
- Series resistor calculator (automotive circuit simulation)
- Engine RPM Monitor with flag-based alert system
- Circular Buffer implementation using modulo arithmetic  

**Files:** `phase1-C-basics/day03-loops/`

### Day 4 — Arrays & Memory
**Concepts:** Array memory layout, buffer overflow, zero-based index,
circular buffer  
**Projects:**
- Multi-sensor buffer with min/max/average
- ECU Monitor System: 3-sensor fault classification ← **Capstone**  

**Files:** `phase1-C-basics/day04-arrays/`

### Day 5 — Pointers
**Concepts:** Address-of (&), dereference (*), pass-by-pointer,
pointer arithmetic, array-pointer equivalence  
**Projects:**
- Pointer basics: RAM address inspection
- Swap function: pass-by-value vs pass-by-pointer
- Array traversal using pointer arithmetic
- Sensor Data Processor: 3 functions with pointer parameters  

**Files:** `phase1-C-basics/day05-pointers/`

---

## Key Patterns Learned
- `flag` pattern for one-shot alerts in safety systems
- Circular buffer with modulo arithmetic
- MISRA C: `/* */` comments, `0.0f` literals, single return
- Sensor data processing loop structure used in real ECU firmware