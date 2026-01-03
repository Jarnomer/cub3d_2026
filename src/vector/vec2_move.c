/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_vec2	vec2_lerp(t_vec2 a, t_vec2 b, t_f32 t)
{
	return ((t_vec2){lerpf(a.x, b.x, t), lerpf(a.y, b.y, t)});
}

t_vec2	vec2_clamp_len(t_vec2 v, t_f32 max_len)
{
	t_f32	len_sq;

	len_sq = vec2_len_sq(v);
	if (len_sq > max_len * max_len)
		return (vec2_mul(vec2_normalize(v), max_len));
	return (v);
}

t_vec2	vec2_move_toward(t_vec2 from, t_vec2 to, t_f32 max_dist)
{
	t_vec2	diff;
	t_f32	dist;

	diff = vec2_sub(to, from);
	dist = vec2_len(diff);
	if (dist <= max_dist || dist < EPSILON)
		return (to);
	return (vec2_add(from, vec2_mul(diff, max_dist / dist)));
}
