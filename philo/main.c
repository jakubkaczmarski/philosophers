/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:13:37 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/27 13:03:41 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_data* get_input(int argc, char **argv)
{	
	if(argc != 5 && argc != 6)
		return NULL;
	t_philo_data *philo = malloc(sizeof(t_philo_data));
	philo->philo_num = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if(check_for_int_overflow(philo->philo_num, argv[1]) == 0
		|| check_for_int_overflow(philo->time_to_die, argv[2]) == 0
		|| check_for_int_overflow(philo->time_to_eat , argv[3]) == 0
		|| check_for_int_overflow(philo->time_to_sleep, argv[4]) == 0)
		return NULL;
	if(argc == 6)
	{
		philo->eat_times = ft_atoi(argv[5]);
		if(philo->eat_times == 0 || check_for_int_overflow(philo->eat_times , argv[5]) == 0)
		{
			return NULL;
		}
	}else{
		philo->eat_times = -1;
	}
    if(philo->philo_num < 0 || philo->time_to_die < 0 || philo->time_to_eat < 0 || philo->time_to_sleep < 0)
        return NULL;
	return philo;
}
int init_philos(t_philo_data *philo)
{
	philo->philo = malloc(sizeof(t_philo) * philo->philo_num);
	int i = 0;
	
	while(i + 1 < philo->philo_num + 1)
	{
		if(i == 0)
		{
			philo->philo[i].philo_id = i + 1;
			philo->philo[i].left_fork = philo->philo_num - 1;
			philo->philo[i].right_fork = i;
			philo->philo[i].s_philo_data = philo;
			philo->philo[i].state = 1;
		}else
		{
			philo->philo[i].philo_id = i;
			philo->philo[i].left_fork = i - 1;
			philo->philo[i].right_fork = i;
			philo->philo[i].state = 1;
			philo->philo[i].s_philo_data = philo;
		}
		i++;
	}
	return 1;
}
int throw_err()
{
	printf("Error\n");
	return 0;
}
int	init_mutex(t_philo_data *philo)
{
	int i = 0;
	philo->forks_arr = malloc(sizeof(pthread_mutex_t) * philo->philo_num);
	while(i < philo->philo_num)
	{
		if(pthread_mutex_init(&philo->forks_arr[i], NULL))
		{
			
			return 1;
		}
		i++;
	}
	pthread_mutex_destroy(&(philo->death_lock));
	return 0;
}
long long get_time()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void eat(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
	printf("Philo id = %d Picked up left fork id == %d\n", philo_p->philo_id, philo_p->left_fork);
	pthread_mutex_lock(&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
	printf("Philo id = %d Picked up right fork id == %d\n", philo_p->philo_id,philo_p->right_fork);
	usleep(philo_p->s_philo_data->time_to_eat * 1000);
	philo_p->times_ate++;
	pthread_mutex_lock(&philo_p->s_philo_data->death_lock);
	printf("\nTime %lld\n", philo_p->last_meal_time);
	if(philo_p->last_meal_time + philo_p->s_philo_data->time_to_die > get_time())
	{
		printf("Philo %d died\n", philo_p->philo_id);
		philo_p->state = 0;
		pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
		return ;
	}else{
		printf("Philo %d is eating\n", philo_p->philo_id);
	}
	philo_p->last_meal_time = get_time();
	pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
	pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
	pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);

}
void philo_sleep(t_philo *philo_p)
{
	printf("Philosopher id = %d is sleeping\n", philo_p->philo_id);
	usleep(philo_p->s_philo_data->time_to_sleep * 1000);
}
void thinking(t_philo *philo_p)
{
	printf("Philosopher id = %d is thinking\n", philo_p->philo_id);
}
int state_check(t_philo *philo_p)
{
		if(philo_p->state == 0)
		{
			return 1;
		}else
		{
			return 0;
		}
		if(philo_p->s_philo_data->eat_times != -1)
		{
			if(philo_p->times_ate == philo_p->s_philo_data->eat_times)
				return 1;
		}
}
void *manage_philo(void * philo_p)
{
	// t_philo *philo_ptr = (t_philo*) philo_p;
	if(!philo_p)
		printf("Siemanko");
	int i = 0;
	while(1)
	{
		if(state_check((t_philo*)philo_p) == 1)
			break;
		eat((t_philo*)philo_p);
		philo_sleep((t_philo*)philo_p);
		thinking((t_philo*)philo_p);
		i++;
	}
	return NULL;
}
int	init_threads(t_philo_data *philo)
{
	int i = 0;
	while(i < philo->philo_num)
	{
		if(pthread_create(&philo->philo[i].philo_thread, NULL,manage_philo , (void *)&philo->philo[i]))
		{
			return 1;
		};
		i++;
	}
	return 0;
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
	i = 0;
	while (i < philo->philo_num)
	{
		pthread_mutex_destroy(&(philo->forks_arr[i]));
		i++;
	}
	pthread_mutex_destroy(&(philo->death_lock));
	return 0;
}
int	main(int argc, char **argv)
{
	
	t_philo_data * philo = get_input(argc, argv);
	if(!philo)
		return (throw_err());
	else{
		init_mutex(philo);
		init_philos(philo);
		init_threads(philo);
		clean_threads(philo);
		printf("Good input cool cool cool\n");
	}

}