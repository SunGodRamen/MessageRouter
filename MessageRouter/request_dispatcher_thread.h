#ifndef REQUEST_DISPATCHER_THREAD_H
#define REQUEST_DISPATCHER_THREAD_H

#include "tcp_constants.h"
#include "message_protocol.h"
#include "tcp_server.h"

#include <stdbool.h>

DWORD WINAPI request_dispatcher_thread(LPVOID param);


#endif // !REQUEST_DISPATCHER_THREAD_H
