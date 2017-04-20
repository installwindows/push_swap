/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:04:36 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/19 23:58:33 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	print_stack(t_stack *a, t_stack *b)
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
}

static void	check_stack(t_stack *a, int flag)
{
	int		i;
	int		max;

	max = 2147483647;
	i = 0;
	while (i < a->size)
	{
		if (a->array[i] <= max)
			max = a->array[i];
		else
			break ;
		i++;
	}
	if (i == a->size)
		ft_printf(flag & FLAG_C ? "\e[1m\e[92mOK\e[0m\e[39m\n" : "OK");
	else
		ft_printf(flag & FLAG_C ? "\e[1m\e[91mKO\e[0m\e[39m\n" : "KO");
}

int			checker(t_stack *a, t_stack *b, int fd, int flag)
{
	int		r;
	char	*line;
	t_oplst	*lst;
	t_oplst	**cur;

	lst = NULL;
	cur = &lst;
	if (flag & FLAG_V)
		print_stack(a, b);
	while ((r = gnl(fd, &line)))
	{
		if (r == -1)
			return (-1);
		if (flag & FLAG_V)
		{
			if ((r = execute(line, a, b)))
				return (r);
			print_stack(a, b);
		}
		else
		{
			if (!(*cur = malloc(sizeof(t_oplst))))
				return (-1);
			(*cur)->op = line;
			(*cur)->next = NULL;
			cur = &(*cur)->next;
		}
	}
	cur = &lst;
	while (*cur)
	{
		if (flag & FLAG_DEBUG)
			ft_printf("DEBUG: %s\n", (*cur)->op);
		if ((r = execute((*cur)->op, a, b)))
			return (r);
		cur = &(*cur)->next;
	}
	gnl(-42, NULL);
	check_stack(a, flag);
	return (0);
}
