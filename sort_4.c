/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 01:02:24 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/25 19:01:23 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	sort_4(t_stack *a, t_oplst **lst)
{
	t_oplst	**cur;
	int		i;
	t_stack	*b;

	b = create_stack(NULL, a->size);
	cur = lst;
	i = a->size;
	while (--i >= 0)
		if (a->array[i] == a->max)
			break ;
	i = i < a->size / 2 ? 1 : 0;
	while (a->array[0] != a->max)
		do_op(a, b, &cur, i ? "rra" : "ra");
	do_op(a, b, &cur, "pb");
	do_op(a, b, &cur, "pb");
	do_op(a, b, &cur, "pb");
	sort_rev_3(b, &cur);
	do_op(a, b, &cur, "pa");
	do_op(a, b, &cur, "pa");
	do_op(a, b, &cur, "pa");
	free_stack(b);
}
