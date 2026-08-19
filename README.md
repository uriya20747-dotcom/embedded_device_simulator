# Embedded Device Simulator

An event-driven embedded firmware simulator written in C.

The project demonstrates modular firmware architecture using a State Machine,
Event Queue, Dispatch Table, hardware abstraction, fault management,
fault severity classification and recovery mechanisms.

---

## Version 1.1

### Features

- Command Parser
- Ring Buffer Event Queue
- Event Dispatcher (Dispatch Table)
- State Machine
- Logger
- Event-Driven Architecture

---

## Version 1.2

### New Features

- Device Controller layer
- LED Driver abstraction
- Internal LED Driver State
- Software Timer Manager
- Event Timeout support
- Event Statistics Manager
- System Statistics
- ERROR state
- RESET event
- State Transition Rules
- State transition validation
- Hardware output updates only after successful state transitions

---

## Version 1.3

### New Features

- Fault Manager
- Multiple active fault tracking using a bitmask
- Fault metadata table
- Fault severity classification:
  - WARNING
  - ERROR
  - CRITICAL
- Fault reporting and clearing APIs
- Active fault reporting through system STATUS
- Pending fault event handling
- Automatic recovery for ERROR-level faults
- Manual RESET requirement for CRITICAL faults
- RESET protection while active faults remain
- Dedicated State Machine recovery path
- Device status reporting through the Device Controller
- Fault handling separated from system state transitions
- Internal fault implementation hidden behind the Fault Manager API

### Fault Severity Behavior

#### WARNING

- Fault is recorded by the Fault Manager
- Fault appears in system STATUS
- System continues operating normally
- No transition to ERROR state is generated
- Fault can be cleared without RESET

#### ERROR

- Fault is recorded by the Fault Manager
- EVENT_ERROR is generated
- System transitions to ERROR state
- Fault appears in system STATUS
- When the fault is cleared and no other ERROR/CRITICAL faults remain,
  the system automatically recovers to IDLE

#### CRITICAL

- Fault is recorded by the Fault Manager
- EVENT_ERROR is generated
- System transitions to ERROR state
- Fault appears in system STATUS
- Clearing the fault does not automatically recover the system
- Manual RESET is required before returning to normal operation
- RESET is rejected while active faults remain

---

## Project Structure

- command_parser
- event_queue
- event_dispatcher
- state_machine
- logger
- device_controller
- led_driver
- timer_manager
- statistics_manager
- fault_manager

---

## Architecture Overview

The simulator follows an event-driven architecture.

Commands and internal system conditions generate events that are placed in
the Event Queue. The Event Dispatcher processes these events and coordinates
state transitions and device behavior.

The State Machine controls the system operating state, while the Device
Controller translates system states into driver-level actions.

The Fault Manager independently tracks active faults and their severity.
Faults can influence system behavior by generating events without directly
changing the State Machine.

This separation keeps system state management, fault management and hardware
control independent from each other.

---

## Fault Management Architecture

The Fault Manager supports multiple simultaneous faults.

Active faults are stored internally using a bitmask. The internal bitmask is
not exposed to other modules. Instead, the Fault Manager provides APIs for
querying active faults and retrieving their metadata.

Each fault contains metadata describing its type, name and severity.

The system distinguishes between WARNING, ERROR and CRITICAL faults so that
different recovery policies can be applied depending on fault severity.

Only the Event Dispatcher is responsible for requesting system state
transitions. The Fault Manager reports system conditions through events rather
than modifying the State Machine directly.

---

## Known Simulator Limitation

The current software timer is based on main-loop ticks rather than a real
hardware time source.

Because console input is blocking, timer behavior in the PC simulator does not
represent precise real-time behavior.

A hardware timer will replace this simulated timing mechanism during STM32
integration.

---

## Future Work

- STM32 NUCLEO-F446RE hardware integration
- GPIO hardware control
- UART communication
- Hardware timers and interrupts
- Logic analyzer based debugging
- Additional Device Drivers
- Additional hardware fault sources