#include "request_receiver_thread.h"

// Setup and Monitor the TCP server for messages from clients
DWORD WINAPI request_receiver_thread(LPVOID request_receiver_config) {
    uint64_t requestID = 0;
    // Initialize TCP server
    SOCKET serverSocket = init_server((uint16_t)(*((int*)REQUEST_RECEIVER_PORT)));

    while (1) {
        // loop, accepting connections
        SOCKET clientSocket = { 0 };
        while (!clientSocket){
            clientSocket = accept_connection(serverSocket);
        }

        // reading request messages
        char clientMsg[MAX_MSG_SIZE];
        uint64_t message;
        uint64_t bytesRead = read_message_from_client(clientSocket, clientMsg);
        if (bytesRead == sizeof(uint64_t)) {  // Ensure we read a full 64-bit message.

            // Convert the received message into a 64-bit number
            memcpy(&message, clientMsg, sizeof(uint64_t));

            // Generate a request id
            requestID++;
            insert_request_id(requestID, &message);
            
            // Push the request onto the RequestsReceivedBuffer
            push_message(message, requestsReceivedBuffer);

            // Send a confirmation for the received message
            uint64_t confirmation;
            encode_confirmation(requestID, &confirmation);  // Assuming that the 'message' contains the request ID
            send_to_client(clientSocket, (const char*)&confirmation, sizeof(uint64_t));

            cleanup_client(clientSocket);
        }
    }

    cleanup_server(serverSocket);
    return 0;
}