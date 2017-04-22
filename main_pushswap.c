/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pushswap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:30:13 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/22 01:12:52 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	set_flag(char *a, int *flag)
{
	if (*(a + 1) == '\0')
		return (1);
	while (*++a)
	{
		if (*a == 'f' && !(*flag & FLAG_F))
			*flag |= FLAG_F;
		else
			return (1);
	}
	return (0);
}

static int	parse_option(char **av, int ac, t_flag *flag, int *a)
{
	int		in;
	int		out;

	in = 0;
	out = 0;
	while (*++av)
	{
		if (**av == '-')
			if (set_flag(*av, flag->flag))
				return (1);
		if (!in && flag->flag & FLAG_I
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_stack	*a;
	t_flag	flag;

	ft_memset(&flag, 0, sizeof(t_flag));
	if (argc == 1)
		return (0);
	if (parse_option(argv, argc, &flag))
		return (ft_printf(2, "Error\n") ? 1 : 1);
	else if (!(flag.array = parse_number(++argv, argc - 1)))
		return (ft_fprintf(2, "Error\n") ? 1 : 1);
	flag.size = flag.size ? flag.size : argc - 1;
	if (check_doublon(flag.array, flag.size))
		return (ft_fprintf(2, "Error\n") ? 1 : 1);
	if (!(a = create_stack(flag.array, flag.size)))
		return (1);
	if (a->size <= 1)
		return (0);
	flag.sorted_array = sort(flag.array, flag.size);
	if (pushswap(a, &flag))
		return (1);
	free_stack(a);
	free(flag.array);
}
