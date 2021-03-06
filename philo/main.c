/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:13:37 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/23 13:39:32 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manage_philo(void *philo_p)
{
	int		i;

	i = 0;
	if (init_philo_loop(philo_p) == 1)
		return (NULL);
	while (check_if_dead(philo_p) != 1)
	{
		if (state_check((t_philo *)philo_p) == 1
			|| check_if_dead((t_philo *)philo_p) == 1)
			break ;
		eat((t_philo *)philo_p);
		if (state_check((t_philo *)philo_p) == 1
			|| check_if_dead((t_philo *)philo_p) == 1)
			break ;
		philo_sleep((t_philo *)philo_p);
		if (check_if_dead((t_philo *)philo_p) == 1)
			break ;
		thinking((t_philo *)philo_p);
		if (check_if_dead((t_philo *)philo_p) == 1)
			break ;
		i++;
	}
	return (NULL);
}

int	init_threads(t_philo_data *philo)
{
	int	i;

	i = 0;
	philo->dead_id = -1;
	while (i < philo->philo_num)
	{
		if (pthread_create(&philo->philo[i].philo_thread, NULL, manage_philo,
				(void *)&philo->philo[i]))
			return (1);
		i++;
	}
	loop_check(philo);
	return (0);
}

void	loop_check(t_philo_data *philo)
{
	int	j;

	while (philo->philo_num != 1)
	{
		j = 0;
		while (j < philo->philo_num)
		{
			if (all_ate(philo) == 0)
				return ;
			pthread_mutex_lock(&philo->death_lock);
			if (philo->philo[j].last_meal_time != 0
				&& get_time() - philo->philo[j].last_meal_time
				> philo->time_to_die)
			{
				philo->someone_is_dead = 1;
				philo->dead_time = get_time() - philo->start_time;
				philo->dead_id = j + 1;
				pthread_mutex_unlock(&philo->death_lock);
				return ;
			}
			pthread_mutex_unlock(&philo->death_lock);
			usleep(150);
			j++;
		}
	}
}

int	init_philo_loop(t_philo *philo_p)
{
	if (one_philo(philo_p) == 1)
		return (1);
	if (philo_p->philo_id % 2 == 0)
		usleep(500 * philo_p->s_philo_data->time_to_eat);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_data	*philo;

	philo = get_input(argc, argv);
	if (!philo)
		return (throw_err());
	else
	{
		philo->dead_id = -1;
		init_mutex(philo);
		init_philos(philo);
		philo->start_time = get_time();
		init_threads(philo);
		clean_threads(philo);
	}
}
