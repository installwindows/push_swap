/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:42:08 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 06:17:15 by varnaud          ###   ########.fr       */
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
/*
int			do_op(t_stack *a, t_stack *b, t_oplst **lst, const char *op)
{
	t_oplst	**cur;

	cur = lst;
	while (*cur)
		cur = &(*cur)->next;
	if (!(*cur = malloc(sizeof(t_oplst))))
		return (-1);
	(*cur)->op = ft_strdup(op);
	(*cur)->next = NULL;
	return (execute(op, a, b));
}
*/
int			do_op(t_stack *a, t_stack *b, t_oplst ***cur, const char *op)
{
	**cur = malloc(sizeof(t_oplst));
	(**cur)->op = ft_strdup(op);
	(**cur)->next = NULL;
	*cur = &(**cur)->next;
	return (execute(op, a, b));
}
/*
int			naive_sort(t_stack *a, t_oplst **lst, t_flag *f)
{
	int		length;
	int		top;
	int		r;
	t_stack	*b;

	if (!(b = create_stack(NULL, a->size)))
		return (1);
	length = 0;
	top = a->size - 1;
	while (!array_cmp(a->array, a->size, f->stack->array, f->stack->size))
	{
		if (a->array[top] == f->max && a->array[top - 1] == f->min)
			r = do_op(a, b, lst, "ra");
		else if (a->array[top] > a->array[top - 1])
			r = do_op(a, b, lst, "sa");
		else
			r = do_op(a, b, lst, "ra");
		if (r)
			return (-1);
		length++;
	}
	free_stack(b);
	return (length);
}*/
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

#define HEAD(a, n) a->array[a->size - 1 - n]
#define TAIL(a, n) a->array[n]
#define MIN f->min
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

static void	set_minmax(t_stack *a, t_flag *f, int *pmin, int *pmax)
{
	int		i;

	*pmin = 0;
	*pmax = 0;
	i = a->size;
	while (i-- >= 0)
	{
		if (a->array[i] == f->min)
			*pmin = a->size - i - 1;
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
	int		pmin;

	cur = lst;
	b = create_stack(NULL, a->size);
	set_minmax(a, f, &pmin, &pmax);
	while (TAIL(a, 0) != f->max)
	{
		if (HEAD(a, 0) != f->max && HEAD(a, 0) != 4 &&  HEAD(a, 0) > HEAD(a, 1))
			do_op(a, b, &cur, "sa");
		else if ((HEAD(a, 1) == f->max && HEAD(a, 0) != 4) && HEAD(a, 0) < HEAD(a, 1))
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
	/*
	if (pmax < 3)
	{
		
	}
	else if (pmax > 3)
	{
	}
	else
	{
		if (HEAD(a, 0) > HEAD(a, 1))
			do_op(a, NULL, &cur, "sa");
		else if (HEAD(a, 0) < HEAD(a, 1))
		{
			do_op(a, b, &cur, "pb");
			do_op(a, b, &cur, "pb");
		}
	}
	*/
}


/*
static void	sort_stack(t_stack *a, t_oplst **lst, t_flag *f)
{
	t_stack	*b;
	t_oplst	**cur;

	cur = lst;
	b = create_stack(NULL, a->size);
	while (!(array_cmp(f->stack->array, f->stack->size, a->array, a->size)))
	{
		if (HEAD(a, 0) == MAX && HEAD(a, 1) == MIN)
			do_op(a, b, &cur, "ra");
		if (HEAD(a, 0) + 1 != HEAD(a, 1) && HEAD(a, 1) != MIN)
			do_op(a, b, &cur, "pb");
		else
			do_op(a, b, &cur, "ra");
		if (b->size && HEAD(b, 0) + 1 == HEAD(a, 0))
			do_op(a, b, &cur, "pa");
		else if (b->size && HEAD(b, 0) + 1 != HEAD(a, 0))
			do_op(a, b, &cur, "rb");
	}
	free_stack(b);
}
*/

int			pushswap(t_stack *a, t_flag *flag)
{
	t_oplst	*lst;
	t_oplst	*cur;
	int		length;

	flag->min = smallest(a->array, a->size);
	flag->max = biggest(a->array, a->size);
	lst = NULL;
	if (array_cmp(flag->stack->array, flag->stack->size, a->array, a->size))
		;
	else if (a->size == 2)
		sort_2(a, &lst, flag);
	else if (a->size == 3)
		sort_3(a, &lst, flag);
	else
	{
		sort_5(a, &lst, flag);
		/*
		//length = naive_sort(a, &lst, flag);
		ft_printf("Start sort.\n");
	int	i = a->size;
		while (--i >= 0)
			ft_printf(i > 0 ? "%d " : "%d\n", a->array[i]);
		sort_stack(a, &lst, flag);
		ft_printf("Done\n");
		//if (length == -1)
		//	return (-1);
		//ft_printf("length: %d\n", length);*/
	}
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
