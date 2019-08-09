#include <sys/types.h>

#include <Winsock2.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <errno.h>

#include <stdint.h>

#pragma warning( disable : 4996)

#pragma comment(lib, "Ws2_32.lib")

#define CAPACITY UINT8_MAX

uint8_t buf[CAPACITY];  //newbuf[CAPACITY - 5];

int header_is_ok =
(buf[0] == 0 && buf[1] == 0 && buf[2] == 0 && buf[3] == 0);


int main()

{
	char sendMessage[1024], receiveMessage[1024];

	int sock, connected, result;

	struct sockaddr_in serverAdd, clientAdd;

	int iResult;

	int length;


	// Initialize Winsock

	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}



	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)

	{

		perror("Socket creation is failed");

		exit(1);

	}


	char optval = 1;

	serverAdd.sin_family = AF_INET;

	serverAdd.sin_port = htons(5000);

	serverAdd.sin_addr.s_addr = INADDR_ANY;

	memset(&(serverAdd.sin_zero), 8, sizeof(int));




	if (bind(sock, (struct sockaddr*) & serverAdd, sizeof(struct sockaddr)) == -1)

	{

		perror("Unable to bind");

		exit(1);

	}

	if (listen(sock, 3) == -1)

	{

		perror("Listen");

		exit(1);

	}


	printf("TCPServer Waiting for client connection\n");

	fflush(stdout);

	length = sizeof(struct sockaddr_in);

	connected = accept(sock, (struct sockaddr*) & clientAdd, &length);

	printf("%d\n", connected);

	printf("Server is connected with IP address %s and port %d    \n", inet_ntoa(clientAdd.sin_addr), ntohs(clientAdd.sin_port));





	while (1)

	{
		printf(" SEND the message : ");
		uint8_t* contents = buf + 5;
		fgets(sendMessage, 100, stdin);

		send(connected, sendMessage, strlen(sendMessage), 0);

		result = recv(connected, receiveMessage, 512, 0);


		if (header_is_ok) {
			uint8_t length = buf[4];

			if (length > 0 && length < CAPACITY - 5) {

				memcpy(receiveMessage, contents, length);
			}
		}

		printf("length: %d\n", length);

		receiveMessage[result] = '\0';

		memset(contents, 0, sizeof(buf[0]));

		printf("Received message : %s \n", receiveMessage);

		fflush(stdout);


	}


	return 0;

}
