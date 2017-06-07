/*
** cmd_tranfert_type.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Sat May 13 16:44:35 2017 Enguerrand Allamel
** Last update Sun May 21 17:14:26 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

int		cmd_tranfer_type_pasv(t_ftp_client_info	*client_info,
				      const char	*cmd)
{
  char		*res;
  char		*ip;
  size_t	port_data;

  if (!check_is_log(client_info))
    return (1);
  port_data = 1024;
  client_info->client_data_last = init_client_data_info(client_info,
							&port_data,
  							FTP_MODE_PASV,
  							cmd);
  if (!(ip = replace_char(inet_ntoa(client_info->client.addr.sin_addr),
			  '.', ',')) ||
      (!(res = malloc(1024))) || (!memset(res, 0, 1024)) ||
      (sprintf(res, "Entering Passive Mode (%s,%ld,%ld)", ip, port_data / 256,
	       port_data % 256) <= 0))
    return (-1);
  send_response(client_info, 227, res);
  free(res);
  free(ip);
  return (0);
}

int		cmd_tranfer_type_port(t_ftp_client_info	*client_info,
				      const char	*cmd)
{
  size_t	port_data;

  if (!check_is_log(client_info))
    return (1);
  else if (!get_pos_args(cmd))
    {
      send_response(client_info, 500,
		    "Illegal PORT command.");
      return (1);
    }
  port_data = 20;
  client_info->client_data_last = init_client_data_info(client_info,
  							&port_data,
  							FTP_MODE_ACTIVE,
  							cmd);
  send_response(client_info, 200, "Entering active mode");
  return (0);
}
