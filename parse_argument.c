/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 23:13:58 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/23 00:50:29 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int		set_fd(t_flag *f)
{
	if (f->input && (f->fdin = open(f->input, O_RDONLY)) == -1)
		return (1);
	if (f->output && (f->fdout =
					open(f->input, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		return (1);
}

static void		*cleanup(char **split, int i, t_stack *stack, char *line)
{
	if (split)
	{
		while (i)
			free(split[i--]);
		free(split);
	}
	if (stack)
		free(stack);
	if (line)
		free(line);
	return (NULL);
}

static t_stack	*parse_numfile(t_flag *f)
{
	t_stack *stack;
	char	**num;
	char	*line;
	int		i;
	int		n;

	if ((f->fdnum = open(f->numfile, O_RDONLY)) == -1)
		return (NULL);
	if ((stack = create_stack(NULL, 1024)))
		return (NULL);
	while ((r = gnl(f->fdnum, &line)) && r != -1)
	{
		num = ft_split(line, ft_strlen(line), NULL);
		i = 0;
		if (num)
		{
			while (num[i])
			{
				if (ft_natoi(num, &n) || push(stack, n))
					return (cleanup(num, i, stack, line));
				free(num[i++]);
			}
			free(num);
		}
		free(line);
	}
	return (stack);
}

static t_stack	*parse_number(char **argv, t_flag *f, int ac)
{
	t_stack	*stack;
	char	**num;
	char	*line;
	int		i;
	int		n;

	if (f->numfile)
	{
		if ((stack = parse_numfile(f)))
			return (NULL);
	}
	else
	{
		if ((stack = parse_numarg(f, argv, ac)))
			return (NULL);
	}
	stack->array = ft_re
	if (size < 1 || numbers == NULL)
		return (NULL);
	array = malloc(sizeof(int) * size);
	if (array == NULL)
		return (NULL);
	while (size)
	{
		if (ft_natoi(*numbers, &n))
		{
			free(array);
			return (NULL);
		}
		array[--size] = n;
		numbers++;
	}
	return (array);
}

static int		set_file(char **argv, t_flag *f, int argc, int *i)
{
	int		j;

	j = 0;
	while (argv[*i][j++])
	{
		if (argv[*i][j] == 'i')
		{
			if (*i == argc - 1)
				return (1);
			f->input = argv[++(*i)];
		}
		else if (argv[*i][j] == 'o')
		{
			if (*i == argc - 1)
				return (1);
			f->output = argv[++(*i)];
		}
		else if (argv[*i][j] == 'n')
		{
			if (*i == argc - 1)
				return (1);
			f->numfile = argv[++(*i)];
		}
	}
	return (0);
}

static int		set_flag(char *av, t_flag *f)
{
	if (*(a + 1) == '\0')
		return (1);
	while (*++a)
		if (!ft_strchr(f->flagorder, *a) && ft_strchr(f->flags, *a))
			ft_strncat(f->flagorder, a, 1);
		else
			return (1);
	return (0);
}

t_flag			*parse_argument(int ac, char **av, char *flags)
{
	t_flag	*f;
	int		i;

	if ((f = ft_memalloc(sizeof(t_flag) + ft_strlen(flags))))
		return (NULL);
	f->flags = flags;
	i = 0;
	while (++i < ac)
	{
		if (argv[i] == '-')
		{
			if (set_flag(argv[i], f) || set_file(argv, f, argc, &i))
				return (cleanup(f));
		}
		else
			break ;
	}
	if (set_fd(f))
		return (cleanup(f));
	if (parse_number(argv, f, i))
		return (cleanup(f));
	return (f);
}
