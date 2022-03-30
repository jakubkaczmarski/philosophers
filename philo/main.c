/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:13:37 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/30 18:23:01 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manage_philo(void *philo_p)
{
	t_philo	*philo_ptr;
	int		i;

	philo_ptr = (t_philo *) philo_p;
	i = 0;
	if (init_philo_loop(philo_p) == 1)
		return (NULL);
	while (check_if_dead((t_philo *)philo_p) == 0)
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
	while (i < philo->philo_num)
	{
		if (pthread_create(&philo->philo[i].philo_thread, NULL, manage_philo,
				(void *)&philo->philo[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
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
		init_mutex(philo);
		init_philos(philo);
		philo->start_time = get_time();
		init_threads(philo);
		clean_threads(philo);
	}
}
