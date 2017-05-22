/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:42:08 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 17:20:49 by varnaud          ###   ########.fr       */
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

static void	find_next_to_sort(t_stack *a, int *i, int *dir)
{
	int		k;

	k = a->size;
	while (--k >= 0)
		if (a->array[k] == *i)
			break ;
	while (1)
	{
		k--;
		if (k < 0)
			k = a->size - 1;
		if (a->array[k] != ++(*i))
			break ;
	}
	k = 0;
	while (k < a->size && a->array[k] != *i)
		k++;
	*dir = k > a->size / 2 ? 0 : 1;
}

static void	set_min_to_head(t_stack *a, t_oplst ***cur, t_flag *f)
{
	int		i;

	i = a->size;
	while (--i >= 0)
		if (a->array[i] == f->min)
			break ;
	if (a->size - i == 1)
		return ;
	if (a->size / 2 < i)
		while (a->array[a->size - 1] != f->min)
			do_op(a, NULL, cur, "ra");
	else
		while (a->array[a->size - 1] != f->min)
			do_op(a, NULL, cur, "rra");
}

static void	sort_stack(t_stack *a, t_oplst **lst, t_flag *f)
{
	t_stack	*b;
	t_oplst	**cur;
	int		i;
	int		dir;

	cur = lst;
	b = create_stack(NULL, a->size);
	i = 1;
	while (!(array_cmp(f->stack->array, f->stack->size, a->array, a->size)))
	{
		find_next_to_sort(a, &i, &dir);
		if (i > f->max)
			break ;
		while (HEAD(a, 0) != i)
			do_op(a, b, &cur, dir == 0 ? "ra" : "rra");
		do_op(a, b, &cur, "pb");
		while (TAIL(a, 0) != i - 1)
			do_op(a, b, &cur, dir == 0 ? "rra" : "ra");
		do_op(a, b, &cur, "pa");
	}
	set_min_to_head(a, &cur, f);
	i = a->size;
	while (--i >= 0)
		ft_printf(i > 0 ? "%d " : "%d\n", a->array[i]);
	free_stack(b);
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

static void	set_max_maxx(t_stack *a, t_flag *f, int *maxx, int *pmax)
{
	int		i;

	*maxx = -2147438648;
	*pmax = 0;
	i = a->size;
	while (i-- >= 0)
	{
		if (a->array[i] != f->max && a->array[i] > *maxx)
			*maxx = a->array[i];
		if (a->array[i] == f->max)
			*pmax = a->size - i - 1;
	}
}

static void	find_min_max(t_stack *s, int *min, int *max)
{
	int		i;

	*min = 2147438647;
	*max = -2147438648;
	i = s->size;
	while (--i >= 0)
	{
		if (s->array[i] > *max)
			*max = s->array[i];
		if (s->array[i] < *min)
			*min = s->array[i];
	}
}
static void	sort_rev_3(t_stack *b, t_oplst ***cur)
{
	int		min;
	int		max;

	find_min_max(b, &min, &max);
	if (b->array[2] != max && b->array[2] != min)
	{
		if (b->array[1] == min)
			do_op(NULL, b, cur, "rrb");
		else
			do_op(NULL, b, cur, "sb");
	}
	else if (b->array[2] == max)
	{
		if (b->array[1] == min)
		{
			do_op(NULL, b, cur, "sb");
			do_op(NULL, b, cur, "rb");
		}
	}
	else if (b->array[2] == min)
	{
		if (b->array[0] == max)
		{
			do_op(NULL, b, cur, "sb");
			do_op(NULL, b, cur, "rrb");
		}
		else
			do_op(NULL, b, cur, "rb");
	}
}
static void sort_5(t_stack *a, t_oplst **lst, t_flag *f)
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
		if (HEAD(a, 0) != f->max && HEAD(a, 0) != maxx &&  HEAD(a, 0) > HEAD(a, 1))
			do_op(a, b, &cur, "sa");
		else if ((HEAD(a, 1) == f->max && HEAD(a, 0) != maxx) && HEAD(a, 0) < HEAD(a, 1))
			do_op(a, b, &cur, "pb");

		else
			do_op(a, NULL, &cur, pmax <= 2 ? "ra" : "rra");
	}
	while (a->size != 2)
		if (HEAD(a, 0) > HEAD(a, 1))
		{
			do_op(a, b, &cur, "sa");
			do_op(a, b, &cur, "pb");
		}
		else
			do_op(a, b, &cur, "pb");
	sort_rev_3(b, &cur);
	do_op(a, b, &cur, "pa");
	do_op(a, b, &cur, "pa");
	do_op(a, b, &cur, "pa");
	free_stack(b);
}

static int	next_min(t_stack *a, int min, int max)
{
	int		i;
	int		tmp;

	tmp = max;
	i = a->size;
	while (--i >= 0)
	{
		if (a->array[i] < tmp && a->array[i] > min)
			tmp = a->array[i];
	}
	return (tmp);
}

static int	min_location(t_stack *a, int min)
{
	int		i;

	i = a->size;
	while (--i >= 0)
		if (a->array[i] == min)
			return (a->size - i - 1);
	return (i);
}

static void	sort_x(t_stack *a, t_oplst **lst, t_flag *f)
{
	t_stack	*b;
	t_oplst	**cur;
	int		min;
	int		step;

	cur = lst;
	b = create_stack(NULL, a->size);
	min = f->min;
	step = min_location(a, min);
	while (min < f->max)
	{
		if (HEAD(a, 0) == min)
		{
			do_op(a, b, &cur, "pb");
			min = next_min(a, min, f->max);
			step = min_location(a, min);
		}
		else
			do_op(a, NULL, &cur, step > a->size / 2 ? "rra" : "ra");
	}
	while (b->size)
		do_op(a, b, &cur, "pa");
	free_stack(b);
}

int			pushswap(t_stack *a, t_flag *flag)
{
	t_oplst	*lst;
	t_oplst	*cur;
	int		length;


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
	length = 0;
	while (lst)
	{
		length++;
		ft_fprintf(flag->fdout, "%s\n", lst->op);
		lst = lst->next;
	}
	ft_printf(flag->flag & FLAG_D ? "Total: %d\n" : "", length);
	cleanup(cur);
	return (0);
}
