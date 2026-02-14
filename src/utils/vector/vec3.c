/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_vec3	vec3_new(t_f32 x, t_f32 y, t_f32 z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	vec3_zero(void)
{
	return ((t_vec3){0.0f, 0.0f, 0.0f});
}

t_vec3	vec3_from_vec2(t_vec2 v, t_f32 z)
{
	return ((t_vec3){v.x, v.y, z});
}
