/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_5_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:40:16 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/22 21:25:42 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void		set_max_maxx(t_stack *a, t_flag *f, int *maxx, int *pmax)
{
	int		i;

	*maxx = -2147483648;
	*pmax = 0;
	i = a->size;
	while (i-- >= 0)
	{
		if (a->array[i] != f->max && a->array[i] > *maxx)
			*maxx = a->array[i];
		if (a->array[i] == f->max)
			*pmax = a->size - i - 1;
	}
}

static void	sort_rev_3_min(t_stack *b, t_oplst ***cur, int max)
{
	if (b->array[0] == max)
	{
		do_op(NULL, b, cur, "sb");
		do_op(NULL, b, cur, "rrb");
	}
	else
		do_op(NULL, b, cur, "rb");
}

void		sort_rev_3(t_stack *b, t_oplst ***cur)
{
	int		min;
	int		max;

	ft_find_min_max(b->array, b->size, &min, &max);
	if (b->array[2] != max && b->array[2] != min)
	{
		if (b->array[1] == min)
			do_op(NULL, b, cur, "rrb");
		else
			do_op(NULL, b, cur, "sb");
	}
	else if (b->array[2] == max)
	{
		if (b->array[1] == min)
		{
			do_op(NULL, b, cur, "sb");
			do_op(NULL, b, cur, "rb");
		}
	}
	else if (b->array[2] == min)
		sort_rev_3_min(b, cur, max);
}
