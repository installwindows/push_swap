/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:50:55 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/23 22:12:36 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_s
{
	int			f;
	int			num;
	int			step_a;
	int			step_b;
	int			total;
	int			dir_a;
	int			dir_b;
	int			ra;
	int			rra;
	int			rb;
	int			rrb;
	int			rr;
	int			rrr;
}				t_s;

void	calculate_b(t_s *n, t_stack *b)
{
	int		up;
	int		down;
	int		i;
	int		j;

	up = -2147483648;
	down = 2147483647;
	i = b->size;
	if (b->num > b->max)
	{
	}
	else if (b->num < b->min)
	{
	}
	else
	{
		while (--i >= 0)
		{
			if (b->array[i] > n->num && b->array[i] < down)
			{
				down = b->array[i];
				j = i;
			}
			else if (b->array[i] < n->num && b->array[i] > up)
			{
				up = b->array[i];
				j = i;
			}
		}
	}

}

void	calculate_total(t_s *tmp);
{
}

void	find_next(t_stack *a, t_stack *b, t_s *n)
{
	t_s		tmp;
	int		i;

	n->total = 2147483647;
	i = a->size;
	while (--i >= 0)
	{
		ft_memset(&tmp, 0, sizeof(t_s));
		tmp.num = a->array[i];
		tmp.step_a = a->size - i - 1;
		if (tmp.step_a > a->size / 2)
		{
			tmp.step_a = ft_abs(tmp.step_a - a->size);
			dir_a = 1;
		}
		calculate_b(&tmp, b);
		calculate_total(&tmp);
		if (tmp.total < n->total)
			ft_memcpy(n, &tmp, sizeof(t_s));
	}
}

void	sort_it(t_stack *a, t_stack *b, t_oplst ***cur)
{
	t_s		n;

	find_next(a, b, &n);
}

int		not_relatively_sorted(t_stack *a)
{
	int		i;

	i = a->size;
	while (--i >= 1)
	{
		if (a->array[i] == a->max && a->array[i - 1] == f->min)
			continue ;
		if (a->array[i] > a->array[i - 1])
			return (1);
	}
	return (0);
}

void	align_a_and_b(t_stack *a, t_stack *b, t_oplst ***cur)
{
	int		step_a;
	int		step_b;


}

void	align_a(t_stack *a)
{
	int		step;
}

void	sort_alot(t_stack *a, t_oplst **cur, t_flag *f)
{
	t_stack	*b;
	t_s		*n;

	b = create_stack(NULL, a->size);
	do_op(a, b, &cur, "pb");
	do_op(a, b, &cur, "pb");
	do_op(a, b, &cur, "pb");
	//sort_3(b, cur, 'b');
	//revvvv
	while ((*cur))
		cur = &(*cur)->next;
	while (a->size /*not_relatively_sorted(a)*/)
		sort_it(a, b, &cur);
	align_a_and_b(a, b, &cur);
	while (b->size)
		do_op(a, b, &cur, "pa");
	align_a(a);
	free_stack(b);
}
