/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:21:21 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/21 12:07:28 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <pthread.h>
typedef struct philosopher{
    pthread_t philo_thread;
    int philo_num;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
}   philosopher_;
int     ft_strcmp(const char *s1, const char *s2);
int     ft_atoi(const char *str);
int     ft_isdigit(int c);
char	*ft_itoa(int n);
int     check_for_int_overflow(int num, char *str);
char    *run_edgecase(void);
int     getlenght(int checknum);
void	checkedgecase(char *resarr, int *negative, int n, int *len);