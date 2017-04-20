/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:57:14 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/19 21:47:20 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "operation.h"

int		execute(const char *op, t_stack *a, t_stack *b)
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
		return (do_rotate(a));
	else if (!ft_strcmp(op, "rb"))
		return (do_rotate(b));
	else if (!ft_strcmp(op, "rr"))
		return (do_rotate(a) + do_rotate(b));
	else if (!ft_strcmp(op, "rra"))
		return (do_rev_rotate(a));
	else if (!ft_strcmp(op, "rrb"))
		return (do_rev_rotate(b));
	else if (!ft_strcmp(op, "rrr"))
		return (do_rev_rotate(a) + do_rev_rotate(b));
	else
		return (1);
	return (0);
}

int		do_swap(t_stack *stack)
{
	int		tmp;

	if (stack->size < 2)
		return (0);
	tmp = stack->array[stack->size - 1];
	stack->array[stack->size - 1] = stack->array[stack->size - 2];
	stack->array[stack->size - 2] = tmp;
	return (0);
}

int		do_push(t_stack *x, t_stack *y)
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

int		do_rotate(t_stack *stack)
{
	int		i;
	int		prev;
	int		next;

	if (stack->size <= 2)
		return (do_swap(stack));
	prev = stack->array[0];
	stack->array[0] = stack->array[stack->size - 1];
	i = 1;
	while (i < stack->size - 1)
	{
		next = stack->array[i];
		stack->array[i] = prev;
		prev = next;
		i++;
	}
	return (0);
}

int		do_rev_rotate(t_stack *stack)
{
	int		i;
	int		prev;
	int		next;

	if (stack->size <= 2)
		return (do_swap(stack));
	prev = stack->array[stack->size - 1];
	stack->array[stack->size - 1] = stack->array[0];
	i = stack->size - 1;
	while (--i)
	{
		next = stack->array[i];
		stack->array[i] = prev;
		prev = next;
	}
	return (0);
}
