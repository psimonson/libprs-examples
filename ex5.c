/**
 * @file ex5.c
 * @author Philip R. Simonson
 * @date 01/10/2020
 * @brief Simple example of my poll socket function it's a simple
 * cheezey multi-person chat server.
 ******************************************************************
 * @details This file was written as an example of how you can use
 * my sockhelp and sockpoll libraries with each other. To handle a
 * multiple connection server.
 */

#include <stdio.h>
#include <string.h>

#include "sockhelp.h"
#include "sockpoll.h"

/* Strip off new line characters.
 */
void strip_newline(char *s)
{
	while(*s) {
		if(*s == '\r' || *s == '\n')
			break;
		s++;
	}
	*s = 0;
}
/* Client connected.
 */
static void on_connect(sock_t *sock)
{
	writef_socket(sock, "Welcome to my simple chat server program.\r\n"
		"Have phun :-)\r\n\r\n");
}
/* Client handling function.
 */
static int handle_client(sock_t *sock, int *done)
{
	char data[BUFSIZ];
	int bytes;
	bytes = recv_data(sock, data, sizeof(data), 0);
	if(bytes > 0) {
		struct pollfd fds[POLL_MAXCONN];
		int i;

		for(i = 0; i < get_poll_count(); i++)
			fds[i] = get_poll_fd(i);

		for(i = 0; i < get_poll_count(); i++) {
			if(fds[i].sock != get_server_socket()
				&& fds[i].sock != sock) {
				strip_newline(data);
				bytes = writef_socket(fds[i].sock,
					"Client [%s]: %s\r\n",
					get_addr_socket(sock),
					data);
				if(bytes < 0) {
					printf("Server: Sending message failed from [%s].\n",
						get_addr_socket(fds[i].sock));
				}
			}
		}
		memset(data, 0, sizeof(data));
	}
	return bytes;
}
/* Simple chat server program.
 */
int main()
{
	sock_t *server;
	socket_startup();
	if(server_socket(&server, "8000"))
		return 1;
	set_server_socket(server);
	poll_multiple_socket(server, on_connect, handle_client);
	socket_shutdown();
	return 0;
}
