/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:52:54 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 17:40:11 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	set_flag(t_flag *f)
{
	int		i;
	char	c;

	i = 0;
	while ((c = f->flagorder[i]))
	{
		if (c == 'v')
			f->flag |= FLAG_V;
		else if (c == 'c')
			f->flag |= FLAG_C;
		else if (c == 'i')
			f->flag |= FLAG_I;
		else if (c == 'o')
			f->flag |= FLAG_O;
		else if (c == 'n')
			f->flag |= FLAG_N;
		else if (c == 'd')
			f->flag |= FLAG_D;
		i++;
	}
}

static int	cleanup(t_flag *f)
{
	if (f)
	{
		free_stack(f->stack);
		free_stack(f->a);
		free_stack(f->b);
		if (f->flags)
			free(f->flags);
		if (f->fdin > 1)
			close(f->fdin);
		if (f->fdout > 1)
			close(f->fdout);
		free(f);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_flag	*flag;

	if (!(flag = parse_argument(argc, argv, "vciond")))
	{
		ft_fprintf(2, "Error\n");
		return (1);
	}
	set_flag(flag);
	if (checker(flag->a, flag->b, flag->fdin, flag))
		ft_fprintf(2, "Error\n");
	cleanup(flag);
	return (0);
}
