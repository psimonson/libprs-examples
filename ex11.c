/*
 * ex11.c - Simple program for networking showing disconnecting when
 *          all clients disconnect.
 *
 * Author: Philip R. Simonson
 * Date  : 06/05/2020
 *
 ***************************************************************************
 */

#include <stdio.h>
#include <stdbool.h>

#include "unused.h"
#include "sockhelp.h"
#include "sockpoll.h"

static int clients = 0; /* Current number of connected clients */

/* Handle what happens for every new connection.
 */
static void on_connect(sock_t *sock)
{
	printf("Server: Saying hi to %s\n", get_addr_socket(sock));
	writef_socket(sock, "Server: Hello.\r\n");
	clients++;
}
/* Handle disconnect from client.
 */
static void on_disconnect(sock_t *UNUSED(sock), int *done)
{
	clients--;
	if(clients <= 0)
		*done = 1;
}
/* Handle client data for connection.
 */
static int on_data(sock_t *sock, int *UNUSED(done))
{
	writef_socket(sock, "Hello world, this is a test.\r\n");
	return 0;
}
/* Entry point for test.
 */
int main(void)
{
	sock_t *s;
	socket_startup();

	if(server_socket(&s, "8000")) {
		fprintf(stderr, "Error: %s\n", get_error_socket(s));
		return 1;
	}
	set_server_socket(s);
	poll_multiple_socket(s, on_connect, on_data, on_disconnect);
	socket_shutdown();
	return 0;
}
