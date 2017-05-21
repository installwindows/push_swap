/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 00:40:09 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/21 03:36:21 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft.h"
# include "utils.h"
# include "stack.h"
# include "operation.h"
# include "parse.h"
# define FLAG_O 1
# define FLAG_N 2
# define FLAG_D 3

int		pushswap(t_stack *a, t_flag *flag);

#endif
