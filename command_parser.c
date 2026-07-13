#include <string.h>
#include "command_parser.h"
#include "event_queue.h"
#include "logger.h"

typedef struct
{
    const char *command;
    EventType event;
} CommandEntry;

static CommandEntry commands[] =
{
    { "start",  EVENT_START },
    { "stop",   EVENT_STOP },
    { "status", EVENT_STATUS },
    { "help",   EVENT_HELP },
	{"error", EVENT_ERROR},
	{ "reset", EVENT_RESET }
};

void process_command(const char *command)
{
    int len = sizeof(commands) / sizeof(commands[0]);

    for(int i = 0; i < len; i++)
    {
        if(strcmp(command, commands[i].command) == 0)
        {
            if(!event_queue_push(commands[i].event))
            {
                log_error("Event queue is full");
            }

            return;
        }
    }

    log_error("Unknown command");
	return;
}