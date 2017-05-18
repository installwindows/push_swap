/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 20:28:55 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/17 21:29:39 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct		s_num
{
	int				n;
	int				p;
	struct s_num	*next;
	struct s_num	*prev;
}					t_num;

typedef struct		s_stack
{
	int				size;
	t_num			*head;
	t_num			*tail;
	t_num			*list;
}					t_stack;

t_num	*new_t_num(int *input, int s_input, int *sorted, int s_sorted)
{
	t_num	*lst;
	t_num	**cur;
	t_num	*prev;
	int		i;
	int		j;

	lst = NULL;
	prev = NULL;
	cur = &lst;
	i = 0;
	while (i < s_input)
	{
		(*cur) = malloc(sizeof(t_num));
		(*cur)->next = NULL;
		(*cur)->prev = prev;
		(*cur)->n = input[i];
		j = 0;
		while (sorted[j] != input[i] && j < s_sorted)
			j++;
		(*cur)->p = j;
		prev = (*cur);
		cur = &(*cur)->next;
		i++;
	}
	return (lst);
}


