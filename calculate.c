/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 00:33:15 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/25 01:01:52 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void		calculate_b(t_s *n, t_stack *b)
{
	int		down;
	int		i;
	int		p_d;

	down = -2147483648;
	i = n->num > b->max || n->num < b->min ? b->size - 1 : b->size;
	if ((p_d = -1) && (n->num > b->max || n->num < b->min))
		while (((n->step_b = i) || 1) && b->array[i] != b->max)
			i--;
	else
		while (--i >= 0)
			if (b->array[i] < n->num && b->array[i] > down && ((p_d = i) || 1))
			{
				down = b->array[i];
				n->step_b = i;
			}
	if (p_d > n->step_b && p_d > b->size / 2)
		n->step_b = p_d;
	n->dir_b = n->step_b < b->size / 2 ? 1 : 0;
	if (n->step_b == 0)
		n->step_b = 1;
	else
		n->step_b = n->step_b < b->size / 2 ? n->step_b + 1 : b->size -
					n->step_b - 1;
}

static void	calculate_total_step(t_s *n, t_stack *a, t_stack *b)
{
	if (n->step_a > b->size && n->dir_a != n->dir_b)
	{
		if (n->dir_b == 1 && !(n->rrb = 0))
			n->rb = b->size - n->step_b;
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
}

static void	calculate_total_r(t_s *n)
{
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
}

static void	calculate_total_rr(t_s *n)
{
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
}

void		calculate_total(t_s *n, t_stack *a, t_stack *b)
{
	if (n->dir_a == 0)
		n->ra = n->step_a;
	else
		n->rra = n->step_a;
	if (n->dir_b == 0)
		n->rb = n->step_b;
	else
		n->rrb = n->step_b;
	calculate_total_step(n, a, b);
	calculate_total_r(n);
	calculate_total_rr(n);
	n->total = n->ra + n->rb + n->rra + n->rrb + n->rr + n->rrr + 1;
}
