/**
 * @file ex3.c
 * @author Philip R. Simonson
 * @date 01/10/2020
 * @brief Very simple usage example of sockhelp.
 *****************************************************************
 * @details Just shows a very simple way of using my sockhelp
 * library.
 */

#include <stdio.h>
#include "sockhelp.h"

int main()
{
	char buf[32];
	int bytes;
	sock_t *server, *client;
	socket_startup();
	server_socket(&server, "8000");
	if(get_errori_socket(server) != SOCKERR_OKAY)
		return 1;
	client = accept_socket(server);
	writef_socket(client, "Hello world, this is a %s.\r\n", "test");
	bytes = recv_data(client, buf, 32, 0);
	buf[bytes] = 0;
	printf("Data:\n%s\n", buf);
	destroy_socket(client);
	destroy_socket(server);
	socket_shutdown();
	return 0;
}
