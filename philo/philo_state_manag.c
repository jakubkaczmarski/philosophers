/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_manag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:20:07 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/30 14:21:14 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void eat(t_philo *philo_p)
{
	
	pthread_mutex_lock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
	if(change_to_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		return ;
	}
	printf("%lld Philosopher id = %d Picked up left fork id == %d\n",get_time() - philo_p->s_philo_data->start_time, philo_p->philo_id, philo_p->left_fork);
	if(change_to_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		return ;
	}
	pthread_mutex_lock(&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
	if(change_to_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		return ;
	}
	printf("%lld Philosopher id = %d Picked up right fork id == %d\n",get_time() - philo_p->s_philo_data->start_time,  philo_p->philo_id,philo_p->right_fork);
	philo_p->times_ate++;

	if(change_to_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
		return ;
	}else{
		philo_p->last_meal_time = get_time();
		printf("%lld Philosopher %d is eating\n",get_time() - philo_p->s_philo_data->start_time, philo_p->philo_id);
		usleep(philo_p->s_philo_data->time_to_eat * 1000);
	}
	pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
	pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);

}
void philo_sleep(t_philo *philo_p)
{
	if(change_to_dead(philo_p) == 1)
	{
		return ;
	}else{
		long long time = get_time();
		// long long time_of_death = time - philo_p->last_meal_time;
		printf("%lld Philosopher id = %d is sleeping\n", get_time() - philo_p->s_philo_data->start_time,  philo_p->philo_id);
		while(1)
		{
			// if(time_of_death > philo_p->s_philo_data->time_to_die)
			// {
			// 	printf("%lld Philosopher %d died\n", get_time() - philo_p->s_philo_data->start_time, philo_p->philo_id);
			// 	pthread_mutex_lock(&philo_p->s_philo_data->death_lock);
			// 	philo_p->s_philo_data->someone_is_dead = 1;	
			// 	pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
			// 	break;	
			// }
			if(get_time() - time >= philo_p->s_philo_data->time_to_sleep)
				break;
		}
	}
}

void thinking(t_philo *philo_p)
{
	if(change_to_dead(philo_p) == 1)
	{
		return ;
	}
	if(check_if_dead((t_philo*)philo_p) == 1)
	{
		return ;	
	}else
	{
		printf("%lld Philosopher id = %d is thinking\n",get_time() - philo_p->s_philo_data->start_time, philo_p->philo_id);
	}
}

int clean_threads(t_philo_data *philo)
{
	int i = 0;
	while(i < philo->philo_num)
	{
		if(pthread_join(philo->philo[i].philo_thread, NULL))
		{
			return 1;
		};
		i++;
	}
	free(philo->philo);
	i = 0;
	while (i < philo->philo_num)
	{
		pthread_mutex_destroy(&(philo->forks_arr[i]));
		i++;
	}
	free(philo->forks_arr);
	pthread_mutex_destroy(&(philo->death_lock));
	return 0;
}