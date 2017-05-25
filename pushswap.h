/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:40:09 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/25 01:10:28 by varnaud          ###   ########.fr       */
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

typedef struct	s_s
{
	int			f;
	int			num;
	int			step_a;
	int			step_b;
	int			total;
	int			dir_a;
	int			dir_b;
	int			ra;
	int			rra;
	int			rb;
	int			rrb;
	int			rr;
	int			rrr;
}				t_s;

int				pushswap(t_stack *a, t_flag *flag);
void			sort_3(t_stack *s, t_oplst **cur, char c);
void			sort_rev_3(t_stack *b, t_oplst ***cur);
void			sort_5(t_stack *a, t_oplst **lst, t_flag *f);
void			sort_4(t_stack *a, t_oplst **lst);
void			sort_x(t_stack *a, t_oplst **lst, t_flag *f);
void			sort_alot(t_stack *a, t_oplst **cur, t_flag *f);
int				do_op(t_stack *a, t_stack *b, t_oplst ***cur, const char *op);
void			find_min_max(t_stack *s, int *min, int *max);
void			set_max_maxx(t_stack *a, t_flag *f, int *maxx, int *pmax);
void			calculate_b(t_s *n, t_stack *b);
void			calculate_total(t_s *n, t_stack *a, t_stack *b);

#endif
