/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:14:18 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/27 12:48:42 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct sStack
{
	int				top;
	unsigned int	capacity;
	pthread_mutex_t		*array;
}	t_stack;
typedef struct s_philo
{
	int philo_id;
	int left_fork;
	int right_fork;
	long long last_meal_time;
	pthread_t philo_thread;
	int state;
	int times_ate;
	struct s_philo_data *s_philo_data;
} t_philo;

typedef struct s_philo_data
{
	int philo_num;
	int time_to_sleep;
	int time_to_eat;
	int time_to_die;
	pthread_mutex_t *forks_arr;
	pthread_mutex_t death_lock;
	int eat_times;
	t_philo *philo;
} t_philo_data;


int		ft_isdigit(int c);
char	*run_edgecase(void);
int		getlenght(int checknum);
void	checkedgecase(char *resarr, int *negative, int n, int *len);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_itoa(int n);
int		check_for_int_overflow(int num, char *str);
int		throw_err();
t_philo_data* get_input(int argc, char **argv);

#endif
