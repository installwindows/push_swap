/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:23:55 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/19 16:03:19 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

#include <stdlib.h>

typedef struct	s_stack
{
	int			*array;
	int			max_size;
	int			size;
}				t_stack;

int				push(t_stack *stack, int value);
int				pop(t_stack *stack, int *value);
int				peek(t_stack *stack, int *value);
t_stack			*create_stack(int *array, int size);

#endif
