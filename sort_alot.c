/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:50:55 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/25 00:52:42 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	find_next(t_stack *a, t_stack *b, t_s *n)
{
	t_s		tmp;
	int		i;

	n->total = 2147483647;
	i = a->size;
	while (--i >= 0)
	{
		ft_memset(&tmp, 0, sizeof(t_s));
		tmp.num = a->array[i];
		tmp.step_a = a->size - i - 1;
		if (tmp.step_a > a->size / 2)
		{
			tmp.step_a = ft_abs(tmp.step_a - a->size);
			tmp.dir_a = 1;
		}
		calculate_b(&tmp, b);
		calculate_total(&tmp, a, b);
		if (tmp.total < n->total)
			ft_memcpy(n, &tmp, sizeof(t_s));
	}
}

void	sort_it(t_stack *a, t_stack *b, t_oplst ***cur)
{
	t_s		n;

	find_next(a, b, &n);
	while (n.ra-- > 0)
		do_op(a, b, cur, "ra");
	while (n.rb-- > 0)
		do_op(a, b, cur, "rb");
	while (n.rra-- > 0)
		do_op(a, b, cur, "rra");
	while (n.rrb-- > 0)
		do_op(a, b, cur, "rrb");
	while (n.rr-- > 0)
		do_op(a, b, cur, "rr");
	while (n.rrr-- > 0)
		do_op(a, b, cur, "rrr");
	do_op(a, b, cur, "pb");
}

void	align_a_and_b(t_stack *a, t_stack *b, t_oplst ***cur)
{
	int		i;

	i = b->size;
	while (b->array[--i] != b->max)
		;
	if (i > b->size / 2)
		while (++i < b->size)
			do_op(a, b, cur, "rb");
	else
		while (i-- >= 0)
			do_op(a, b, cur, "rrb");
}

void	sort_alot(t_stack *a, t_oplst **cur, t_flag *f)
{
	t_stack	*b;

	if (f)
		;
	b = create_stack(NULL, a->size);
	do_op(a, b, &cur, "pb");
	do_op(a, b, &cur, "pb");
	do_op(a, b, &cur, "pb");
	sort_rev_3(b, &cur);
	while (a->size)
		sort_it(a, b, &cur);
	align_a_and_b(a, b, &cur);
	while (b->size)
		do_op(a, b, &cur, "pa");
	free_stack(b);
}
