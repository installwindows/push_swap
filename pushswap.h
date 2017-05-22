/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:40:09 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 18:23:11 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft.h"
# include "utils.h"
# include "stack.h"
# include "operation.h"
# include "parse.h"
# define FLAG_O 1
# define FLAG_N 2
# define FLAG_D 3
# define HEAD(a, n) a->array[a->size - 1 - n]
# define TAIL(a, n) a->array[n]

int		pushswap(t_stack *a, t_flag *flag);
void 	sort_5(t_stack *a, t_oplst **lst, t_flag *f);
void	sort_x(t_stack *a, t_oplst **lst, t_flag *f);
int		do_op(t_stack *a, t_stack *b, t_oplst ***cur, const char *op);
void	find_min_max(t_stack *s, int *min, int *max);

#endif
