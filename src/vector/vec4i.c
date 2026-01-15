/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_vec4i	vec4i_new(t_i32 x, t_i32 y, t_i32 w, t_i32 h)
{
	return ((t_vec4i){x, y, w, h});
}

bool	vec4i_contains(t_vec4i v, t_i32 x, t_i32 y)
{
	if (x < v.x || x >= v.x + v.w)
		return (false);
	if (y < v.y || y >= v.y + v.h)
		return (false);
	return (true);
}
