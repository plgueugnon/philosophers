# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 14:58:12 by pgueugno          #+#    #+#              #
#    Updated: 2021/03/09 20:25:56 by pgueugno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                               Filename output                                #
################################################################################

NAME		=	philo

################################################################################
#                         Sources and objects directories                      #
################################################################################

HEADERS_DIR	=	header
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
LIBFT_MAKE	=	Makefile

################################################################################
#                               Sources filenames                              #
################################################################################

SRCS		=	main.c exit.c utils.c init.c philo_living.c display.c uitoa.c\
				philo_action.c monitor.c

################################################################################
#                              Commands and arguments                          #
################################################################################

CC			=	@gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I$(HEADERS_DIR) -fsanitize=address #-fsanitize=thread
LDFLAGS 	=	-L . -fsanitize=address #-fsanitize=thread #-fsanitize=address
RM			=	@rm -f

################################################################################
#                                 Defining colors                              #
################################################################################

_RED		=	\033[31m
_GREEN		=	\033[32m
_YELLOW		=	\033[33m
_CYAN		=	\033[96m

################################################################################
#                                  Compiling                                   #
################################################################################

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all:	init $(NAME)

init:
		@ if test -f $(NAME);\
		then echo "$(_CYAN)[philo program already created]";\
		else echo "$(_YELLOW)[Initialize philo program]";\
		fi
		$(shell mkdir -p $(OBJS_DIR))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
				@ echo "\t$(_YELLOW) compiling... $*.c"
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			@ echo "\t$(_YELLOW)[Creating philo program]"
			$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
			@ echo "$(_GREEN)[philo program created & ready]"

clean:
		@ echo "$(_RED)[cleaning up .out & objects files]"
		$(RM) $(OBJS)

fclean: clean
		@ echo "$(_RED)[cleaning up .out, objects & library files]"
		$(RM) $(NAME)

re:	fclean all

.SILENT:
		all
.PHONY: all clean fclean re bonus
