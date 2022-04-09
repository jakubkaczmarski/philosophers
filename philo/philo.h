/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:14:18 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/04/09 18:59:03 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					philo_id;
	int					left_fork;
	int					right_fork;
	long long			last_meal_time;
	pthread_t			philo_thread;
	int					state;
	int					times_ate;
	struct s_philo_data	*s_philo_data;
}	t_philo;

typedef struct s_philo_data
{
	int				philo_num;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	pthread_mutex_t	*forks_arr;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	action_lock;
	int				dead_id;
	int				someone_is_dead;
	int				eat_times;
	long long		start_time;
	t_philo			*philo;
}	t_philo_data;

void			kapibara(t_philo_data *philo);
int				your_a_wizard(t_philo_data *philo, char **argv);
int				ft_isdigit(int c);
char			*run_edgecase(void);
int				getlenght(int checknum);
void			checkedgecase(char *resarr, int *negative, int n, int *len);
int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_itoa(int n);
int				check_for_int_overflow(int num, char *str);
int				throw_err(void);
t_philo_data	*get_input(int argc, char **argv);
int				init_philos(t_philo_data *philo);
int				init_mutex(t_philo_data *philo);
int				change_to_dead(t_philo *philo_p);
int				check_if_dead(t_philo *philo_p);
int				state_check(t_philo *philo_p);
int				one_philo(t_philo *philo_p);
long long		get_time(void);
void			eat(t_philo *philo_p);
void			philo_sleep(t_philo *philo_p);
void			thinking(t_philo *philo_p);
int				clean_threads(t_philo_data *philo);
void			print_time(t_philo *philo_p);
t_philo_data	*philo_assigment(char **argv);
void			assign_single_philo(t_philo_data *philo, int i);
void			l_fork_pick(t_philo *philo_p, long long time);
void			philo_died_msg(t_philo *philo_p);
void			philo_eat(t_philo *philo_p);
void			r_fork_pick(t_philo *philo_p, long long time);
void			unlock_mutex(t_philo *philo_p);
int				check_death_l(t_philo *philo_p);
int				init_philo_loop(t_philo *philo_p);

#endif
