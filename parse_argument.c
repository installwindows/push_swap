/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 23:13:58 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/24 00:19:17 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void		*cleanup(t_flag *f)
{
	if (f)
	{
		free(f->flags);
		if (f->fdin > 1)
			close(f->fdin);
		if (f->fdout > 1)
			close(f->fdout);
		free(f);
	}
	return (NULL);
}

static int		set_fd(t_flag *f)
{
	if (f->input && (f->fdin = open(f->input, O_RDONLY)) == -1)
		return (1);
	if (f->output && (f->fdout =
					open(f->input, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		return (1);
	return (0);
}

static int		set_file(char **argv, t_flag *f, int argc, int *i)
{
	int		j;
	int		k;

	j = 0;
	k = *i;
	while (argv[*i][j++])
		if (argv[*i][j] == 'i')
		{
			if (k == argc - 1)
				return (1);
			f->input = argv[++k];
		}
		else if (argv[*i][j] == 'o')
		{
			if (k == argc - 1)
				return (1);
			f->output = argv[++k];
		}
		else if (argv[*i][j] == 'n')
		{
			if (k == argc - 1)
				return (1);
			f->numfile = argv[++k];
		}
	return (!(*i = k));
}

static int		set_flag(char *a, t_flag *f)
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

t_flag			*parse_argument(int argc, char **argv, const char *flags)
{
	t_flag	*f;
	int		i;

	if (!(f = ft_memalloc(sizeof(t_flag) + ft_strlen(flags))))
		return (NULL);
	if (!(f->flags = ft_strdup(flags)))
		return (NULL);
	i = 0;
	while (++i < argc)
		if (argv[i][0] == '-')
		{
			if (ft_isdigit(argv[i][1]))
				break ;
			if (set_flag(argv[i], f) || set_file(argv, f, argc, &i))
				return (cleanup(f));
		}
		else
			break ;
	if (!(f->stack = parse_number(argv, f, i)) || set_fd(f))
		return (cleanup(f));
	return (f);
}
