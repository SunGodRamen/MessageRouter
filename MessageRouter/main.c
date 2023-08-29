#include "main.h"

char* LOG_FILE = "C:\\Users\\avons\\Code\\Anatomic\\MessageRouter\\logs\\MessageRouter.log";

MessageBuffer RequestsReceived;
MessageBuffer RequestsSent;

int main() {
    init_logger(LOG_FILE);

    // Received Requests
    initialize_message_buffer(&RequestsReceived);
    HANDLE request_receiver;
    request_receiver = CreateThread(NULL, 0, request_receiver_thread, &RequestsReceived, 0, NULL);
    if (request_receiver == NULL) {
        // handle thread creation error
        write_log("Error creating thread for a port.");
    }

    // Sent Requests
    initialize_message_buffer(&RequestsSent);
    HANDLE request_dispatcher;
    request_dispatcher = CreateThread(NULL, 0, request_dispatcher_thread, &RequestsSent, 0, NULL);
    if (request_dispatcher == NULL) {
        write_log("Error creating client test thread.");
    }

    // Received Responses
 
    // Sent Responses

    // Wait for all threads to exit
    WaitForSingleObject(request_receiver_thread, INFINITE);
    CloseHandle(request_receiver_thread);
    WaitForSingleObject(request_dispatcher_thread, INFINITE);
    CloseHandle(request_dispatcher_thread);

    close_logger();
    return 0;
}
