/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pushswap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:30:13 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/21 00:53:06 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int		main(int argc, char **argv)
{
	int		*array;
	t_stack	*a;
	t_flag	flag;

	if (argc == 1)
		return (0);
	if (!(array = parse_number(++argv, argc - 1)) ||
		check_doublon(array, argc - 1))
	{
		ft_fprintf(2, "Error\n");
		return (1);
	}
	if (!(a = create_stack(array, argc - 1)))
		return (1);
	if (a->size <= 1)
		return (0);
	flag.sorted_array = sort(array, argc - 1);
	flag.size = argc - 1;
	if (pushswap(a, &flag))
		return (1);
	free_stack(a);
	free(array);
}
