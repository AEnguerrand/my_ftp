/*
** cmd_login.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Fri May 12 21:35:38 2017 Enguerrand Allamel
** Last update Sun May 21 17:07:29 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

int	cmd_login_user(t_ftp_client_info	*client_info,
		       const char		*cmd)
{
  if (!cmd || !get_pos_args(cmd))
    {
      send_response(client_info, 530, "Login not good");
      return (1);
    }
  else if (client_info->is_log == 1)
    {
      send_response(client_info, 530, "Can't change from guest user.");
      return (1);
    }
  else if ((client_info->username = strdup(get_pos_args(cmd))) == NULL)
    return (-1);
  client_info->is_log = 2;
  send_response(client_info, 331, "User name okay, need password.");
  return (0);
}

int	cmd_login_pass(t_ftp_client_info	*client_info,
		       const char		*cmd)
{
  if (client_info->is_log != 2)
    {
      send_response(client_info, 503, "USER <username> is required.");
      return (1);
    }
  else if (!client_info->username ||
	  (get_pos_args(cmd) && strcmp(get_pos_args(cmd), " ")) ||
	  strcasecmp(client_info->username, "Anonymous") != 0)
    {
      send_response(client_info, 530, "Bad login user / pass.");
      return (1);
    }
  client_info->is_log = 1;
  if (chdir(client_info->path_default) != 0)
    return (-1);
  send_response(client_info, 230, "User logged in, proceed.");
  return (0);
}
