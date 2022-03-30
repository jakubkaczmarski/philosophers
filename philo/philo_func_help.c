/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:50:58 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/30 18:21:47 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_died_msg(t_philo *philo_p)
{
	long long	time;

	time = get_time() - philo_p->s_philo_data->start_time;
	printf("%lld Philosopher %d died\n", time, philo_p->philo_id);
}

void	r_fork_pick(t_philo *philo_p, long long time)
{
	printf ("%lld Philosopher id = %d Picked up right fork id == %d\n",
		time, philo_p->philo_id, philo_p->right_fork);
}

void	philo_eat(t_philo *philo_p)
{
	philo_p->last_meal_time = get_time();
	printf("%lld Philosopher %d is eating\n",
		get_time() - philo_p->s_philo_data->start_time, philo_p->philo_id);
	usleep(philo_p->s_philo_data->time_to_eat * 1000);
}

void	unlock_mutex(t_philo *philo_p)
{
	pthread_mutex_unlock(
		&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
	pthread_mutex_unlock(
		&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
}

int	check_death_l(t_philo *philo_p)
{
	if (change_to_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(
			&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		return (1);
	}
	return (0);
}
