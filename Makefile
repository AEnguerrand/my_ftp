##
## Makefile for Rendu in /home/enguerrandallamel/Rendu/PSU_2016_my_ftp
##
## Made by enguerrandallamel
## Login   <enguerrand.allamel@epitech.net>
##
## Started on  Fri May 12 15:48:46 2017 Enguerrand Allamel
## Last update Sun May 21 17:38:15 2017 Allamel Enguerrand
##

NAME =	server

CC =	gcc

RM =	rm -f

CFLAGS +=	-W -Wall -Wextra -Werror -std=gnu99	\
		-I ./includes

SRCS =	./srcs/main.c \
	./srcs/error.c \
	./srcs/accept_client.c \
	./srcs/one_client.c \
	./srcs/command.c \
	./srcs/cmd_auth.c \
	./srcs/cmd_login.c \
	./srcs/cmd_work_dir.c \
	./srcs/cmd_type.c \
	./srcs/cmd_utils.c \
	./srcs/cmd_tranfer_type.c \
	./srcs/cmd_file.c \
	./srcs/console_log.c \
	./srcs/one_client_data.c \
	./srcs/op_data_file.c \
	./srcs/utils.c \
	./srcs/block_user_dir.c \
	./srcs/op_data.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
