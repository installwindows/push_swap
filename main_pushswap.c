/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pushswap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:30:13 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 20:56:28 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	cleanup(t_flag *f)
{
	if (f)
	{
		free_stack(f->a);
		free_stack(f->b);
		free_stack(f->stack);
		if (f->flags)
			free(f->flags);
		if (f->fdout > 1)
			close(f->fdout);
		free(f);
	}
	return (1);
}

static void	set_flag(t_flag *f)
{
	int		i;
	char	c;

	i = 0;
	while ((c = f->flagorder[i]))
	{
		if (c == 'o')
			f->flag |= FLAG_O;
		else if (c == 'n')
			f->flag |= FLAG_N;
		else if (c == 'd')
			f->flag |= FLAG_D;
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_flag	*flag;

	if (argc == 1)
		return (0);
	if (!(flag = parse_argument(argc, argv, "nod")))
	{
		ft_fprintf(2, "Error\n");
		return (1);
	}
	set_flag(flag);
	pushswap(flag->a, flag);
	cleanup(flag);
}
