/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_manag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:20:07 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/23 13:36:18 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
	if (check_death_l(philo_p) == 0)
		fork_pick(philo_p, get_time() - philo_p->s_philo_data->start_time, 1);
	if (check_death_l(philo_p) == 1)
		return ;
	pthread_mutex_lock(
		&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
	if (check_death_l(philo_p) == 1)
		return ;
	fork_pick(philo_p, get_time() - philo_p->s_philo_data->start_time, 0);
	pthread_mutex_lock(&philo_p->s_philo_data->eat_lock);
	philo_p->times_ate++;
	pthread_mutex_unlock(&philo_p->s_philo_data->eat_lock);
	if (check_if_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(
			&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		pthread_mutex_unlock(
			&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
		return ;
	}
	else
		philo_eat(philo_p);
	unlock_mutex(philo_p);
}

void	philo_sleep(t_philo *philo_p)
{
	long long	time;

	if (check_if_dead(philo_p) == 1)
	{
		return ;
	}
	else
	{
		time = get_time();
		printf("%lld Philosopher %d is sleeping\n",
			get_time() - philo_p->s_philo_data->start_time, philo_p->philo_id);
		while (1)
		{
			if (check_death_l(philo_p) == 1)
				break ;
			if (get_time() - time >= philo_p->s_philo_data->time_to_sleep)
				break ;
		}
	}
}

void	print_time(t_philo *philo_p)
{
	long long	time;

	if (check_if_dead(philo_p) == 0)
	{
		time = get_time() - philo_p->s_philo_data->start_time;
		printf("%lld Philosopher %d is thinking\n", time, philo_p->philo_id);
	}
}

void	thinking(t_philo *philo_p)
{
	if (check_if_dead((t_philo *)philo_p) == 1)
	{	
		return ;
	}
	else
	{
		print_time((t_philo *)philo_p);
	}
}

int	clean_threads(t_philo_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_join(philo->philo[i].philo_thread, NULL))
		{
			return (1);
		}
		i++;
	}
	pthread_mutex_lock(&philo->death_lock);
	if (philo->someone_is_dead == 1)
		printf("%lld Philo %d died\n",
			philo->dead_time, philo->dead_id);
	pthread_mutex_unlock(&philo->death_lock);
	i = 0;
	while (i < philo->philo_num)
		pthread_mutex_destroy(&(philo->forks_arr[i++]));
	pthread_mutex_destroy(&(philo->death_lock));
	pthread_mutex_destroy(&(philo->eat_lock));
	free(philo->philo);
	free(philo);
	free(philo->forks_arr);
	return (0);
}
