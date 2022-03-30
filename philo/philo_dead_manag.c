/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dead_manag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:02:13 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/30 14:14:29 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	change_to_dead(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->s_philo_data->death_lock);
	if (philo_p->s_philo_data->someone_is_dead == 1)
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
		return (1);
	}
		
	if (philo_p->last_meal_time != 0 && philo_p->last_meal_time + philo_p->s_philo_data->time_to_die < get_time())
	{
		philo_p->s_philo_data->someone_is_dead = 1;
		printf("%lld Philosopher %d died\n", get_time() - philo_p->s_philo_data->start_time, philo_p->philo_id);
		pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
		return (1);
	}else
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
		return (0);
	}
}

int check_if_dead(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->s_philo_data->death_lock);
	if(philo_p->s_philo_data->someone_is_dead == 1)
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
		return (1);
	}else{
		pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
		return (0);
	}
}

int state_check(t_philo *philo_p)
{
	if(philo_p->state == 0)
	{
		return (1);
	}else if(philo_p->s_philo_data->eat_times != -1)
	{
		if(philo_p->times_ate == philo_p->s_philo_data->eat_times)
			return (1);
	}
	return (0);
}

int one_philo(t_philo *philo_p)
{
	long long val;

	val = 0;
	if (philo_p->s_philo_data->philo_num == 1)
	{
		val = get_time() - philo_p->s_philo_data->start_time;
		printf ("%lld Philosopher id = %d Picked up left fork id == %d\n", val , philo_p->philo_id,philo_p->right_fork);
		usleep (philo_p->s_philo_data->time_to_die * 1000);
		val = get_time() - philo_p->s_philo_data->start_time;
		printf("%lld Philosopher %d died\n", val, philo_p->philo_id);
		return (1);
	}
	return (0);
}
