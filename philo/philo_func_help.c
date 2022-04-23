/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:50:58 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/23 13:23:09 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_pick(t_philo *philo_p, long long time, int dir)
{
	if(check_if_dead(philo_p) == 1)
	{
		if(dir == 1)
		{
			pthread_mutex_unlock(
				&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		}else if(dir == 0)
		{
			pthread_mutex_unlock(
				&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
		}
		return ;
	}
	else
		printf ("%lld Philosopher %d has taken a fork\n",
			time, philo_p->philo_id);
}

void	philo_eat(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->s_philo_data->death_lock);
	philo_p->last_meal_time = get_time();
	pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
	if (check_death_l(philo_p) == 1)
		return ;
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
	if (check_if_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(
			&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		return (1);
	}
	return (0);
}

int	inp_handling(t_philo_data *philo, char **argv)
{
	if (check_for_int_overflow(philo->philo_num, argv[1]) == 0
		|| check_for_int_overflow(philo->time_to_die, argv[2]) == 0
		|| check_for_int_overflow(philo->time_to_eat, argv[3]) == 0
		|| check_for_int_overflow(philo->time_to_sleep, argv[4]) == 0)
	{
		free(philo);
		return (1);
	}
	return (0);
}
