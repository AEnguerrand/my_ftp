/*
** cmd_file.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 15 12:42:52 2017 Enguerrand Allamel
** Last update Sun May 21 17:06:09 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

int	cmd_file_list(t_ftp_client_info	*client_info,
		      const char	*cmd)
{
  if (!check_is_log(client_info))
    return (1);
  run_one_client_data(client_info,
		      FTP_DATA_CMD_LIST,
		      get_pos_args(cmd));
  return (0);
}

int	cmd_file_retr(t_ftp_client_info	*client_info,
		      const char	*cmd)
{
  if (!check_is_log(client_info))
    return (1);
  else if (client_info->client_data_last.mode == FTP_MODE_NOT_SET)
    {
      send_response(client_info, 425, "Use PORT or PASV first.");
      return (1);
    }
  else if (!get_pos_args(cmd))
    {
      send_response(client_info, 550,
		    "please specify a file to retrieve");
      return (1);
    }
  return (run_one_client_data(client_info,
			      FTP_DATA_CMD_RETR,
			      get_pos_args(cmd)));
}

int	cmd_file_stor(t_ftp_client_info	*client_info,
		      const char	*cmd)
{
  if (!check_is_log(client_info))
    return (1);
  else if (client_info->client_data_last.mode == FTP_MODE_NOT_SET)
    {
      send_response(client_info, 425, "Use PORT or PASV first.");
      return (1);
    }
  else if (!get_pos_args(cmd))
    {
      send_response(client_info, 550,
		    "please specify a file to store");
      return (1);
    }
  return (run_one_client_data(client_info,
			      FTP_DATA_CMD_STOR,
			      get_pos_args(cmd)));
}

int	cmd_file_dele(t_ftp_client_info	*client_info,
		      const char	*cmd)
{
  if (!check_is_log(client_info))
    return (1);
  if (remove(get_pos_args(cmd)) != 0)
    {
      send_response(client_info, 550, "File not removable.");
      return (1);
    }
  send_response(client_info, 250, "Delete operation successful");
  return (0);
}
