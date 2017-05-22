/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 18:16:07 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 21:26:17 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	push_back_to_a(t_stack *a, t_stack *b, t_oplst ***cur)
{
	while (a->size != 2)
		if (HEAD(a, 0) > HEAD(a, 1))
		{
			do_op(a, b, cur, "sa");
			do_op(a, b, cur, "pb");
		}
		else
			do_op(a, b, cur, "pb");
	sort_rev_3(b, cur);
	do_op(a, b, cur, "pa");
	do_op(a, b, cur, "pa");
	do_op(a, b, cur, "pa");
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
		if (HEAD(a, 0) != f->max && HEAD(a, 0) != maxx &&
									HEAD(a, 0) > HEAD(a, 1))
			do_op(a, b, &cur, "sa");
		else if (HEAD(a, 0) < HEAD(a, 1) &&
				!(HEAD(a, 1) == f->max && HEAD(a, 0) == maxx))
			do_op(a, b, &cur, "pb");
		else
			do_op(a, NULL, &cur, pmax <= 2 ? "ra" : "rra");
	}
	push_back_to_a(a, b, &cur);
	free_stack(b);
}
