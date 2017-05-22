/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 18:18:46 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 18:21:49 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	next_min(t_stack *a, int min, int max)
{
	int		i;
	int		tmp;

	tmp = max;
	i = a->size;
	while (--i >= 0)
	{
		if (a->array[i] < tmp && a->array[i] > min)
			tmp = a->array[i];
	}
	return (tmp);
}

static int	min_location(t_stack *a, int min)
{
	int		i;

	i = a->size;
	while (--i >= 0)
		if (a->array[i] == min)
			return (a->size - i - 1);
	return (i);
}

void		sort_x(t_stack *a, t_oplst **lst, t_flag *f)
{
	t_stack	*b;
	t_oplst	**cur;
	int		min;
	int		step;

	cur = lst;
	b = create_stack(NULL, a->size);
	min = f->min;
	step = min_location(a, min);
	while (min < f->max)
	{
		if (HEAD(a, 0) == min)
		{
			do_op(a, b, &cur, "pb");
			min = next_min(a, min, f->max);
			step = min_location(a, min);
		}
		else
			do_op(a, NULL, &cur, step > a->size / 2 ? "rra" : "ra");
	}
	while (b->size)
		do_op(a, b, &cur, "pa");
	free_stack(b);
}
