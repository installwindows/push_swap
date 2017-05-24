/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:21:55 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/23 22:12:31 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(int argc, char **argv)
{
	int		array[] = {10, 2, 4, 6, 8};
	int		size = sizeof(array) / sizeof(int);

	int		min;
	int		max;
	int		up;
	int		down;
	int		num;

	if (argc != 2)
		return (1);
	num = ft_atoi(argv[1]);
	ft_find_min_max(array, size, &min, &max);
	up = -2147483648;
	down = 2147483647;
	
	int		i;
	int		j;

	j = 0;
	i = size;
	if (num > max)
	{
		while (--i >= 0)
			if (array[i] == max)
				break ;
		j = i;
	}
	else if (num < min)
	{
		while (--i >= 0)
			if (array[i] == max)
				break ;
		j = i;
	}
	else
	{
		while (--i >= 0)
		{
			if (array[i] < num && array[i] < down)
			{
				down = array[i];
				j = i;
			}
			else if (array[i] > num && array[i] > up)
			{
				up = array[i];
				j = i;
			}
		}
	}
	j = size - j - 1;
	i = size;
	while (--i >= 0)
		ft_printf(i > 0 ? "%d " : "%d\n", array[i]);
	ft_printf("up: %d\ndown: %d\nj: %d\n", up, down, j);
}
