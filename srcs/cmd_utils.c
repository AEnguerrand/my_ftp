/*
** cmd_utils.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Sun May 14 15:18:40 2017 Enguerrand Allamel
** Last update Sun May 21 17:15:38 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

int	cmd_utils_noop(t_ftp_client_info *client_info, const char *cmd)
{
  (void)cmd;
  if (!check_is_log(client_info))
    return (1);
  send_response(client_info, 200, "NOOP ok.");
  return (0);
}

int	cmd_utils_quit(t_ftp_client_info *client_info, const char *cmd)
{
  (void)cmd;
  send_response(client_info, 221, "Service closing control connection.");
  return (20);
}

int	cmd_utils_help(t_ftp_client_info *client_info, const char *cmd)
{
  (void)cmd;
  if (!check_is_log(client_info))
    return (1);
  send_response(client_info, 214, "Help OK. Nothing more now.");
  return (0);
}
