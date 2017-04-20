/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:54:37 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/19 23:50:25 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATION_H
# define OPERATION_H
# include "libft.h"

int		execute(const char *op, t_stack *a, t_stack *b);
int		do_swap(t_stack *stack);
int		do_push(t_stack *x, t_stack *y);
int		do_rotate(t_stack *stack, int d);

#endif
