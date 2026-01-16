/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_proj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/15 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_i32	proj_calc_z_shift(t_render *render, t_proj *proj)
{
	t_f32	scale;

	if (proj->trans.y < EPSILON)
		return (0);
	scale = render->height / proj->trans.y;
	return ((t_i32)(proj->trans.z * scale));
}

static t_vec2i	proj_calc_screen(t_game *game, t_render *render, t_camera *cam,
	t_proj *proj)
{
	t_vec2i	screen;
	t_i32	shift;
	t_i32	offset;
	t_f32	ratio;

	if (proj->trans.y < EPSILON)
		ratio = 0.5f;
	else
		ratio = 1.0f + proj->trans.x / proj->trans.y;
	screen.x = (t_i32)((render->width / 2) * ratio);
	screen.y = render->height / 2;
	screen.y += (t_i32)(cam->pitch * render->height);
	shift = proj_calc_z_shift(render, proj);
	offset = camera_sprite_offset(game, proj->trans.y);
	screen.y = screen.y - shift + offset;
	return (screen);
}

static t_vec2i	proj_calc_size(t_render *render, t_entity *ent, t_proj *proj)
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

static void	init_sprite_ctx(t_entity *ent, t_proj *proj, t_vec3 *world,
	t_vec2 *plane)
{
	proj->pos = vec3_new(world->x, world->y, world->z);
	proj->trans = vec3_new(plane->x, plane->y, world->z);
	proj->dist = plane->y;
	proj->tex_id = ent->spr_id;
	proj->use_sheet = ent->use_sheet;
	proj->sheet_id = ent->sheet_id;
	proj->frame = 0;
}

bool	sprite_project(t_game *game, t_entity *ent, t_proj *proj)
{
	t_vec3	world;
	t_vec2	plane;

	world = vec3_new(ent->pos.x, ent->pos.y, ent->pos.z);
	plane = trans_world_to_cam(&game->camera, vec2_from_vec3(world));
	if (trans_behind_camera(plane.y))
		return (false);
	init_sprite_ctx(ent, proj, &world, &plane);
	proj->screen = proj_calc_screen(game, &game->render, &game->camera, proj);
	proj->size = proj_calc_size(&game->render, ent, proj);
	proj->bounds = rect_centered(proj->screen, proj->size);
	rect_clip(&proj->bounds, game->render.width, game->render.height);
	return (!rect_is_offscreen(proj->bounds));
}
