/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:35:04 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/21 23:45:44 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "libft.h"

typedef struct		s_oplst
{
	char			*op;
	struct s_oplst	*next;
}					t_oplst;

typedef struct		s_flag
{
	int				*array;
	int				*sorted_array;
	int				size;
	int				min;
	int				max;
	int				flag;
	char			*flags;
	char			*filename;
	char			*input;
	char			*output;
	int				fdin;
	int				fdout;
	char			flagorder[1];
}					t_flag;

int					ft_natoi(char *s, int *n);
int					*parse_number(char **numbers, int size);
int					check_doublon(int *a, int size);
int					is_sort(int *a, int sizea, int *s, int sizes);
int					*sort(int *a, int size);

#endif
