/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:52:54 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/22 01:12:49 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	*cleanup(void *p)
{
	free(p);
	return (NULL);
}
/*
static int	set_flag(char *a, int *flag)
{
	if (*(a + 1) == '\0')
		return (1);
	while (*++a)
	{
		if (*a == 'v' && !(*flag & FLAG_V))
			*flag |= FLAG_V;
		else if (*a == 'c' && !(*flag & FLAG_C))
			*flag |= FLAG_C;
		else if (*a == 'f' && !(*flag & FLAG_F))
			*flag |= FLAG_F;
		else
			return (1);
	}
	return (0);
}

static int	parse_option(char ***av, int *ac, t_flag *flag)
{
	int		fileset;

	fileset = 0;
	while (*++(*av))
	{
		if (***av == '-')
		{
			if (ft_isdigit(*(**av + 1)))
				break ;
			if (set_flag(**av, &flag->flag))
				return (1);
			(*ac)--;
			if (!fileset && flag->flag & FLAG_F && (fileset = 1))
			{
				(*ac)--;
				flag->filename = *++(*av);
			}
		}
		else
			break ;
	}
	return (0);
}
*/
static int		set_file(char **argv, t_flag *f, int a, int *i)
{
	char	*in;
	char	*out;

	in = ft_strchr(f->flagorder, 'i');
	out = ft_strchr(f->flagorder, 'o');
	if ((!in && !out) || (f->input && f->output))
		return (0);
	if ((((in && !f->input && f->output) || (out && !f->input && f->input)) &&
		*i >= a - 2) || ((!f->input && !f->output && in && out && *i >= a - 3)))
		return (1);
	if (in && !f->input && ++(*i))
	{
		if ((out && out > in) || f->output || !out)
			f->input = argv[i];
		else if (out < in)
			f->input = argv[i + 1];
	}
	if (out && !f->output && ++(*i))
	{
		if ((in && in > out) || f->input || !in)
			f->output = argv[i];
		else if (in < out)
			f->output = argv[i + 1];
	}
	return (0);
}

static int		check_flag(char *a, const char *o, t_flag *f)
{
	if (*(a + 1) == '\0')
		return (1);
	while (*++a)
		if (!ft_strchr(f->flagorder, *a) && ft_strchr(o, *a))
			ft_strncat(f->flagorder, a, 1);
		else
			return (1);
	return (0);
}


static t_flag	*set_flag(int *argc, char **argv, const char *flags)
{
	t_flag	*f;
	char	*tmp;
	int		i;

	if ((f = ft_memalloc(sizeof(t_flag) + ft_strlen(flags))))
		return (NULL);
	i = 0;
	while (argv[i++])
	{
		if (argv[i] == '-')
		{
			if (check_flag(argv[i], flags, f) || set_file(argv, f, *argc, &i))
				return (cleanup(f));
		}
		else
			break ;
	}
	if (f->
	*argc = i;
	return (f);
}

int			main(int argc, char **argv)
{
	int		*numbers;
	t_flag	*flag;
	t_stack	*a;
	t_stack	*b;
	int		fd;

	flag = set_flag(&argc, argv, "iovc");
	if (flag == NULL)
	{
		ft_fprintf(2, "Error\n");
		return (1);
	}
	if (!(numbers = parse_number(argv, argc - 1)) ||
		check_doublon(numbers, argc - 1))
		return (ft_fprintf(2, "Error\n"));
	if (!(a = create_stack(numbers, argc - 1)))
		return (1);
	if (!(b = create_stack(NULL, argc - 1)))
		return (1);
	flag.size = argc - 1;
	flag.sorted_array = sort(numbers, argc - 1);
	if ((fd = flag.filename ? open(flag.filename, O_RDONLY) : 0) == -1)
		return (ft_fprintf(2, "Error: Cannot open %s\n", flag.filename));
	if ((flag.flag = checker(a, b, fd, &flag)))
		return (ft_fprintf(2, "Error\n"));
	close(fd);
	free(numbers);
	free_stack(a);
	free_stack(b);
	free(flag);
}
