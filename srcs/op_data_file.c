/*
** op_data_file.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 15 16:16:51 2017 Enguerrand Allamel
** Last update Sun May 21 17:31:49 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

int	op_data_file(t_ftp_client_data	*client_data,
		     const char		*arg)
{
  int	oldfd;
  char	*ls_cmd;
  char 	*path;

  send_response_fd(client_data->client_control.fd, 150,
		   "Here comes the directory listing.");
  if (arg)
    {
      if (!(path = realpath(arg, NULL)) ||
	  !(ls_cmd = malloc(11 + strlen(path) + 14)) ||
	  !strcat(ls_cmd, "/bin/ls -l ") || !strcat(ls_cmd, path) ||
	  !strcat(ls_cmd, " | tail -n +2"))
	return (-1);
    }
  else if (!(ls_cmd = strdup("/bin/ls -l | tail -n +2")))
    return (-1);
  if ((oldfd = dup(1)) == -1 ||
      dup2(client_data->client.fd, 1) == -1 ||
      system(ls_cmd) == -1 ||
      dup2(oldfd, 1) == -1)
    return (-1);
  free(ls_cmd);
  send_response_fd(client_data->client_control.fd, 226, "Directory send OK.");
  return (0);
}

int	op_data_retr(t_ftp_client_data	*client_data,
		     const char		*arg)
{
  int	file_fd;
  char	buffer[1025];
  int	r;
  char	*path;

  if (!(path  = realpath(arg, NULL)) ||
	  (file_fd = open(path, O_RDONLY)) == -1)
    return (1);
  send_response_fd(client_data->client_control.fd, 150, "RETR start.");
  while ((r = read(file_fd, buffer, 1024)) > 0)
    {
      if (write(client_data->client.fd, buffer, r) == -1)
	return (-1);
    }
  if (close(file_fd) == -1)
    return (-1);
  send_response_fd(client_data->client_control.fd, 226, "Transfer complete.");
  return (0);
}

int	op_data_stor(t_ftp_client_data	*client_data,
		     const char		*arg)
{
  int	f_fd;
  char	buffer[1025];
  int	r;

  if ((f_fd = creat(arg, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))== -1)
    return (1);
  send_response_fd(client_data->client_control.fd, 150, "STOR start");
  while ((r = read(client_data->client.fd, buffer, 1024)) > 0)
    {
      if (write(f_fd, buffer, r) == -1)
	return (-1);
    }
  if (close(f_fd) == -1)
    return (-1);
  send_response_fd(client_data->client_control.fd, 226, "Transfer complete.");
  return (0);
}
