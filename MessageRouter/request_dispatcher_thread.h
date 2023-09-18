#ifndef REQUEST_DISPATCHER_THREAD_H
#define REQUEST_DISPATCHER_THREAD_H

#include "tcp_constants.h"
#include "message_protocol.h"
#include "tcp_server.h"

#include <stdbool.h>

typedef struct {
	MessageBuffer requestsReceivedBuffer;
	MessageBuffer requestsSentBuffer;
} request_dispatcher_config;

DWORD WINAPI request_dispatcher_thread(LPVOID request_dispatcher_config);


#endif // !REQUEST_DISPATCHER_THREAD_H
