/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:19:48 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/21 18:19:51 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void think(t_philosopher *philo)
// {
// 	// int duration = philo->time_to_
// }

struct p_info{
	int philo_num;
	pthread_mutex_t *forks;
}	typedef t_info;
t_info philo_inf;
t_philosopher *	init_philo(t_philosopher philo_id, int num_of_philo)
{
	int i = 1;
	t_philosopher *arr;
	arr = malloc(sizeof(t_philosopher) * num_of_philo);
	while(i < num_of_philo + 1)
	{
		arr[i].has_to_eat = philo_id.has_to_eat;
		arr[i].philo_num = i;
		arr[i].time_to_die = philo_id.time_to_die;
		arr[i].time_to_sleep = philo_id.time_to_sleep;
		arr[i].time_to_eat = philo_id.time_to_eat;
		i++;
	}
	return arr;
}
void *manage_philo(void *philo)
{
	t_philosopher *arr = (t_philosopher *)philo;
	printf("Philosopher number %d is thinking\n", arr->philo_num);
	pthread_mutex_lock(&philo_inf.forks[arr->philo_num]);
	pthread_mutex_lock(&philo_inf.forks[(arr->philo_num + 1) % philo_inf.philo_num]);
	printf("Philosopher %d is eating \n", arr->philo_num);
	usleep(arr->time_to_eat);
	pthread_mutex_unlock(&philo_inf.forks[arr->philo_num]);
	pthread_mutex_unlock(&philo_inf.forks[(arr->philo_num + 1) % philo_inf.philo_num]);
	printf("Philosopher %d is sleeping \n", arr->philo_num);
	usleep(arr->time_to_sleep);
	return (NULL);
}
int main(int argc, char **argv)
{
	
	pthread_mutex_t mutex;
	pthread_mutex_lock(&mutex);
	
	pthread_mutex_unlock(&mutex);
	pthread_mutex_init(&mutex, NULL);
	t_philosopher philo;
	if(get_input(argc,argv, &philo, &philo_inf.philo_num) == 0)
	{
		printf("Error\n");
		return 0;
	};
	t_philosopher *arr;
	arr = init_philo(philo, philo_inf.philo_num);
	
	int i = 0;
	//Allocate memory for mutaxes
	philo_inf.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_inf.philo_num);
	while(i < philo_inf.philo_num)
	{
		pthread_mutex_init(&philo_inf.forks[i], NULL);
		i++;
	}
	i = 0;
	while(i < philo_inf.philo_num)
	{
		pthread_create(&arr[i].philo_thread, NULL, manage_philo, (void*)&arr[i]);
		i++;
	}
	i = 0;
	while(i < philo_inf.philo_num)
	{
		pthread_join(arr[i].philo_thread, NULL);
		i++;
	}
	i = 0;
	while(i < philo_inf.philo_num)
	{
		pthread_mutex_destroy(&philo_inf.forks[i]);
		i++;
	}
	// int philo_id = 0;
	// pthread_t t0;
	// pthread_create(&t0, NULL, init_philo, (void *)philo_id);
	// pthread_join(philo_id, NULL);
	printf("\nGood input cool cool cool\n");
}