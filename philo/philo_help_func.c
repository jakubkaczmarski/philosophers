/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_help_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:31:36 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/21 14:20:41 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_input(int argc,char **argv, t_philosopher *philo, int *numof_philo)
{
	if(argc < 5 || argc > 6)
	{
		return 0;
	}
	*numof_philo = ft_atoi(argv[1]);
	philo->philo_num = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if(check_for_int_overflow(*numof_philo, argv[1]) == 0
		|| check_for_int_overflow(philo->philo_num, argv[2]) == 0
		|| check_for_int_overflow(philo->time_to_eat , argv[3]) == 0
		|| check_for_int_overflow(philo->time_to_sleep, argv[4]) == 0)
		return 0;
	if(argc == 6)
	{
		philo->has_to_eat = ft_atoi(argv[5]);
		if(philo->has_to_eat == 0 || check_for_int_overflow(philo->has_to_eat , argv[5]) == 0)
		{
			return 0;
		}
	}
    if(*numof_philo < 0 || philo->philo_num < 0 || philo->time_to_eat < 0 || philo->time_to_sleep < 0)
        return 0;
	return 1;
}