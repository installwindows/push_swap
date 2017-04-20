/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 21:39:16 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/19 23:56:00 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# include "stack.h"
# include "operation.h"
# define FLAG_V 1
# define FLAG_C 2
# define FLAG_DEBUG 4
# define IS_DIGIT(a) (a == '0' || a == '1' || a == '2' || a == '3' || a == '4' \
					|| a == '5' || a == '6' || a == '7' || a == '8' || a == '9')

typedef struct		s_oplst
{
	char			*op;
	struct s_oplst	*next;
}					t_oplst;

int					checker(t_stack *a, t_stack *b, int fd, int flag);

#endif
