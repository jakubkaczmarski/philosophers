# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 12:19:14 by jkaczmar          #+#    #+#              #
#    Updated: 2022/03/20 18:59:46 by jkaczmar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: philo

philo:
	gcc -Wall -Wextra -Werror -lpthread -o philo philo.c philo_help_func.c helper_func.c
clean:
	@rm -f philo
fclean:
	@rm -f philo
re: fclean all

.PHONY: all clean fclean re