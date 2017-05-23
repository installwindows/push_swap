/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_min_max.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 21:12:54 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/22 21:18:04 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_find_min_max(int *array, int size, int *min, int *max)
{
	int		i;

	if (array == NULL || size <= 0)
		return (1);
	*min = 2147483647;
	*max = -2147483648;
	i = size;
	while (--i >= 0)
	{
		if (array[i] > *max)
			*max = array[i];
		if (array[i] < *min)
			*min = array[i];
	}
	return (0);
}
