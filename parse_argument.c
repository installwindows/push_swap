/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 23:13:58 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/22 01:12:45 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	set_fd(t_flag *f)
{
}

static int	parse_number(char **argv, t_flag *f, int i)
{

}

static int	set_file(char **argv, t_flag *f, int argc, int *i)
{
	int		j;

	j = 0;
	while (argv[*i][j++])
	{
		if (argv[*i][j] == 'i')
		{
			if (i == argc - 1)
				return (1);
			f->input = argv[++(*i)];
		}
		else if (argv[*i][j] == 'o')
		{
			if (i == argc - 1)
				return (1);
			f->output = argv[++(*i)];
		}
	}
	return (0);
}

static int	set_flag(char *av, t_flag *f)
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

t_flag		*parse_argument(int ac, char **av, char *flags)
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
