/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:52:54 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/24 15:27:52 by varnaud          ###   ########.fr       */
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
/*
static void	print_flag(t_flag *flag)
{
	int		i;

	ft_printf("flags: %s\n", flag->flagorder);
	ft_printf("flag: %b\n", flag->flag);
	ft_printf("input: %s\n", flag->input);
	ft_printf("output: %s\n", flag->output);
	ft_printf("numfile: %s\n", flag->numfile);
	ft_printf("stack:\n");
	ft_printf("size: %d\n", flag->stack->size);
	i = 0;
	while (i < flag->stack->size)
		ft_printf("%d ~ ", flag->stack->array[i++]);
	ft_printf("\na:\n");
	ft_printf("size: %d\n", flag->a->size);
	i = 0;
	while (i < flag->a->size)
		ft_printf("%d ~ ", flag->a->array[i++]);
	ft_printf("\n");
}
*/
int			main(int argc, char **argv)
{
	t_flag	*flag;

	if (!(flag = parse_argument(argc, argv, "vcion")))
	{
		ft_fprintf(2, "Error\n");
		return (1);
	}
	set_flag(flag);
	//print_flag(flag);
	//exit(0);
	checker(flag->a, flag->b, flag->fdin, flag);
	cleanup(flag);
	return (0);
}
