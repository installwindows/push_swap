/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:50:55 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/25 00:15:24 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

typedef struct	s_s
{
	int			f;
	int			num;
	int			step_a;
	int			step_b;
	int			total;
	int			dir_a;
	int			dir_b;
	int			ra;
	int			rra;
	int			rb;
	int			rrb;
	int			rr;
	int			rrr;
}				t_s;

void	calculate_b(t_s *n, t_stack *b)
{
	int		down;
	int		dir;
	int		i;
	int		j;
	int		p_d;

	down = -2147483648;
	dir = 0;
	p_d = 0;
	j = 0;
	i = b->size;
	if (n->num > b->max)
	{
		while (--i >= 0)
			if (b->array[i] == b->max)
				break ;
		j = i;
	}
	else if (n->num < b->min)
	{
		while (--i >= 0)
			if (b->array[i] == b->max)
				break ;
		j = i;
	}
	else
	{
		while (--i >= 0)
			if (b->array[i] < n->num && b->array[i] > down)
			{
				down = b->array[i];
				p_d = i;
				j = i;
			}
		if (p_d > j && p_d > b->size / 2)
			j = p_d;
	}
	dir = j < b->size / 2 ? 1 : 0;//1: rrb, 0: rb
	if (j == 0)
		j = 1;
	else
		j = j < b->size / 2 ? j + 1: b->size - j - 1;
	n->dir_b = dir;
	n->step_b = j;
}

void	calculate_total(t_s *n, t_stack *a, t_stack *b)
{
	if (n->dir_a == 0)
		n->ra = n->step_a;
	else
		n->rra = n->step_a;
	if (n->dir_b == 0)
		n->rb = n->step_b;
	else
		n->rrb = n->step_b;
	if (n->step_a > b->size && n->dir_a != n->dir_b)
	{
		if (n->dir_b == 1)
		{
			n->rrb = 0;
			n->rb = b->size - n->step_b;
		}
		else
		{
			n->rb = 0;
			n->rrb = b->size - n->step_b;
		}
	}
	else if (n->step_b > a->size && n->dir_a != n->dir_b)
	{
		if (n->dir_a == 1)
		{
			n->rra = 0;
			n->ra = a->size - n->step_a;
		}
		else
		{
			n->ra = 0;
			n->rra = a->size - n->step_a;
		}
	}
	if (n->ra && n->rb)
	{
		if (n->ra - n->rb > 0)
		{
			n->rr = n->rb;
			n->ra -= n->rb;
			n->rb = 0;
		}
		else
		{
			n->rr = n->ra;
			n->rb -= n->ra;
			n->ra = 0;
		}
	}
	if (n->rra && n->rrb)
	{
		if (n->rra - n->rrb > 0)
		{
			n->rrr = n->rrb;
			n->rra -= n->rrb;
			n->rrb = 0;
		}
		else
		{
			n->rrr = n->rra;
			n->rrb -= n->rra;
			n->rra = 0;
		}
	}
	n->total = n->ra + n->rb + n->rra + n->rrb + n->rr + n->rrr + 1;
}

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
