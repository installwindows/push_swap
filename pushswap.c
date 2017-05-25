/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:42:08 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/25 00:26:40 by varnaud          ###   ########.fr       */
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

void		sort_3(t_stack *s, t_oplst **cur, char c)
{
	if (s->array[2] != s->max && s->array[2] != s->min)
	{
		if (s->array[1] == s->min)
			do_op(s, NULL, &cur, c == 'a' ? "sa" : "sb");
		else
			do_op(s, NULL, &cur, c == 'a' ? "rra" : "rrb");
	}
	else if (s->array[2] == s->min)
	{
		if (s->array[1] == s->max)
		{
			do_op(s, NULL, &cur, c == 'a' ? "rra" : "rrb");
			do_op(s, NULL, &cur, c == 'a' ? "sa" : "sb");
		}
	}
	else if (s->array[2] == s->max)
	{
		do_op(s, NULL, &cur, c == 'a' ? "ra" : "rb");
		if (s->array[2] != s->min)
			do_op(s, NULL, &cur, c == 'a' ? "sa" : "sb");
	}
}

void		sort_4(t_stack *a, t_oplst **lst)
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
}

int			pushswap(t_stack *a, t_flag *flag)
{
	t_oplst	*lst;
	t_oplst	*cur;

	ft_find_min_max(a->array, a->size, &flag->min, &flag->max);
	lst = NULL;
	if (array_cmp(flag->stack->array, flag->stack->size, a->array, a->size))
		;
	else if (a->size == 2)
		sort_2(a, &lst, flag);
	else if (a->size == 3)
		sort_3(a, &lst, 'a');
	else if (a->size == 4)
		sort_4(a, &lst);
	else if (a->size == 5)
		sort_5(a, &lst, flag);
	else
		sort_alot(a, &lst, flag);
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
