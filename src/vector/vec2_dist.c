/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_f32	vec2_dist_sq(t_vec2 a, t_vec2 b)
{
	return (vec2_len_sq(vec2_sub(b, a)));
}

t_f32	vec2_dist(t_vec2 a, t_vec2 b)
{
	return (sqrtf(vec2_dist_sq(a, b)));
}

t_f32	vec2_angle(t_vec2 v)
{
	return (atan2f(v.y, v.x));
}

t_f32	vec2_angle_to(t_vec2 from, t_vec2 to)
{
	return (vec2_angle(vec2_sub(to, from)));
}
