/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 21:39:16 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/21 16:19:11 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# include "stack.h"
# include "utils.h"
# include "operation.h"
# define FLAG_V 1
# define FLAG_C 2
# define FLAG_DEBUG 4
# define GTR(a, b) ((a > b) ? a : b)

int					checker(t_stack *a, t_stack *b, int fd, t_flag *flag);

#endif
