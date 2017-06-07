/*
** auth_cmd.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Fri May 12 20:29:52 2017 Enguerrand Allamel
** Last update Sun May 21 17:03:03 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

int	cmd_auth(t_ftp_client_info *client_info, const char *cmd)
{
  (void)cmd;
  send_response(client_info, 530,
	       "Please login with USER and PASS.");
  return (0);
}
