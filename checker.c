/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:52:54 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/19 18:09:38 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stack.h"

int		ft_natoi(char *s, int *n)
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

int		*parse_number(char **numbers, int size)
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

int		main(int argc, char **argv)
{
	int		*numbers;
	t_stack	*a;
	t_stack	*b;
	int		value;

	if (argc < 2 ||	!(numbers = parse_number(++argv, argc - 1)))
	{
		ft_fprintf(2, "Error\n");
		return (1);
	}
	a = create_stack(numbers, argc - 1);
	b = create_stack(NULL, argc - 1);
	while (!pop(a, &value))
	{
		printf("%d\n", value);
	}
	free(numbers);
	free_stack(a);
	free_stack(b);
}
