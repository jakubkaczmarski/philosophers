# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 15:34:39 by jkaczmar          #+#    #+#              #
#    Updated: 2022/03/26 13:42:14 by jkaczmar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: philo
RED   = \x1b[31m
GREEN = \x1b[32m
philo:
	gcc -Wall -Wextra -Werror -lpthread -fsanitize=thread -o philo main.c philo_help.c stack_instructions.c | echo "${GREEN}It works somehow 🤠😺🙉"
clean:
	@rm -f philo
fclean:
	@rm -f philo
re: fclean all

.PHONY: all clean fclean re