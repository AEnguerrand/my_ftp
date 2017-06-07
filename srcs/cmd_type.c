/*
** cmd_type.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Sat May 13 16:37:12 2017 Enguerrand Allamel
** Last update Sun May 21 17:14:50 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

int	cmd_type(t_ftp_client_info *client_info, const char *cmd)
{
  (void)cmd;
  if (!check_is_log(client_info))
    return (1);
  send_response(client_info, 200, "Switching to Binary mode.");
  return (0);
}
