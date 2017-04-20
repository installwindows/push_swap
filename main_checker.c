/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:52:54 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/19 22:01:24 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stack.h"
#include "checker.h"

static int	ft_natoi(char *s, int *n)
{
	int		sign;

	if (s == NULL)
		return (1);
	*n = 0;
	sign = 0;
	if (*s == '-')
		sign = *s++;
	while (*s)
	{
		if (!(*s == '0' || *s == '1' || *s == '2' || *s == '3' || *s == '4' ||
			*s == '5' || *s == '6' || *s == '7' || *s == '8' || *s == '9'))
			return (1);
		if (*n && ((!sign && (long)*n * 10 + (*s - '0') > 2147483647) ||
					(sign && (long)*n * 10 + (*s - '0') > 2147483648L)))
			return (1);
		*n = *n * 10 + (*s - '0');
		s++;
	}
	if (sign && *n)
		*n *= -1;
	return (0);
}

static int	*parse_number(char **numbers, int size)
{
	int		*array;
	int		n;

	if (size < 1 || numbers == NULL)
		return (NULL);
	array = malloc(sizeof(int) * size);
	if (array == NULL)
		return (NULL);
	while (size)
	{
		if (ft_natoi(*numbers, &n))
		{
			free(array);
			return (NULL);
		}
		array[--size] = n;
		numbers++;
	}
	return (array);
}

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
		!(numbers = parse_number(argv, argc - 1)))
	{
		ft_fprintf(2, "Error\n");
		return (1);
	}
	if (!(a = create_stack(numbers, argc - 1)))
	{
		free(numbers);
		return (1);
	}
	if (!(b = create_stack(NULL, argc - 1)))
		return (1);
	//for (int i = 0; i < argc - 1; i++)
	//	ft_printf("%d\n", numbers[i]);
	//ft_printf("flag: %d\n", flag);
	//exit(0);
	if (checker(a, b, flag))
		return (1);
	free(numbers);
	free_stack(a);
	free_stack(b);
}
