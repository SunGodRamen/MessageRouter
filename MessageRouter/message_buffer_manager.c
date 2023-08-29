#include "message_buffer_manager.h"

void initialize_message_buffer(MessageBuffer* buffer) {
    buffer->head = 0;
    buffer->tail = 0;
    InitializeCriticalSection(&buffer->mutex);
    InitializeConditionVariable(&buffer->not_empty);
    InitializeConditionVariable(&buffer->not_full);
}

void push_message(MessageBuffer* buffer, uint64_t message) {
    EnterCriticalSection(&buffer->mutex);

    while ((buffer->head + 1) % MAX_BUFFER_SIZE == buffer->tail) {
        SleepConditionVariableCS(&buffer->not_full, &buffer->mutex, INFINITE);
    }

    buffer->buffer[buffer->head] = message;
    buffer->head = (buffer->head + 1) % MAX_BUFFER_SIZE;

    WakeConditionVariable(&buffer->not_empty);
    LeaveCriticalSection(&buffer->mutex);
}

uint64_t pop_message(MessageBuffer* buffer) {
    EnterCriticalSection(&buffer->mutex);

    while (buffer->head == buffer->tail) {
        SleepConditionVariableCS(&buffer->not_empty, &buffer->mutex, INFINITE);
    }

    uint64_t message = buffer->buffer[buffer->tail];
    buffer->tail = (buffer->tail + 1) % MAX_BUFFER_SIZE;

    WakeConditionVariable(&buffer->not_full);
    LeaveCriticalSection(&buffer->mutex);

    return message;
}
