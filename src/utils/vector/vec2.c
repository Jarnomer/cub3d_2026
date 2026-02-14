/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_vec2	vec2_new(t_f32 x, t_f32 y)
{
	return ((t_vec2){x, y});
}

t_vec2	vec2_zero(void)
{
	return ((t_vec2){0.0f, 0.0f});
}

t_vec2	vec2_from_angle(t_f32 angle)
{
	return ((t_vec2){cosf(angle), sinf(angle)});
}

t_vec2	vec2_from_vec3(t_vec3 v)
{
	return ((t_vec2){v.x, v.y});
}
