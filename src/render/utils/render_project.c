/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_project.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_i32	project_wall_height(t_f32 dist, t_i32 screen_h)
{
	if (dist < EPSILON)
		return (screen_h);
	return ((t_i32)(screen_h / dist));
}

t_i32	project_screen_x(t_f32 trans_x, t_f32 trans_y, t_i32 screen_w)
{
	if (trans_y < EPSILON)
		return (screen_w / 2);
	return ((t_i32)((screen_w / 2) * (1.0f + trans_x / trans_y)));
}

t_i32	project_z_offset(t_f32 z_offset, t_f32 dist, t_i32 screen_h)
{
	if (dist < EPSILON)
		return (0);
	return ((t_i32)(z_offset * screen_h / dist));
}

t_vec2i	project_sprite_size(t_f32 scale, t_f32 dist, t_i32 w, t_i32 h)
{
	t_vec2i	size;
	t_f32	factor;

	if (dist < EPSILON)
		factor = scale;
	else
		factor = scale / dist;
	size.x = absi((t_i32)(w * factor));
	size.y = absi((t_i32)(h * factor));
	return (size);
}

t_i32	project_apply_pitch(t_i32 y, t_f32 pitch, t_i32 screen_h)
{
	return (y + (t_i32)(pitch * screen_h));
}
