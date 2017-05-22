/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:42:08 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 18:26:18 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int			cleanup(t_oplst *lst)
{
	t_oplst	*cur;

	while (lst)
	{
		cur = lst->next;
		free(lst->op);
		free(lst);
		lst = cur;
	}
	return (0);
}

int			do_op(t_stack *a, t_stack *b, t_oplst ***cur, const char *op)
{
	**cur = malloc(sizeof(t_oplst));
	(**cur)->op = ft_strdup(op);
	(**cur)->next = NULL;
	*cur = &(**cur)->next;
	return (execute(op, a, b));
}

static void	sort_2(t_stack *a, t_oplst **lst, t_flag *f)
{
	t_oplst	**cur;

	cur = lst;
	if (a->array[1] == f->max)
		do_op(a, NULL, &cur, "sa");
}

static void	sort_3(t_stack *a, t_oplst **lst, t_flag *f)
{
	t_oplst	**cur;

	cur = lst;
	if (a->array[2] != f->max && a->array[2] != f->min)
	{
		if (a->array[1] == f->min)
			do_op(a, NULL, &cur, "sa");
		else
			do_op(a, NULL, &cur, "rra");
	}
	else if (a->array[2] == f->min)
	{
		if (a->array[1] == f->max)
		{
			do_op(a, NULL, &cur, "rra");
			do_op(a, NULL, &cur, "sa");
		}
	}
	else if (a->array[2] == f->max)
	{
		do_op(a, NULL, &cur, "ra");
		if (a->array[2] != f->min)
			do_op(a, NULL, &cur, "sa");
	}
}

int			pushswap(t_stack *a, t_flag *flag)
{
	t_oplst	*lst;
	t_oplst	*cur;

	find_min_max(a, &flag->min, &flag->max);
	lst = NULL;
	if (array_cmp(flag->stack->array, flag->stack->size, a->array, a->size))
		;
	else if (a->size == 2)
		sort_2(a, &lst, flag);
	else if (a->size == 3)
		sort_3(a, &lst, flag);
	else if (a->size == 5)
		sort_5(a, &lst, flag);
	else
		sort_x(a, &lst, flag);
	cur = lst;
	while (lst)
	{
		flag->length++;
		ft_fprintf(flag->fdout, "%s\n", lst->op);
		lst = lst->next;
	}
	ft_printf(flag->flag & FLAG_D ? "Total: %d\n" : "", flag->length);
	cleanup(cur);
	return (0);
}
