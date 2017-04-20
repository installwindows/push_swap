/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:52:54 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/20 01:34:52 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	set_flag(char *a, int *flag)
{
	if (*(a + 1) == '\0')
		return (1);
	while (*++a)
	{
		if (*a == 'v')
			*flag |= FLAG_V;
		else if (*a == 'c')
			*flag |= FLAG_C;
		else if (*a == 'd')
			*flag |= FLAG_DEBUG;
		else
			return (1);
	}
	return (0);
}

static int	parse_option(char ***av, int *ac, int *flag)
{
	while (*++(*av))
	{
		if (***av == '-')
		{
			if (ft_isdigit(*(**av + 1)))
				break ;
			if (set_flag(**av, flag))
				return (1);
			(*ac)--;
		}
		else
			break ;
	}
	return (0);
}

int			main(int argc, char **argv)
{
	int		*numbers;
	int		flag;
	t_stack	*a;
	t_stack	*b;

	flag = 0;
	if (parse_option(&argv, &argc, &flag) ||
		!(numbers = parse_number(argv, argc - 1)) ||
		check_doublon(numbers, argc - 1))
	{
		ft_fprintf(2, "Error\n");
		return (1);
	}
	if (!(a = create_stack(numbers, argc - 1)))
		return (1);
	if (!(b = create_stack(NULL, argc - 1)))
		return (1);
	if ((flag = checker(a, b, 0, flag)))
	{
		ft_fprintf(2, flag > 0 ? "Error\n" : "Something terrible happened\n");
		return (1);
	}
	free(numbers);
	free_stack(a);
	free_stack(b);
}
