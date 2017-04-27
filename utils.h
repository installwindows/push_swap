/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:35:04 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/26 15:24:44 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "libft.h"
# include "stack.h"

typedef struct		s_oplst
{
	char			*op;
	struct s_oplst	*next;
}					t_oplst;

typedef struct		s_flag
{
	t_stack			*a;
	t_stack			*b;
	t_stack			*stack;
	int				min;
	int				max;
	int				med;
	int				flag;
	char			*flags;
	char			*input;
	char			*output;
	char			*numfile;
	int				fdin;
	int				fdout;
	int				fdnum;
	char			flagorder[1];
}					t_flag;

int					ft_natoi(char *s, int *n);
int					check_doublon(int *a, int size);
int					array_cmp(int *a, int sizea, int *s, int sizes);
int					*sort(int *a, int size);
int					*revarr(int *a, int size);
int					smallest(int *a, int size);
int					biggest(int *a, int size);

#endif
