/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:04:36 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 21:14:52 by varnaud          ###   ########.fr       */
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

static int		cleanup(t_oplst *lst, char *line)
{
	t_oplst	*cur;

	while (lst)
	{
		cur = lst->next;
		free(lst->op);
		free(lst);
		lst = cur;
	}
	free(line);
	gnl(-42, NULL);
	return (0);
}

static int		eval_operation(t_oplst *cur, t_stack *a, t_stack *b,
				t_flag *flag)
{
	t_oplst	*lst;

	lst = cur;
	while (cur)
	{
		execute(cur->op, a, b);
		cur = cur->next;
	}
	if (array_cmp(a->array, a->size, flag->stack->array, flag->stack->size))
		ft_fprintf(flag->fdout,
				flag->flag & FLAG_C ? "\e[1m\e[92mOK\e[0m\e[39m\n" : "OK\n");
	else
		ft_fprintf(flag->fdout,
				flag->flag & FLAG_C ? "\e[1m\e[91mKO\e[0m\e[39m\n" : "KO\n");
	cleanup(lst, NULL);
	if (flag->flag & FLAG_D)
		ft_printf("Length: %d\n", flag->length);
	return (0);
}

static int		add_op(t_oplst ***cur, char *line)
{
	(**cur) = malloc(sizeof(t_oplst));
	if (!(**cur))
		return (-1);
	(**cur)->op = ft_strdup(line);
	(**cur)->next = NULL;
	*cur = &(**cur)->next;
	return (ft_strcmp(line, "sa") && ft_strcmp(line, "sb") &&
			ft_strcmp(line, "ss") && ft_strcmp(line, "pa") &&
			ft_strcmp(line, "pb") && ft_strcmp(line, "ra") &&
			ft_strcmp(line, "rb") && ft_strcmp(line, "rr") &&
			ft_strcmp(line, "rra") && ft_strcmp(line, "rrb") &&
			ft_strcmp(line, "rrr"));
}

int				checker(t_stack *a, t_stack *b, int fd, t_flag *flag)
{
	int		r;
	char	*line;
	t_oplst	*lst;
	t_oplst	**cur;

	if (!(lst = NULL) && flag->flag & FLAG_V)
		print_stack(a, b, flag, "");
	cur = &lst;
	while ((r = gnl(fd, &line)))
	{
		if (r == -1)
			return (!cleanup(lst, line));
		if (flag->flag & FLAG_V)
		{
			if ((r = execute(line, a, b)))
				print_stack(a, b, flag, "Error");
			else if (++(flag->length) || 1)
				print_stack(a, b, flag, line);
		}
		else if (add_op(&cur, line) || (!++(flag->length)))
			return (!cleanup(lst, line));
		free(line);
	}
	return (eval_operation(lst, a, b, flag));
}
