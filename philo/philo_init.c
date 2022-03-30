/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:51:31 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/30 14:01:18 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_data *	get_input(int argc, char **argv)
{	
	t_philo_data *philo;

	if (argc != 5 && argc != 6)
		return (NULL);
	philo = malloc(sizeof(t_philo_data));
	philo->philo_num = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (check_for_int_overflow(philo->philo_num, argv[1]) == 0
		|| check_for_int_overflow(philo->time_to_die, argv[2]) == 0
		|| check_for_int_overflow(philo->time_to_eat , argv[3]) == 0
		|| check_for_int_overflow(philo->time_to_sleep, argv[4]) == 0)
		return (NULL);
	if (argc == 6)
	{
		philo->eat_times = ft_atoi(argv[5]);
		if (philo->eat_times == 0 || check_for_int_overflow (philo->eat_times, argv[5]) == 0)
		{
			return (NULL);
		}
	}
	else
		philo->eat_times = -1;
	if (philo->philo_num < 0 || philo->time_to_die < 0
		|| philo->time_to_eat < 0 || philo->time_to_sleep < 0)
		return (NULL);
	return (philo);
}

int	init_philos(t_philo_data *philo)
{
	int	i;

	philo->philo = malloc(sizeof(t_philo) * philo->philo_num);
	i = 0;
	while (i + 1 < philo->philo_num + 1)
	{
		if (i == 0)
		{
			philo->philo[i].philo_id = i + 1;
			philo->philo[i].left_fork = philo->philo_num - 1;
			philo->philo[i].right_fork = i;
			philo->philo[i].s_philo_data = philo;
			philo->philo[i].state = 1;
		}
		else
		{
			philo->philo[i].philo_id = i + 1;
			philo->philo[i].left_fork = i - 1;
			philo->philo[i].right_fork = i;
			philo->philo[i].state = 1;
			philo->philo[i].s_philo_data = philo;
		}
		i++;
	}
	philo->someone_is_dead = 0;
	return (1);
}

int	throw_err(void)
{
	printf("Error\n");
	return (0);
}

int	init_mutex(t_philo_data *philo)
{
	int	i;

	i = 0;
	philo->forks_arr = malloc(sizeof(pthread_mutex_t) * philo->philo_num);
	while (i < philo->philo_num)
	{
		if (pthread_mutex_init(&philo->forks_arr[i], NULL))
		{	
			return (1);
		}
		i++;
	}
	pthread_mutex_init(&(philo->death_lock), NULL);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;
	long long		ret_val;

	gettimeofday(&time, NULL);
	ret_val = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret_val);
}