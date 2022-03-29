/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:13:37 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/29 19:24:00 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_data	*get_input(int argc, char **argv)
{
	t_philo_data	*philo;

	if (argc != 5 && argc != 6)
		return (NULL);
	philo = malloc(sizeof(t_philo_data));
	philo->philo_num = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (check_for_int_overflow(philo->philo_num, argv[1]) == 0 ||
		check_for_int_overflow(philo->time_to_die, argv[2]) == 0 ||
		check_for_int_overflow(philo->time_to_eat, argv[3]) == 0 ||
		check_for_int_overflow(philo->time_to_sleep, argv[4]) == 0)
		return (NULL);
	if (argc == 6)
	{
		philo->eat_times = ft_atoi(argv[5]);
		if (philo->eat_times == 0 ||
			check_for_int_overflow(philo->eat_times, argv[5]) == 0)
		{
			return (NULL);
		}
	}
	else
	{
		philo->eat_times = -1;
	}
	if (philo->philo_num < 0 || philo->time_to_die < 0 ||
		philo->time_to_eat < 0 || philo->time_to_sleep < 0)
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

int	throw_err()
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

long long	get_time()
{
	struct timeval	time;
	long long		ret_val;

	gettimeofday(&time, NULL);
	ret_val = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret_val);
}

int	change_to_dead(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->s_philo_data->death_lock);
	if (philo_p->s_philo_data->someone_is_dead == 1)
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
		return (1);
	}
	if (philo_p->last_meal_time != 0 &&
		philo_p->last_meal_time + philo_p->s_philo_data->time_to_die < get_time())
	{
		philo_p->s_philo_data->someone_is_dead = 1;
		printf("%lld Philosopher %d died\n",
				get_time() - philo_p->s_philo_data->start_time,
				philo_p->philo_id);
		pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
		return (0);
	}
}

void			eat(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
	if (change_to_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(
			&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		return ;
	}
	printf("%lld Philosopher id = %d Picked up left fork id == %d\n",
			get_time() - philo_p->s_philo_data->start_time,
			philo_p->philo_id,
			philo_p->left_fork);
	if (change_to_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(
			&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		return ;
	}
	pthread_mutex_lock(&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
	if (change_to_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(
			&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		return ;
	}
	printf("%lld Philosopher id = %d Picked up right fork id == %d\n",
			get_time() - philo_p->s_philo_data->start_time,
			philo_p->philo_id,
			philo_p->right_fork);
	philo_p->times_ate++;
	if (change_to_dead(philo_p) == 1)
	{
		pthread_mutex_unlock(
			&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
		pthread_mutex_unlock(
			&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
		return ;
	}
	else
	{
		philo_p->last_meal_time = get_time();
		printf("%lld Philosopher %d is eating\n",
		get_time() - philo_p->s_philo_data->start_time,
		philo_p->philo_id);
		usleep(philo_p->s_philo_data->time_to_eat * 1000);
	}
	pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->left_fork]);
	pthread_mutex_unlock(&philo_p->s_philo_data->forks_arr[philo_p->right_fork]);
}

void	philo_sleep(t_philo *philo_p)
{
	long long	time;

	if (change_to_dead(philo_p) == 1)
	{
		return ;
	}
	else
	{
		time = get_time();
		printf("%lld Philosopher id = %d is sleeping\n",
				get_time() - philo_p->s_philo_data->start_time,
				philo_p->philo_id);
		while (1)
		{
			if (get_time() - time >= philo_p->s_philo_data->time_to_sleep)
				break ;
		}
	}
}

int				check_if_dead(t_philo *philo_p)
{
	pthread_mutex_lock(&philo_p->s_philo_data->death_lock);
	if (philo_p->s_philo_data->someone_is_dead == 1)
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo_p->s_philo_data->death_lock);
		return (0);
	}
}

void	thinking(t_philo *philo_p)
{
	if (change_to_dead(philo_p) == 1)
	{
		return ;
	}
	if (check_if_dead((t_philo *)philo_p) == 1)
	{
		return ;
	}
	else
	{
		printf("%lld Philosopher id = %d is thinking\n",
		get_time() - philo_p->s_philo_data->start_time,
		philo_p->philo_id);
	}
}
int	one_philo(t_philo *philo_p)
{
	if (philo_p->s_philo_data->philo_num == 1)
	{
		printf("%lld Philosopher id = %d Picked up left fork id == %d\n",
		get_time() - philo_p->s_philo_data->start_time,
		philo_p->philo_id,
		philo_p->right_fork);
		usleep(philo_p->s_philo_data->time_to_die * 1000);
		printf("%lld Philosopher %d died\n",
		get_time() - philo_p->s_philo_data->start_time,
		philo_p->philo_id);
		return (1);
	}
	return (0);
}

int	state_check(t_philo *philo_p)
{
	if (philo_p->state == 0)
	{
		return 1;
	}
	else if (philo_p->s_philo_data->eat_times != -1)
	{
		if (philo_p->times_ate == philo_p->s_philo_data->eat_times)
			return 1;
	}
	return 0;
}

void	*manage_philo(void *philo_p)
{
	t_philo	*philo_ptr;
	int		i;
		return NULL;
	return	NULL;

	philo_ptr = (t_philo *)philo_p;
	if (!philo_p)
		printf("Siemanko");
	i = 0;
	if (one_philo(philo_p) == 1)
	if (philo_ptr->philo_id % 2 == 0)
		usleep(500 * philo_ptr->s_philo_data->time_to_eat);
	while (check_if_dead((t_philo *)philo_p) == 0)
	{
		if (state_check((t_philo *)philo_p) == 1)
			break ;
		if (check_if_dead((t_philo *)philo_p) == 1)
			break ;
		eat((t_philo *)philo_p);
		if (state_check((t_philo *)philo_p) == 1)
			break ;
		if (check_if_dead((t_philo *)philo_p) == 1)
			break ;
		philo_sleep((t_philo *)philo_p);
		if (state_check((t_philo *)philo_p) == 1)
			break ;
		if (check_if_dead((t_philo *)philo_p) == 1)
			break ;
		thinking((t_philo *)philo_p);
		if (check_if_dead((t_philo *)philo_p) == 1)
			break ;
		i++;
	}
}

int	init_threads(t_philo_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_create(&philo->philo[i].philo_thread,
							NULL,
							manage_philo,
							(void *)&philo->philo[i]))
		{
			return 1;
		};
		i++;
	}
	return 0;
}

int	clean_threads(t_philo_data *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_join(philo->philo[i].philo_thread, NULL))
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
		// printf("Good input cool cool cool\n");
	}
}
