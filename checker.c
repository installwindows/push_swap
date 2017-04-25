/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:04:36 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/24 22:37:44 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void		print_stack(t_stack *a, t_stack *b, t_flag *f, const char *op)
{
	int		i;
	char	c[42];

	ft_strcpy(c, f->flag & FLAG_C ? "\e[32m" : "");
	c[3] = f->flag & FLAG_C && *op == 'E' ? '1' : c[3];
	ft_strcat(c, op);
	ft_strcat(c, f->flag & FLAG_C ? "\e[0m\e[39m" : "");
	i = -1;
	ft_fprintf(f->fdout, "-------------top-------------\n");
	while (++i < a->size && i < b->size)
		ft_fprintf(f->fdout, "% 11d  --- %-13d%-s\n", a->array[a->size - i - 1],
		b->array[b->size - i - 1], (i == GTR(a->size, b->size) / 2) ? c : "");
	while (i < a->size)
	{
		ft_fprintf(f->fdout, "% 11d  ---%14s%-s\n", a->array[a->size - i - 1],
			"", (i == GTR(a->size, b->size) / 2) ? c : "");
		i++;
	}
	while (i < b->size)
	{
		ft_fprintf(f->fdout, "%13s--- %-13d%-s\n", "", b->array[b->size - i - 1]
			, (i == GTR(a->size, b->size) / 2) ? c : "");
		i++;
	}
	ft_fprintf(f->fdout, "------------bottom-----------\n");
}

static int		cleanup(t_oplst *lst)
{
	t_oplst	*cur;

	while (lst)
	{
		cur = lst->next;
		if (lst->op)
			free(lst->op);
		free(lst);
		lst = cur;
	}
	gnl(-42, NULL);
	return (0);
}

static void		check_stack(t_stack *a, t_flag *flag)
{
	if (is_sort(a->array, a->size, flag->stack->array, flag->stack->size))
		ft_fprintf(flag->fdout,
				flag->flag & FLAG_C ? "\e[1m\e[92mOK\e[0m\e[39m\n" : "OK\n");
	else
		ft_fprintf(flag->fdout,
				flag->flag & FLAG_C ? "\e[1m\e[91mKO\e[0m\e[39m\n" : "KO\n");
}

static int		eval_operation(t_oplst *cur, t_stack *a, t_stack *b,
				t_flag *flag)
{
	int		r;
	t_oplst	*lst;

	lst = cur;
	r = 0;
	while (cur)
	{
		if ((r = execute(cur->op, a, b)))
			break ;
		cur = cur->next;
	}
	if (!r)
		check_stack(a, flag);
	cleanup(lst);
	return (r);
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

int				checker(t_stack *a, t_stack *b, int fd, t_flag *flag)
{
	int		r;
	char	*line;
	t_oplst	*lst;
	t_oplst	**cur;

	if (flag->flag & FLAG_V && !(lst = NULL))
		print_stack(a, b, flag, "");
	lst = NULL;
	cur = &lst;
	while ((r = gnl(fd, &line)))
	{
		if (r == -1)
			return (!cleanup(lst));
		if (flag->flag & FLAG_V)
		{
			if ((r = execute(line, a, b)))
				print_stack(a, b,flag, "Error");
			else
				print_stack(a, b, flag, line);
		}
		else if (add_op(&cur, line))
			return (!cleanup(lst));
	}
	return (eval_operation(lst, a, b, flag));
}
