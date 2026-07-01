#include <stdio.h>
#include <string.h>
#include "state_machine.h"
#include "command_parser.h"
#include "event_queue.h"
#include "event_dispatcher.h"


int main(void)
{
    char command[100];
    EventType event;

    state_machine_init();
    event_queue_init();

    printf("System Booting...\n");
    printf("Type 'help' for commands\n");

    while(1)
    {
        printf("> ");

        if(fgets(command, sizeof(command), stdin) != NULL)
        {
            command[strcspn(command, "\n")] = '\0';
            process_command(command);

            while(event_queue_pop(&event))
            {
                dispatch_event(event);
            }
        }
    }

    return 0;
}