/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:34:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 18:13:20 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		ft_natoi(char *s, int *n)
{
	int		sign;

	if (s == NULL)
		return (1);
	*n = 0;
	sign = 0;
	if (*s == '-')
		sign = *s++;
	while (*s)
	{
		if (!(*s == '0' || *s == '1' || *s == '2' || *s == '3' || *s == '4' ||
			*s == '5' || *s == '6' || *s == '7' || *s == '8' || *s == '9'))
			return (1);
		if (*n && ((!sign && (long)*n * 10 + (*s - '0') > 2147483647) ||
					(sign && (long)*n * 10 + (*s - '0') > 2147483648L)))
			return (1);
		*n = *n * 10 + (*s - '0');
		s++;
	}
	if (sign && *n)
		*n *= -1;
	return (0);
}

int		check_doublon(int *a, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (a[i] == a[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		array_cmp(int *a, int sizea, int *s, int sizes)
{
	int		i;

	if (sizea != sizes)
		return (0);
	i = 0;
	while (i < sizes)
	{
		if (a[i] != s[i])
			return (0);
		i++;
	}
	return (1);
}

int		*sort(int *a, int size)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (a[i] < a[j])
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (a);
}

int		*revarr(int *a, int size)
{
	int		i;
	int		j;
	int		tmp;

	if (!a)
		return (NULL);
	i = 0;
	j = size - 1;
	while (i < j)
	{
		tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
		i++;
		j--;
	}
	return (a);
}
