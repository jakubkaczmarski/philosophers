/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 11:25:14 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/03/30 13:50:28 by jkaczmar         ###   ########.fr       */
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
