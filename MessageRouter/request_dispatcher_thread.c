#include "request_dispatcher_thread.h"

// Check for message on the buffer, if present, pop, find destination, send, log confirmation
DWORD WINAPI request_dispatcher_thread(LPVOID request_dispatcher_config) {

    uint64_t queuedRequest = { 0 };
    while (1) {
        
        while (!queuedRequest) {
            pop_message(request_dispatcher_config->requestsReceivedBuffer, &queuedRequest);
        }

        // find Client ip and port using request uri
        uint64_t uri;
        extract_request_uri(&queuedRequest,uri);

        char* targetIp;
        int targetPort;
        mapUriToServerIP(&uri, &targetIp, &targetPort);
        SOCKET clientSocket = init_client(targetIp, targetPort);

        // send request and listen for confirmation
        char buffer[MAX_MSG_SIZE];
        send_to_server(clientSocket, (const char*)&queuedRequest, sizeof(queuedRequest)); // Send encoded 64-bit request
        uint64_t response_data = 0;
        MessageType response_type;
        int timeoutCounter = 0;

        while (true) {  // Loop until confirmation or timeout
            int bytesRead = read_message_from_server(clientSocket, (char*)&response_data);

            if (response_data != 0) {
                interpret_message(response_data, &response_type);
                if (bytesRead == sizeof(uint64_t) && response_type == CONFIRM_MESSAGE) {
                    break;  // Break out of the loop if confirmation is received
                }

                if (++timeoutCounter >= 10) {  // This will give a total of 10*SOCKET_TIMEOUT_MS time for waiting for the confirmation.
                    write_log("Did not receive a proper confirmation from the server.");
                    break;
                }
            }
        }
        // push request to sent requests buffer

        // Cleanup memory
    }
    return 0;
}

void mapUriToServerIP(uint64_t uri, char* targetIp, int* targetPort) {
    switch (uri) {
    case 0x1:
        targetIp = "127.0.0.1";
        targetPort = 4444;
    }
}