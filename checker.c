/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:04:36 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/20 01:53:13 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int		print_stack(t_stack *a, t_stack *b)
{
	int		i;

	i = 0;
	ft_printf("-------------top-------------\n");
	while (i < a->size && i < b->size)
	{
		ft_printf("% 11d  --- %d\n", a->array[a->size - i - 1],
										b->array[b->size - i - 1]);
		i++;
	}
	while (i < a->size)
	{
		ft_printf("% 11d  ---\n", a->array[a->size - i - 1]);
		i++;
	}
	while (i < b->size)
	{
		ft_printf("             --- %d\n", b->array[b->size - i - 1]);
		i++;
	}
	ft_printf("------------bottom-----------\n");
	return (0);
}

static void		check_stack(t_stack *a, int flag)
{
	if (is_sort(a->array, a->size))
		ft_printf(flag & FLAG_C ? "\e[1m\e[92mOK\e[0m\e[39m\n" : "OK\n");
	else
		ft_printf(flag & FLAG_C ? "\e[1m\e[91mKO\e[0m\e[39m\n" : "KO\n");
}

static int		eval_operation(t_oplst *cur, t_stack *a, t_stack *b, int flag)
{
	int		r;

	while (cur)
	{
		if (flag & FLAG_DEBUG)
			ft_printf("DEBUG: %s\n", cur->op);
		if ((r = execute(cur->op, a, b)))
			return (r);
		cur = cur->next;
	}
	gnl(-42, NULL);
	check_stack(a, flag);
	return (0);
}

static int		add_op(t_oplst ***cur, char *line)
{
	(**cur) = malloc(sizeof(t_oplst));
	if (!(**cur))
		return (-1);
	(**cur)->op = line;
	(**cur)->next = NULL;
	*cur = &(**cur)->next;
	return (0);
}

int				checker(t_stack *a, t_stack *b, int fd, int flag)
{
	int		r;
	char	*line;
	t_oplst	*lst;
	t_oplst	**cur;

	if (flag & FLAG_V && !(lst = NULL))
		print_stack(a, b);
	cur = &lst;
	while ((r = gnl(fd, &line)))
	{
		if (r == -1)
			return (-1);
		if (flag & FLAG_V)
		{
			if ((r = execute(line, a, b)))
				ft_printf("Invalid operation.\n");
			print_stack(a, b);
		}
		else if (add_op(&cur, line))
			return (-1);
	}
	return (eval_operation(lst, a, b, flag));
}
