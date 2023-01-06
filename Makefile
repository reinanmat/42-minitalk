# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: revieira <revieira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 16:15:40 by revieira          #+#    #+#              #
#    Updated: 2023/01/05 15:26:19 by revieira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = Minitalk
SERVER          = server
CLIENT          = client
SERVER_BONUS	= server_bonus
CLIENT_BONUS	= client_bonus

PATH_LIBFT 	    = ./Libft
PATH_SRCS 	    = ./Minitalk/Mandatory/sources/
PATH_OBJS 	    = ./Minitalk/Mandatory/objects/
PATH_INCS	    = ./Minitalk/Mandatory/includes/
PATH_SRCS_BONUS = ./Minitalk/Bonus/sources/
PATH_OBJS_BONUS = ./Minitalk/Bonus/objects/
PATH_INCS_BONUS = ./Minitalk/Bonus/includes/

SRCS 		    = $(addprefix $(PATH_SRCS), server.c client.c)
SRCS_BONUS 	    = $(addprefix $(PATH_SRCS_BONUS), server_bonus.c client_bonus.c)
OBJS_SERVER     = $(PATH_OBJS)server.o 
OBJS_CLIENT     = $(PATH_OBJS)client.o
OBJS_SERVER_BONUS = $(PATH_OBJS_BONUS)server_bonus.o
OBJS_CLIENT_BONUS = $(PATH_OBJS_BONUS)client_bonus.o

LIBFT 		    = -L $(PATH_LIBFT) -lft
INCLUDES	    = -I $(PATH_INCS) -I $(PATH_LIBFT)/includes/
INCLUDES_BONUS  = -I $(PATH_INCS_BONUS) -I $(PATH_LIBFT)/includes/
CFLAGS 		    = -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): $(PATH_OBJS) $(SERVER) $(CLIENT)

$(SERVER): $(OBJS_SERVER) $(PATH_LIBFT)/libft.a
	cc $(CFLAGS) $< $(LIBFT) -o $@

$(CLIENT): $(OBJS_CLIENT) $(PATH_LIBFT)/libft.a
	cc $(CFLAGS) $< $(LIBFT) -o $@

$(PATH_OBJS): 
	mkdir -p $(PATH_OBJS)

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(PATH_LIBFT)/libft.a:
	make -C $(PATH_LIBFT) --no-print-directory

bonus: $(PATH_OBJS_BONUS) $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(OBJS_SERVER_BONUS) $(PATH_LIBFT)/libft.a
	cc $(CFLAGS) $< $(LIBFT) -o $@

$(CLIENT_BONUS): $(OBJS_CLIENT_BONUS) $(PATH_LIBFT)/libft.a
	cc $(CFLAGS) $< $(LIBFT) -o $@

$(PATH_OBJS_BONUS):
	mkdir -p $(PATH_OBJS_BONUS)

$(PATH_OBJS_BONUS)%.o: $(PATH_SRCS_BONUS)%.c
	cc $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
	rm -rf $(PATH_OBJS) $(PATH_OBJS_BONUS)
	make -C $(PATH_LIBFT) clean --no-print-directory
	
fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	make -C $(PATH_LIBFT) fclean --no-print-directory

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re
