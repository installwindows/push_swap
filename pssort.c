/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pssort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:01:02 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/26 17:45:40 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_oplst	*pssort(t_stack *a, t_flag *f)
{
	t_oplst	*lst;
	t_stack	*b;
	int		med;

	med = f->stack->array[f->stack->size / 2];
	lst = NULL;
	b = create_stack(NULL, a->size);
	while (!array_cmp(f->stack->array, f->stack->size, a->array, a->size))
	{
		if (a->size && a->array[a->top] < med)
			do_op(a, b, &lst, "pb");
		
	}
}
