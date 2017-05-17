/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pssort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:01:02 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/16 23:24:38 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	do_op(t_stack *a, t_stack *b, t_oplst ***cur, const char *op)
{
}

static void	first_phase(t_stack *a. t_stack *b, t_oplst **cur, t_flag *f)
{
	while (!array_cmp(f->stack->array, f->stack->size, a->array, a->size))
	{
		if (a->size && a->array[a->top] < med)
			do_op(a, b, &lst, "pb");
		if (a->size && a->array[a->top] > med && a->size > 1 && a->array[a->top - 1] < a->array[a->top])
			do_op(a, b, &lst, "sa");
		else if (a->size && a->array[a->top] > med)
			do_op(a, b, &lst, "ra");
	}

}

static void	second_phase(t_stack *a. t_stack *b, t_oplst **cur, t_flag *f)
{
}

t_oplst	*pssort(t_stack *a, t_flag *f)
{
	t_oplst	*lst;
	t_oplst	**cur;
	t_stack	*b;

	lst = NULL;
	cur = &lst;
	b = create_stack(NULL, a->size);
	first_phase(a, b, cur, f);
	second_phase(a, b, cur, f);
	return (lst);
}
