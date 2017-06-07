/*
** one_client_data.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 15 12:50:11 2017 Enguerrand Allamel
** Last update Sun May 21 17:29:09 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

static t_my_ftp_op_data_func g_op_data[] =
{
	{FTP_DATA_CMD_LIST, &op_data_file},
	{FTP_DATA_CMD_RETR, &op_data_retr},
	{FTP_DATA_CMD_STOR, &op_data_stor},
	{FTP_DATA_CMD_NOT_SET, NULL}
};

static void	one_client_data_init_pasv(t_ftp_client_data	*client_data)
{
  socklen_t	client_data_size;

  if (client_data->mode == FTP_MODE_PASV)
    {
      client_data_size = sizeof(client_data->client.addr);
      if ((client_data->client.fd =
		   accept(client_data->server.fd,
			  (struct sockaddr *)&client_data->client.addr,
			  &client_data_size)) < 0)
	error_server_init("accept", client_data->server.fd);
    }
  else if (client_data->mode == FTP_MODE_ACTIVE)
    {
      if (connect(client_data->server.fd,
		  (const struct sockaddr *)&client_data->server.addr,
		  sizeof(client_data->server.addr)) < 0)
	error_server_init("connect", client_data->server.fd);
      client_data->client.fd = client_data->server.fd;
    }
}

static int	one_client_data(t_ftp_client_data	client_data,
				const char		*arg)
{
  int		i;

  if (client_data.mode == FTP_MODE_PASV ||
	  client_data.mode == FTP_MODE_ACTIVE)
    one_client_data_init_pasv(&client_data);
  else
    return (1);
  i = 0;
  while (client_data.cmd != FTP_DATA_CMD_NOT_SET && g_op_data[i].func_ptr &&
	 g_op_data[i].cmd != client_data.cmd)
    i += 1;
  if (g_op_data[i].cmd == client_data.cmd)
    return (g_op_data[i].func_ptr(&client_data, arg));
  return (1);
}

static int	run_in_ftp_active(t_ftp_client_info	*client_info,
				  const char		*arg)
{
  if (one_client_data(client_info->client_data_last, arg) != 0)
    send_response(client_info, 550, "File error, check your arguments.");
  else if (shutdown(client_info->client_data_last.server.fd, SHUT_RDWR)
	   == - 1 ||
      close(client_info->client_data_last.server.fd) == -1)
    return (-1);
  return (0);
}

static int	run_in_ftp_passive(t_ftp_client_info	*client_info,
				   const char		*arg)
{
  int		pid_one_client_data;

  if ((pid_one_client_data = fork()) < 0)
    return (-1);
  else if (pid_one_client_data == 0)
    {
      if (one_client_data(client_info->client_data_last, arg) != 0)
	send_response(client_info, 550, "File error, check your arguments.");
      else if (shutdown(client_info->client_data_last.server.fd, SHUT_RDWR)
	       == - 1 ||
	       close(client_info->client_data_last.server.fd) == -1)
	exit(EXIT_FAILURE);
      exit(EXIT_SUCCESS);
    }
  return (0);
}

int	run_one_client_data(t_ftp_client_info	*client_info,
			    t_ftp_data_cmd	data_cmd,
			    const char		*arg)
{
  if (client_info->client_data_last.mode == FTP_MODE_NOT_SET)
    {
      send_response(client_info, 425, "Use PORT or PASV first.");
      return (1);
    }
  client_info->client_data_last.cmd = data_cmd;
  client_info->client_data_last.arg = arg;
  if (client_info->client_data_last.mode == FTP_MODE_PASV &&
      run_in_ftp_passive(client_info, arg) != 0)
    return (-1);
  else if (client_info->client_data_last.mode == FTP_MODE_ACTIVE &&
	  run_in_ftp_active(client_info, arg) != 0)
    return (-1);
  client_info->client_data_last.mode = FTP_MODE_NOT_SET;
  return (0);
}
