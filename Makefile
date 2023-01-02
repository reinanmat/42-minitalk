# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: revieira <revieira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 16:15:40 by revieira          #+#    #+#              #
#    Updated: 2023/01/02 14:16:23 by revieira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minitalk
SERVER 		= server
CLIENT 		= client

PATH_SRCS 	= ./sources/
PATH_OBJS 	= ./objects/
SRCS_SERVER = $(PATH_SRCS)server.c
SRCS_CLIENT = $(PATH_SRCS)client.c
OBJS_SERVER = $(PATH_OBJS)server.o
OBJS_CLIENT = $(PATH_OBJS)client.o

PATH_LIBFT 	= ./libft
LIBFT 		= -L $(PATH_LIBFT) -lft
INCLUDES	= -I includes/ -I $(PATH_LIBFT)/includes/
CFLAGS 		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(OBJS_SERVER) $(PATH_LIBFT)/libft.a
	cc $(CFLAGS) $< $(LIBFT) -o $@

$(CLIENT): $(OBJS_CLIENT)
	cc $(CFLAGS) $< $(LIBFT) -o $@

$(PATH_OBJS):
	mkdir -p $(PATH_OBJS)

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c $(PATH_OBJS)
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(PATH_LIBFT)/libft.a:
	make -C $(PATH_LIBFT) --no-print-directory

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	rm -rf $(PATH_OBJS)
	make -C $(PATH_LIBFT) clean --no-print-directory
	
fclean: clean
	rm -f $(SERVER) $(CLIENT) 
	make -C $(PATH_LIBFT) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re
