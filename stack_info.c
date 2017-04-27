/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:17:54 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/26 15:24:00 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		smallest(int *a, int size)
{
	int		i;
	int		min = 2147483647;

	i = 0;
	while (i < size)
	{
		if (a[i] < min)
			min = a[i];
		i++;
	}
	return (min);
}

int		biggest(int *a, int size)
{
	int		i;
	int		max = -2147483648;

	i = 0;
	while (i < size)
	{
		if (a[i] > max)
			max = a[i];
		i++;
	}
	return (max);
}
