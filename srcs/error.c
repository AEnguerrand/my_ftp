/*
** error.c for PSU_2016_myftp in /home/enguerrand/delivery/
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Fri May 12 15:49:28 2017 Enguerrand Allamel
** Last update Sun May 21 17:23:20 2017 Allamel Enguerrand
*/

#include "../includes/my_ftp.h"

void	error_server_init(char *func, int server_fd)
{
  perror(func);
  close(server_fd);
  exit(EXIT_FAILURE);
}
