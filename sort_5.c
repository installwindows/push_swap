/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 18:16:07 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 18:29:03 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	set_max_maxx(t_stack *a, t_flag *f, int *maxx, int *pmax)
{
	int		i;

	*maxx = -2147438648;
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

void		find_min_max(t_stack *s, int *min, int *max)
{
	int		i;

	*min = 2147438647;
	*max = -2147438648;
	i = s->size;
	while (--i >= 0)
	{
		if (s->array[i] > *max)
			*max = s->array[i];
		if (s->array[i] < *min)
			*min = s->array[i];
	}
}

static void	sort_rev_3(t_stack *b, t_oplst ***cur)
{
	int		min;
	int		max;

	find_min_max(b, &min, &max);
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
	{
		if (b->array[0] == max)
		{
			do_op(NULL, b, cur, "sb");
			do_op(NULL, b, cur, "rrb");
		}
		else
			do_op(NULL, b, cur, "rb");
	}
}

void		sort_5(t_stack *a, t_oplst **lst, t_flag *f)
{
	t_stack	*b;
	t_oplst	**cur;
	int		pmax;
	int		maxx;

	cur = lst;
	b = create_stack(NULL, a->size);
	set_max_maxx(a, f, &maxx, &pmax);
	while (TAIL(a, 0) != f->max)
	{
		if (HEAD(a, 0) != f->max && HEAD(a, 0) != maxx &&  HEAD(a, 0) > HEAD(a, 1))
			do_op(a, b, &cur, "sa");
		else if ((HEAD(a, 1) == f->max && HEAD(a, 0) != maxx) && HEAD(a, 0) < HEAD(a, 1))
			do_op(a, b, &cur, "pb");
		else
			do_op(a, NULL, &cur, pmax <= 2 ? "ra" : "rra");
	}
	while (a->size != 2)
		if (HEAD(a, 0) > HEAD(a, 1))
		{
			do_op(a, b, &cur, "sa");
			do_op(a, b, &cur, "pb");
		}
		else
			do_op(a, b, &cur, "pb");
	sort_rev_3(b, &cur);
	do_op(a, b, &cur, "pa");
	do_op(a, b, &cur, "pa");
	do_op(a, b, &cur, "pa");
	free_stack(b);
}
