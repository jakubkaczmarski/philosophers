# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 15:34:39 by jkaczmar          #+#    #+#              #
#    Updated: 2022/04/09 18:45:34 by jkaczmar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: philo
RED   = \x1b[31m
GREEN = \x1b[32m
philo:
	gcc -Wall -Wextra -Werror -lpthread -o philo main.c philo_help.c philo_helper_func.c philo_init.c philo_dead_manag.c philo_func_help.c philo_state_manag.c| echo "${GREEN}It works somehow 🤠😺🙉"
clean:
	@rm -f philo
fclean:
	@rm -f philo
re: fclean all

.PHONY: all clean fclean re

#-fsanitize=thread