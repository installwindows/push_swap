/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:52:54 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/21 20:25:43 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

int			main(int argc, char **argv)
{
	int		*numbers;
	t_flag	flag;
	t_stack	*a;
	t_stack	*b;
	int		fd;

	ft_memset(&flag, 0, sizeof(t_flag));
	if (parse_option(&argv, &argc, &flag) ||
		!(numbers = parse_number(argv, argc - 1)) ||
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
}
