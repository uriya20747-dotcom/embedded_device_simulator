#include "fault_manager.h"
#include "event_queue.h"

static uint32_t active_faults;
static bool error_event_pending;
static bool reset_required;
static bool fault_cleared_event_pending;
static bool has_active_error_fault(void);


static const FaultInfo fault_table[] =
{
    {
        FAULT_UART_TIMEOUT,
        FAULT_SEVERITY_CRITICAL,
        "UART TIMEOUT"
    },
    {
        FAULT_SENSOR_FAILURE,
        FAULT_SEVERITY_ERROR,
        "SENSOR FAILURE"
    },
    {
        FAULT_INTERNAL_ERROR,
        FAULT_SEVERITY_CRITICAL,
        "INTERNAL ERROR"
    }
};

void fault_manager_init(void)
{
    active_faults = FAULT_NONE;
	reset_required = false;
	fault_cleared_event_pending = false;
}

void fault_manager_report(FaultType fault)
{
    const FaultInfo *info = fault_manager_get_fault_info(fault);

    if (info == NULL)
    {
        return;
    }

    bool had_error_fault = has_active_error_fault();

    active_faults |= (uint32_t)fault;

    if (info->severity == FAULT_SEVERITY_CRITICAL)
    {
        reset_required = true;
    }

    if (info->severity != FAULT_SEVERITY_WARNING &&
        !had_error_fault)
    {
        error_event_pending = true;
    }
}

void fault_manager_clear(FaultType fault)
{
    const FaultInfo *info = fault_manager_get_fault_info(fault);

    if (info == NULL)
    {
        return;
    }

    /* Clear the fault */
    active_faults &= ~((uint32_t)fault);

    /*
     * WARNING does not affect the system state,
     * so clearing it requires no recovery event.
     */
    if (info->severity == FAULT_SEVERITY_WARNING)
    {
        return;
    }

    /*
     * A critical fault requires an explicit RESET,
     * even after the fault itself disappears.
     */
    if (reset_required)
    {
        return;
    }

    /*
     * Auto-recover only when no ERROR/CRITICAL
     * faults remain active.
     */
    if (!has_active_error_fault())
    {
        fault_cleared_event_pending = true;
    }
}

void fault_manager_process(void)
{
    if (error_event_pending)
    {
        if (event_queue_push(EVENT_ERROR))
        {
            error_event_pending = false;
        }
    }

    if (fault_cleared_event_pending)
    {
        if (event_queue_push(EVENT_FAULT_CLEARED))
        {
            fault_cleared_event_pending = false;
        }
    }
}

bool fault_manager_is_active(FaultType fault)
{
    return (active_faults & (uint32_t)fault) != 0U;
}

bool fault_manager_has_active_faults(void)
{
    return active_faults != FAULT_NONE;
}

const FaultInfo *fault_manager_get_fault_info(FaultType fault)
{
    int len = sizeof(fault_table) / sizeof(fault_table[0]);

    for (int i = 0; i < len; i++)
    {
        if (fault_table[i].fault == fault)
        {
            return &fault_table[i];
        }
    }

    return NULL;
}

int fault_manager_get_fault_count(void)
{
    int count = 0;
    int len = sizeof(fault_table) / sizeof(fault_table[0]);

    for (int i = 0; i < len; i++)
    {
        if ((active_faults & (uint32_t)fault_table[i].fault) != 0U)
        {
            count++;
        }
    }

    return count;
}

const FaultInfo *fault_manager_get_fault_by_index(int index)
{
    int active_index = 0;
    int len = sizeof(fault_table) / sizeof(fault_table[0]);

    if (index < 0)
    {
        return NULL;
    }

    for (int i = 0; i < len; i++)
    {
        if ((active_faults & (uint32_t)fault_table[i].fault) != 0U)
        {
            if (active_index == index)
            {
                return &fault_table[i];
            }

            active_index++;
        }
    }

    return NULL;
}

static bool has_active_error_fault(void)
{
    int len = sizeof(fault_table) / sizeof(fault_table[0]);

    for (int i = 0; i < len; i++)
    {
        if ((active_faults & (uint32_t)fault_table[i].fault) != 0U)
        {
            if (fault_table[i].severity == FAULT_SEVERITY_ERROR ||
                fault_table[i].severity == FAULT_SEVERITY_CRITICAL)
            {
                return true;
            }
        }
    }

    return false;
}

void fault_manager_reset(void)
{
    reset_required = false;
}
