/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:04:36 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/24 15:40:34 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int		print_stack(t_stack *a, t_stack *b, const char *c,
													const char *op)
{
	int		i;

	i = 0;
	ft_printf("-------------top-------------\n");
	while (i < a->size && i < b->size)
	{
		ft_printf("% 11d  --- %-13d%s%-s%s\n", a->array[a->size - i - 1],
			b->array[b->size - i - 1], c,
			(i == GTR(a->size, b->size) / 2) ? op : "", "\e[0m\e[39m");
		i++;
	}
	while (i < a->size)
	{
		ft_printf("% 11d  ---%s%14s%-s%s\n", a->array[a->size - i - 1], c, "",
			(i == GTR(a->size, b->size) / 2) ? op : "", "\e[0m\e[39m");
		i++;
	}
	while (i < b->size)
	{
		ft_printf("             --- %-13d%s%-s%s\n", b->array[b->size - i - 1],
			c, (i == GTR(a->size, b->size) / 2) ? op : "", "\e[0m\e[39m");
		i++;
	}
	ft_printf("------------bottom-----------\n");
	return (0);
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
		ft_printf(flag->flag & FLAG_C ? "\e[1m\e[92mOK\e[0m\e[39m\n" : "OK\n");
	else
		ft_printf(flag->flag & FLAG_C ? "\e[1m\e[91mKO\e[0m\e[39m\n" : "KO\n");
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
		print_stack(a, b, flag->flag & FLAG_C ? "\e[1m\e[91m" : "", "");
	lst = NULL;
	cur = &lst;
	while ((r = gnl(fd, &line)))
	{
		if (r == -1)
			return (!cleanup(lst));
		if (flag->flag & FLAG_V)
		{
			if ((r = execute(line, a, b)))
				print_stack(a, b, flag->flag & FLAG_C ? "\e[31m" : "", "Error");
			else
				print_stack(a, b, flag->flag & FLAG_C ? "\e[32m" : "", line);
		}
		else if (add_op(&cur, line))
			return (!cleanup(lst));
	}
	return (eval_operation(lst, a, b, flag));
}
