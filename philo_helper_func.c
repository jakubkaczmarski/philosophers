/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:49:16 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/30 17:42:04 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	counter;
	int	negative;

	negative = 1;
	counter = 0;
	while (str[counter] == ' ' || str[counter] == '\t' || str[counter] == '\n'
		|| str[counter] == '\v' || str[counter] == '\f' || str[counter] == '\r')
		counter++;
	if (str[counter] == '-' || str[counter] == '+')
	{
		if (str[counter] == '-')
			negative = -1;
		counter++;
	}
	res = 0;
	while (str[counter] != '\0' && ft_isdigit(str[counter]))
		res = res * 10 + (str[counter++] - '0');
	return (res * negative);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	counter;
	unsigned char	*magic;
	unsigned char	*helpme;

	counter = 0;
	magic = (unsigned char *)s1;
	helpme = (unsigned char *)s2;
	while ((magic[counter] != '\0' || helpme[counter] != '\0'))
	{
		if (magic[counter] != helpme[counter])
		{
			return (magic[counter] - helpme[counter]);
		}
		counter++;
	}
	return (0);
}

char	*ft_itoa(int n)
{
	char	*resarr;
	int		len;
	int		negative;

	negative = 1;
	if (n == -2147483648)
		return (run_edgecase());
	if (n < 0)
	{
		negative = -1;
		n = -n;
	}
	len = getlenght(n);
	if (negative == -1 || n == 0)
		len++;
	resarr = malloc(sizeof(char) * (len + 1));
	if (!(resarr))
	{
		free(resarr);
		return (NULL);
	}
	resarr[len] = '\0';
	checkedgecase(resarr, &negative, n, &len);
	return (resarr);
}

int	check_for_int_overflow(int num, char *str)
{
	char	*str1;

	str1 = ft_itoa(num);
	if (ft_strcmp(str1, str) == 0)
	{
		free(str1);
		return (1);
	}
	else
	{
		free(str1);
		return (0);
	}
}

t_philo_data	*philo_assigment(char **argv)
{
	t_philo_data	*philo;

	philo = malloc(sizeof(t_philo_data));
	philo->philo_num = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	return (philo);
}
