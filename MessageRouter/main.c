#include "main.h"

char* LOG_FILE = "C:\\Users\\avons\\Code\\Anatomic\\MessageRouter\\logs\\MessageRouter.log";

MessageBuffer RequestsReceived;
MessageBuffer RequestsSent;

#define REQUEST_PORT 4445
#define RESPONSE_PORT 4446

int main() {
    init_logger(LOG_FILE);

    // Received Requests
    initialize_message_buffer(&RequestsReceived);

    request_receiver_config request_receiver_config = {
        .serverPort = REQUEST_PORT,
        .requestsReceivedBuffer = RequestsReceived
    };

    HANDLE request_receiver;
    request_receiver = CreateThread(NULL, 0, request_receiver_thread, &request_receiver_config, 0, NULL);
    if (request_receiver == NULL) {
        // handle thread creation error
        write_log("Error creating thread for a port.");
    }

    // Sent Requests
    request_dispatcher_config request_dispatcher_config = {
        .requestsReceivedBuffer = RequestsReceived,
        .requestsSentBuffer = RequestsSent
    };

    initialize_message_buffer(&RequestsSent);

    HANDLE request_dispatcher;
    request_dispatcher = CreateThread(NULL, 0, request_dispatcher_thread, &request_dispatcher_config, 0, NULL);
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
