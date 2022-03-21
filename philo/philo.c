/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:19:48 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/21 12:24:16 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_input(int argc,char **argv)
{
	if(argc < 5 || argc > 6)
	{
		return 0;
	}
	int num_of_philo = 0;
	int time_to_die = 0;
	int time_to_eat = 0;
	int time_to_sleep = 0;
	int number_of_times = 0;
	num_of_philo = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if(check_for_int_overflow(num_of_philo, argv[1]) == 0
		|| check_for_int_overflow(time_to_die, argv[2]) == 0
		|| check_for_int_overflow(time_to_eat, argv[3]) == 0
		|| check_for_int_overflow(time_to_sleep, argv[4]) == 0)
		return 0;
	if(argc == 6)
	{
		number_of_times = ft_atoi(argv[5]);
		if(check_for_int_overflow(number_of_times, argv[5]) == 0)
		{
			return 0;
		}
	}
	return 1;	
}
// void init_philo()
int main(int argc, char **argv)
{
	if(get_input(argc,argv) == 0)
	{
		printf("Error\n");
		return 0;
	};
	printf("Good input cool cool cool");
}			