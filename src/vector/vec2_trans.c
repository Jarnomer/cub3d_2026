/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_trans.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_f32	vec2_len(t_vec2 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}

t_vec2	vec2_normalize(t_vec2 v)
{
	t_f32	len;

	len = vec2_len(v);
	if (len < EPSILON)
		return (vec2_zero());
	return (vec2_div(v, len));
}

t_vec2	vec2_perp(t_vec2 v)
{
	return ((t_vec2){-v.y, v.x});
}
