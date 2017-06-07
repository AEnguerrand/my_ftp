/*
** one_client.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Fri May 12 15:48:46 2017 Enguerrand Allamel
** Last update Sun May 21 17:26:17 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

static void	init_connection(t_ftp_client_info *client_info)
{
  client_info->username = NULL;
  client_info->is_log = 0;
  client_info->client_data_last.mode = FTP_MODE_NOT_SET;
  send_response(client_info, 220, "Service ready for new user.");
}

int	check_is_log(t_ftp_client_info *client_info)
{
  if (!client_info ||
      client_info->is_log != 1 ||
      !client_info->path_default ||
      !client_info->username)
    {
      send_response(client_info, 530, "Not logged in.");
      return (0);
    }
  return (1);
}

void	one_client(t_ftp_client_info client_info)
{
  int	res;

  printf("[FTP Server] New Client [%ld]: IP Client: [%s] - IP Server: [%s]\n",
	 client_info.id,
	 inet_ntoa(client_info.client.addr.sin_addr),
	 inet_ntoa(client_info.server_info.server.addr.sin_addr));
  init_connection(&client_info);
  while ((res = read_command(&client_info)) >= 0 && res != 20);
  if (res <= -1)
    send_response(&client_info, 500, "Fatal error.");
  if (client_info.username)
    free(client_info.username);
  printf("[FTP Server] Client [%ld] disconnected\n", client_info.id);
}
