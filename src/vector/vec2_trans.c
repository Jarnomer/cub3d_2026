/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_trans.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

t_vec2	vec2_normalize(t_vec2 v)
{
	t_f32	len;

	len = vec2_len(v);
	if (len < EPSILON)
		return (vec2_zero());
	return (vec2_div(v, len));
}

t_vec2	vec2_rotate(t_vec2 v, t_f32 angle)
{
	t_f32	c;
	t_f32	s;

	c = cosf(angle);
	s = sinf(angle);
	return ((t_vec2){v.x * c - v.y * s, v.x * s + v.y * c});
}

t_vec2	vec2_perp(t_vec2 v)
{
	return ((t_vec2){-v.y, v.x});
}

t_vec2	vec2_perp_ccw(t_vec2 v)
{
	return ((t_vec2){v.y, -v.x});
}

t_vec2	vec2_reflect(t_vec2 v, t_vec2 normal)
{
	t_f32	dot;

	dot = vec2_dot(v, normal);
	return (vec2_sub(v, vec2_mul(normal, 2.0f * dot)));
}
