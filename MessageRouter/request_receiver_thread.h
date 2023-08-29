#ifndef REQUEST_RECEIVER_THREAD_H
#define REQUEST_RECEIVER_THREAD_H

#include "tcp_constants.h"
#include "message_protocol.h"
#include "tcp_server.h"

DWORD WINAPI request_receiver_thread(LPVOID port);


#endif // !REQUEST_RECEIVER_THREAD_H
