#ifndef MESSAGE_BUFFER_MANAGER_H
#define MESSAGE_BUFFER_MANAGER_H

#include <windows.h>
#include <stdint.h>

#define MAX_BUFFER_SIZE 100

typedef struct {
    uint64_t buffer[MAX_BUFFER_SIZE];
    int head;
    int tail;
    CRITICAL_SECTION mutex;
    CONDITION_VARIABLE not_empty;
    CONDITION_VARIABLE not_full;
} MessageBuffer;

void initialize_message_buffer(MessageBuffer* buffer);
void push_message(MessageBuffer* buffer, uint64_t message);
uint64_t pop_message(MessageBuffer* buffer);

#endif
