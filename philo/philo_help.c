/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 11:25:14 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/26 11:25:15 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
char	*run_edgecase(void)
{
	char	*resarr;

	resarr = malloc(sizeof(char) * 12);
	resarr[0] = '-';
	resarr[1] = '2';
	resarr[2] = '1';
	resarr[3] = '4';
	resarr[4] = '7';
	resarr[5] = '4';
	resarr[6] = '8';
	resarr[7] = '3';
	resarr[8] = '6';
	resarr[9] = '4';
	resarr[10] = '8';
	resarr[11] = '\0';
	return (resarr);
}
int	getlenght(int checknum)
{
	int	len;

	len = 0;
	while (checknum != 0)
	{
		checknum /= 10;
		len++;
	}
	return (len);
}

void	checkedgecase(char *resarr, int *negative, int n, int *len)
{
	if (*negative == -1)
		resarr[0] = '-';
	else if (n == 0)
		resarr[0] = '0';
	while (n != 0)
	{
		--*len;
		resarr[*len] = n % 10 + '0';
		n = n / 10;
	}
}


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