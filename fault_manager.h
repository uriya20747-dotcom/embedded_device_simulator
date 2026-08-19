#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef enum
{
    FAULT_NONE           = 0,
    FAULT_UART_TIMEOUT   = (1U << 0),
    FAULT_SENSOR_FAILURE = (1U << 1),
    FAULT_INTERNAL_ERROR = (1U << 2)
} FaultType;

typedef enum
{
    FAULT_SEVERITY_WARNING,
    FAULT_SEVERITY_ERROR,
    FAULT_SEVERITY_CRITICAL
} FaultSeverity;

typedef struct
{
    FaultType fault;
    FaultSeverity severity;
    const char *name;
} FaultInfo;

void fault_manager_init(void);

void fault_manager_report(FaultType fault);

void fault_manager_clear(FaultType fault);

bool fault_manager_is_active(FaultType fault);

bool fault_manager_has_active_faults(void);

int fault_manager_get_fault_count(void);

const FaultInfo *
fault_manager_get_fault_info(FaultType fault);

const FaultInfo *
fault_manager_get_fault_by_index(int index);

void fault_manager_process(void);

void fault_manager_reset(void);

#endif