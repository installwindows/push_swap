/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pssort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:01:02 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/30 18:32:01 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	do_op(t_stack *a, t_stack *b, t_oplst ***cur, const char *op)
{
}

t_oplst	*pssort(t_stack *a, t_flag *f)
{
	t_oplst	*lst;
	t_stack	*b;
	int		med;
	char	queue[3][3];

	med = f->stack->array[f->stack->size / 2];
	lst = NULL;
	b = create_stack(NULL, a->size);
	while (!array_cmp(f->stack->array, f->stack->size, a->array, a->size))
	{
		op_a(a, queue);
		op_b(b, queue);
		do_op(a, b, &lst, queue);
		if (a->size && a->array[a->top] < med)
			do_op(a, b, &lst, "pb");
		if (a->size && a->array[a->top] > med && a->size > 1 && a->array[a->top - 1] < a->array[a->top])
			do_op(a, b, &lst, "sa");
		else if (a->size && a->array[a->top] > med)
			do_op(a, b, &lst, "ra");
	}
}
