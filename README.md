# Embedded Device Simulator

An event-driven embedded firmware simulator written in C.
The project demonstrates modular firmware architecture using a State Machine,
Event Queue, Dispatch Table and hardware abstraction.

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

---

## Future Work (Version 1.3)

- Fault Manager
- Multiple Timers
- Additional Device Drivers
- Configuration Manager
- More Embedded Peripherals