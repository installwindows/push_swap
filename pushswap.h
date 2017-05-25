/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:40:09 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/24 22:45:06 by varnaud          ###   ########.fr       */
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
# define FLAG_D 4
# define HEAD(a, n) a->array[a->size - 1 - n]
# define TAIL(a, n) a->array[n]

int		pushswap(t_stack *a, t_flag *flag);
void	sort_3(t_stack *s, t_oplst **cur, char c);
void	sort_rev_3(t_stack *b, t_oplst ***cur);
void	sort_5(t_stack *a, t_oplst **lst, t_flag *f);
void	sort_x(t_stack *a, t_oplst **lst, t_flag *f);
void	sort_alot(t_stack *a, t_oplst **cur, t_flag *f);
int		do_op(t_stack *a, t_stack *b, t_oplst ***cur, const char *op);
void	find_min_max(t_stack *s, int *min, int *max);
void	set_max_maxx(t_stack *a, t_flag *f, int *maxx, int *pmax);

#endif
