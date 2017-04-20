/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:34:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/20 01:53:47 by varnaud          ###   ########.fr       */
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

int		*parse_number(char **numbers, int size)
{
	int		*array;
	int		n;

	if (size < 1 || numbers == NULL)
		return (NULL);
	array = malloc(sizeof(int) * size);
	if (array == NULL)
		return (NULL);
	while (size)
	{
		if (ft_natoi(*numbers, &n))
		{
			free(array);
			return (NULL);
		}
		array[--size] = n;
		numbers++;
	}
	return (array);
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

int		is_sort(int *a, int size)
{
	int		i;
	int		max;

	max = 2147483647;
	i = 0;
	while (i < size)
	{
		if (a[i] <= max)
			max = a[i];
		else
			break ;
		i++;
	}
	return (i == size);
}
