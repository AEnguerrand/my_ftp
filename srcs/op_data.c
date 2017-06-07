/*
** op_data.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Sun May 21 11:45:41 2017 Enguerrand Allamel
** Last update Sun May 21 17:29:54 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

static void		init_data(t_ftp_client_data	*client_data,
				     t_ftp_mode		mode)
{
  client_data->cmd = FTP_DATA_CMD_NOT_SET;
  client_data->mode = mode;
  client_data->arg = NULL;
}

t_ftp_client_data	init_client_data_info(t_ftp_client_info	*client_info,
					      size_t		*port,
					      t_ftp_mode	mode,
					      const char	*cmd)
{
  t_ftp_client_data	client_data;

  init_data(&client_data, mode);
  client_data.client_control = client_info->client;
  if ((client_data.server.fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    error_server_init("socket", client_info->server_info.server.fd);
  client_data.server.addr.sin_family = AF_INET;
  if (client_data.mode == FTP_MODE_PASV)
    {
      client_data.server.addr.sin_port = htons(*port);
      client_data.server.addr.sin_addr.s_addr = INADDR_ANY;
      while (bind(client_data.server.fd,
		  (const struct sockaddr *)&client_data.server.addr,
		  sizeof(client_data.server.addr)) < 0)
	{
	  *port = rand() % (65635 - 1024) + 1024;
	  client_data.server.addr.sin_port = htons(*port);
	}
      if (listen(client_data.server.fd, 100) < 0)
	error_server_init("listen", client_info->server_info.server.fd);
    }
  else if (client_data.mode == FTP_MODE_ACTIVE)
    init_client_data_port(&client_data, cmd);
  return (client_data);
}
