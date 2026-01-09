/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_proj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_i32	proj_screen_x(t_proj *proj, t_render *render)
{
	float	screen_ratio;

	if (proj->trans.y < EPSILON)
		return (render->width / 2);
	screen_ratio = 1.0f + proj->trans.x / proj->trans.y;
	return ((t_i32)((render->width / 2) * screen_ratio));
}

t_i32	proj_z_offset(t_entity *ent, t_proj *proj, t_render *render)
{
	float	depth_scale;

	if (proj->trans.y < EPSILON)
		return (0);
	depth_scale = render->height / proj->trans.y;
	return ((t_i32)(ent->z_offset * depth_scale));
}

t_vec2i	proj_sprite_size(t_entity *ent, t_proj *proj, t_render *render)
{
	t_vec2i	size;
	t_f32	factor;

	if (proj->trans.y < EPSILON)
		factor = ent->scale;
	else
		factor = ent->scale / proj->trans.y;
	size.x = absi((t_i32)(render->width * factor));
	size.y = absi((t_i32)(render->height * factor));
	return (size);
}

t_i32	proj_apply_pitch(t_proj *proj, t_camera *cam, t_render *render)
{
	return (proj->screen.y + (t_i32)(cam->pitch * render->height));
}
