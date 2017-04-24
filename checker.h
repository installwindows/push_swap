/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 21:39:16 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/23 22:37:34 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# include "stack.h"
# include "utils.h"
# include "parse.h"
# include "operation.h"
# define FLAG_V 1
# define FLAG_C 2
# define FLAG_I 4
# define FLAG_O 8
# define FLAG_N 16
# define GTR(a, b) ((a > b) ? a : b)

int					checker(t_stack *a, t_stack *b, int fd, t_flag *flag);

#endif
