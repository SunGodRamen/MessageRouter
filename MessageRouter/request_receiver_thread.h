#ifndef REQUEST_RECEIVER_THREAD_H
#define REQUEST_RECEIVER_THREAD_H

#include "tcp_constants.h"
#include "message_protocol.h"
#include "tcp_server.h"
#include "message_buffer_manager.h"

typedef struct {
	int serverPort;
	MessageBuffer requestsReceivedBuffer;
} request_receiver_config;

DWORD WINAPI request_receiver_thread(LPVOID port);


#endif // !REQUEST_RECEIVER_THREAD_H
