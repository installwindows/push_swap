/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 21:27:19 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 22:10:07 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void		*cleanup(char **split, int i, t_stack *stack, char *line)
{
	if (split)
	{
		while (split[i])
			free(split[i++]);
		free(split);
	}
	if (stack)
	{
		if (stack->array)
			free(stack->array);
		free(stack);
	}
	free(line);
	gnl(-42, NULL);
	return (NULL);
}

static t_stack	*parse_numfile(t_flag *f, char *line)
{
	t_stack *stack;
	char	**num;
	int		i;
	int		n;

	if (((f->fdnum = open(f->numfile, O_RDONLY)) == -1) ||
		!(stack = create_stack(NULL, 1024)))
		return (NULL);
	while ((n = gnl(f->fdnum, &line)) && n != -1)
	{
		num = ft_split(line, ft_strlen(line), NULL);
		if (num && !(i = 0))
		{
			while (num[i])
			{
				if (ft_natoi(num[i], &n) || push(stack, n))
					return (cleanup(num, i, stack, line));
				free(num[i++]);
			}
			free(num);
		}
		free(line);
	}
	close(f->fdnum);
	return (stack);
}

static t_stack	*parse_numarg(char **argv, int i)
{
	t_stack	*stack;
	int		n;

	if (argv[i] == NULL)
		return (NULL);
	if (!(stack = create_stack(NULL, 1024)))
		return (NULL);
	while (argv[i])
	{
		if (argv[i][0] == '\0')
			return (cleanup(NULL, 0, stack, NULL));
		if (ft_natoi(argv[i], &n) || push(stack, n))
			return (cleanup(NULL, 0, stack, NULL));
		i++;
	}
	return (stack);
}

t_stack			*parse_number(char **argv, t_flag *f, int i)
{
	t_stack	*stack;

	if (f->numfile)
	{
		if (argv[i] != NULL)
			return (NULL);
		if (!(stack = parse_numfile(f, NULL)))
			return (NULL);
	}
	else
	{
		if (!(stack = parse_numarg(argv, i)))
			return (NULL);
	}
	if (stack->size == 0)
		return (cleanup(NULL, 0, stack, NULL));
	if (check_doublon(stack->array, stack->size))
		return (cleanup(NULL, 0, stack, NULL));
	if (!(f->a = create_stack(revarr(stack->array, stack->size), stack->size)))
		return (cleanup(NULL, 0, stack, NULL));
	if (!(f->b = create_stack(NULL, stack->size)))
		return (cleanup(NULL, 0, stack, NULL));
	stack->array = sort(stack->array, stack->size);
	return (stack);
}
