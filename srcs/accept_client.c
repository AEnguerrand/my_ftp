/*
** accept_client.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Fri May 12 16:11:05 2017 Enguerrand Allamel
** Last update Sun May 21 17:02:13 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

static void	print_info(t_ftp_server_info *server_info)
{
  printf("[FTP Server] Port: [%ld] - Path Default: [%s]\n",
	 server_info->port,
	 server_info->path);
}

static void	init_server(t_ftp_server_info *server_info)
{
  int		i;

  i = 1;
  if ((server_info->server.fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    error_server_init("socket", server_info->server.fd);
  server_info->server.addr.sin_family = AF_INET;
  server_info->server.addr.sin_port = htons(server_info->port);
  server_info->server.addr.sin_addr.s_addr = INADDR_ANY;
  if (setsockopt(server_info->server.fd, SOL_SOCKET,
		 SO_REUSEPORT, &i,
		 sizeof(int)) < 0)
    error_server_init("setsockopt", server_info->server.fd);
  else if (bind(server_info->server.fd,
	   (const struct sockaddr*)&server_info->server.addr,
	   sizeof(server_info->server.addr)) < 0)
    error_server_init("bind", server_info->server.fd);
  else if (listen(server_info->server.fd, 100) < 0)
    error_server_init("listen", server_info->server.fd);
  server_info->nb_accept = 0;
}

static void	run_client(t_ftp_client_info client_info)
{
  client_info.ip_addr_public = get_addr_ip(client_info.client.fd,
					   &client_info.client.addr);
  one_client(client_info);
  if (shutdown(client_info.client.fd, SHUT_RDWR) == - 1 ||
      close(client_info.client.fd) == -1)
    exit(EXIT_FAILURE);
  free(client_info.path_default);
  exit(EXIT_SUCCESS);
}

static void		wait_for_connect(t_ftp_server_info *server_info)
{
  t_ftp_client_info	client_info;
  socklen_t		client_size;
  pid_t			pid_one_client;

  while (1)
    {
      printf("[FTP Server] Accept new Client\n");
      client_size = sizeof(client_info.client.addr);
      if ((client_info.client.fd =
		   accept(server_info->server.fd,
			  (struct sockaddr *)&client_info.client.addr,
			  &client_size)) < 0)
	error_server_init("accept", server_info->server.fd);
      client_info.id = server_info->nb_accept;
      client_info.is_debug = 1;
      client_info.server_info = *server_info;
      if ((client_info.path_default = strdup(server_info->path)) == NULL)
	error_server_init("strdup", server_info->server.fd);
      server_info->nb_accept += 1;
      if ((pid_one_client = fork()) < 0)
	error_server_init("fork", server_info->server.fd);
      else if (pid_one_client == 0)
	run_client(client_info);
      free(client_info.path_default);
    }
}

int accept_client(t_ftp_server_info *server_info)
{
  printf("[FTP Server] Starting server.\n");
  print_info(server_info);
  init_server(server_info);
  wait_for_connect(server_info);
  close(server_info->server.fd);
  printf("[FTP Server] Halt server.\n");
  return (EXIT_SUCCESS);
}
