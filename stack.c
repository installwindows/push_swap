/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:23:12 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/24 23:48:55 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static int	update_stack(t_stack *stack, int max_size)
{
	int		*array;
	int		i;

	array = malloc(sizeof(int) * max_size);
	if (array == NULL)
		return (1);
	i = 0;
	while (i < stack->size)
	{
		array[i] = stack->array[i];
		i++;
	}
	free(stack->array);
	stack->array = array;
	stack->max_size = max_size;
	return (0);
}

void		*free_stack(t_stack *stack)
{
	if (stack == NULL)
		return (NULL);
	if (stack->array)
		free(stack->array);
	free(stack);
	return (NULL);
}

int			push(t_stack *stack, int value)
{
	if (stack->size == stack->max_size)
		if (update_stack(stack, stack->max_size * 2 + 1))
			return (-1);
	stack->top = stack->size;
	stack->array[stack->size++] = value;
	if (stack->size < 2)
		ft_find_min_max(stack->array, stack->size, &stack->min, &stack->max);
	else if (value > stack->max)
		stack->max = value;
	else if (value < stack->min)
		stack->min = value;
	return (0);
}

int			pop(t_stack *stack, int *value)
{
	if (stack->size > 0)
	{
		*value = stack->array[--stack->size];
		if (*value == stack->max || *value == stack->min)
			ft_find_min_max(stack->array, stack->size, &stack->min,
							&stack->max);
		stack->top = stack->size - 1;
	}
	else
		return (1);
	if (stack->max_size / 3 > stack->size)
		if (update_stack(stack, stack->max_size / 2 + 1))
			return (-1);
	return (0);
}

t_stack		*create_stack(int *array, int size)
{
	t_stack	*stack;
	int		i;

	if (!(stack = malloc(sizeof(t_stack))))
		return (NULL);
	stack->max_size = size * 2 + 1;
	stack->size = 0;
	if (!(stack->array = malloc(sizeof(int) * stack->max_size)))
	{
		free(stack);
		return (NULL);
	}
	if (array && !(i = 0))
	{
		while (i < size)
		{
			stack->array[i] = array[i];
			i++;
		}
		stack->size = size;
		ft_find_min_max(stack->array, stack->size, &stack->min, &stack->max);
	}
	stack->top = stack->size - 1;
	return (stack);
}
