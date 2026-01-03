/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

t_vec2i	vec2i_new(t_i32 x, t_i32 y)
{
	return ((t_vec2i){x, y});
}

t_vec2i	vec2i_from_vec2(t_vec2 v)
{
	return ((t_vec2i){(t_i32)v.x, (t_i32)v.y});
}

t_vec2	vec2_from_vec2i(t_vec2i v)
{
	return ((t_vec2){(t_f32)v.x, (t_f32)v.y});
}

bool	vec2i_eq(t_vec2i a, t_vec2i b)
{
	return (a.x == b.x && a.y == b.y);
}
