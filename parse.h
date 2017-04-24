/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 22:34:03 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/23 22:38:12 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "stack.h"
# include "utils.h"

t_flag	*parse_argument(int argc, char **argv, const char *flags);
t_stack	*parse_number(char **argv, t_flag *f, int i);

#endif
