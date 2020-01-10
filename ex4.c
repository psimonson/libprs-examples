/*
 * @file ex4.c
 * @author Philip R. Simonson
 * @date 01/10/2019
 * @brief Simple web server application using my socket library.
 ********************************************************************
 * @details This web server only supports HTML code. Does not support
 * JavaScript/PHP/Python/Perl/Ruby/etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sockhelp.h"
#include "file.h"

int handle_client(sock_t *sock)
{
	char buf[1024], path[128];
	if(recv_data(sock, buf, 1023, 0) > 0) {
		if(sscanf(buf, "GET %127s", path) == 1) {
			writef_socket(sock, "HTTP/1.1 200 OK\r\n\r\n");
			if(strcmp(path, "/") == 0) {
				char *data;
				file_t *file;
				int len;
				file = open_file("index.html", "rt");
				if(file == NULL) {
					printf("Error: opening index.html.\n");
					return 1;
				}
				len = get_size_file(file);
				data = (char*)malloc(sizeof(char)*(len+1));
				if(data == NULL) {
					close_file(file);
					return 1;
				}
				while(read_file(file, data, sizeof(char), len) > 0);
				/*send_data(sock, data, len, 0);*/
				data[len] = 0;
				writef_socket(sock,
					"%s\r\n",
					data);
				close_file(file);
				free(data);
			} else if(strcmp(path, "/hidden") == 0) {
				writef_socket(sock,
					"<html><body bgcolor=\"#000000\""
					"text=\"#00ff00\"><center><form "
					"action=\"/test2a\" method=\"GET\""
					"><table cellpadding=\"2px\" cell"
					"spacing=\"2px\">"
					"<tr>"
					"  <td><input type=\"edit\" name="
					"\"search\" value=\"Search List\""
					" /></td>"
					"  <td><input type=\"submit\" name="
					"\"searchbtn\" />"
					"</td></tr></table></form></center>"
					"</body></html>");
			} else if(strncmp(path, "/test2a?", 8) == 0) {
				char searchstr[128];
				if(sscanf(path, "/test2a?%s",
					searchstr) == 1) {
					char buf[32];
					file_t *file;
					int bytes;
					file = open_file("tmp.out", "wt");
					if(get_error_file() != FILE_ERROR_OKAY) {
						close_socket(sock);
						return 1;
					}
					writef_file(file,
					"<html><body bgcolor=\"#000000\""
					" text=\"#00ff00\"><p>");
					writef_file(file,
					"\r\n%s</p></body></html>", searchstr);
					close_file(file);
					file = open_file("tmp.out", "rt");
					if(get_error_file() != FILE_ERROR_OKAY) {
						remove("tmp.out");
						return 1;
					} else {
						while((bytes = read_file(file, buf, 1, 32)) > 0)
							send_data(sock, buf, bytes, 0);
					}
					strcpy(buf, get_name_file(file));
					close_file(file);
					remove(buf);
				}
			} else if(strcmp(path, "/favicon.ico") == 0) {
				/* TODO: Add icon handling code */
			} else if(strcmp(path, "/bitmap") == 0) {
				/* TODO: Serve bitmap to browser */
				file_t *file;
				char buf[32];
				int bytes;

				file = open_file("out.bmp", "rb");
				if(get_error_file() != FILE_ERROR_OKAY)
					return 1;

				while((bytes = read_file(file, buf, 1, 32)) > 0) {
					send_data(sock, buf, bytes, 0);
				}
				close_file(file);
			} else {
				printf("Bad request '%s'\n", path);
				close_socket(sock);
				return 1;
			}
		}
	}
	destroy_socket(sock);
	return 0;
}

int main()
{
	sock_t *server, *client;
	int done;
	socket_startup();
	server_socket(&server, "8000");
	if(get_errori_socket(server) != SOCKERR_OKAY)
		return 1;
	done = 0;
	while(!done) {
		client = accept_socket(server);
		done = handle_client(client);
	}
	destroy_socket(server);
	socket_shutdown();
	return 0;
}
