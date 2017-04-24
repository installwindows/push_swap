/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:42:08 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/24 01:06:33 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

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
	while (!is_sort(a->array, a->size, f->stack->array, f->stack->size))
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
}

static int	smallest(int *a, int size)
{
	int		i;
	int		min = 2147483647;

	i = 0;
	while (i < size)
	{
		if (a[i] < min)
			min = a[i];
		i++;
	}
	return (min);
}

static int	biggest(int *a, int size)
{
	int		i;
	int		max = -2147483648;

	i = 0;
	while (i < size)
	{
		if (a[i] > max)
			max = a[i];
		i++;
	}
	return (max);
}

int			pushswap(t_stack *a, t_flag *flag)
{
	t_oplst	*lst;
	int		length;

	flag->min = smallest(a->array, a->size);
	flag->max = biggest(a->array, a->size);
	lst = NULL;
	length = naive_sort(a, &lst, flag);
	if (length == -1)
		return (-1);
	//ft_printf("length: %d\n", length);
	while (lst)
	{
		ft_fprintf(flag->fdout, "%s\n", lst->op);
		lst = lst->next;
	}
	return (0);
}
