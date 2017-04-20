/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:57:14 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/19 23:50:12 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "operation.h"

int			execute(const char *op, t_stack *a, t_stack *b)
{
	if (!ft_strcmp(op, "sa"))
		return (do_swap(a));
	else if (!ft_strcmp(op, "sb"))
		return (do_swap(b));
	else if (!ft_strcmp(op, "ss"))
		return (do_swap(a) + do_swap(b));
	else if (!ft_strcmp(op, "pa"))
		return (do_push(a, b));
	else if (!ft_strcmp(op, "pb"))
		return (do_push(b, a));
	else if (!ft_strcmp(op, "ra"))
		return (do_rotate(a, 1));
	else if (!ft_strcmp(op, "rb"))
		return (do_rotate(b, 1));
	else if (!ft_strcmp(op, "rr"))
		return (do_rotate(a, 1) + do_rotate(b, 1));
	else if (!ft_strcmp(op, "rra"))
		return (do_rotate(a, a->size - 1));
	else if (!ft_strcmp(op, "rrb"))
		return (do_rotate(b, b->size - 1));
	else if (!ft_strcmp(op, "rrr"))
		return (do_rotate(a, a->size - 1) + do_rotate(b, b->size - 1));
	else
		return (1);
	return (0);
}

int			do_swap(t_stack *stack)
{
	int		tmp;

	if (stack->size < 2)
		return (0);
	tmp = stack->array[stack->size - 1];
	stack->array[stack->size - 1] = stack->array[stack->size - 2];
	stack->array[stack->size - 2] = tmp;
	return (0);
}

int			do_push(t_stack *x, t_stack *y)
{
	int		value;

	if (y->size == 0)
		return (0);
	if (pop(y, &value))
		return (-1);
	if (push(x, value))
		return (-1);
	return (0);
}

static void	reverse_array(int *a, int i, int j)
{
	int		tmp;

	while (i < j)
	{
		tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
		i++;
		j--;
	}
}

int			do_rotate(t_stack *stack, int d)
{
	if (stack->size <= 2)
		return (do_swap(stack));
	reverse_array(stack->array, stack->size - d, stack->size - 1);
	reverse_array(stack->array, 0, stack->size - d - 1);
	reverse_array(stack->array, 0, stack->size - 1);
	return (0);
}
