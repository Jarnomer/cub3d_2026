/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decal_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/17 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_vec2i	decal_calc_screen(t_game *game, t_vec2 trans)
{
	t_vec2i	screen;
	t_i32	pitch;
	t_i32	offset;
	t_f32	ratio;

	if (trans.y < EPSILON)
		ratio = 0.5f;
	else
		ratio = 1.0f + trans.x / trans.y;
	screen.x = (t_i32)((game->render.width / 2) * ratio);
	screen.y = game->render.height / 2;
	pitch = (t_i32)(game->camera.pitch * game->render.height);
	offset = camera_wall_offset(game, trans.y);
	screen.y = screen.y + pitch + offset;
	return (screen);
}

static t_vec2i	decal_calc_size(t_game *game, t_decaldef *def, t_f32 dist)
{
	t_vec2i	size;
	t_f32	factor;

	if (dist < EPSILON)
		factor = def->scale;
	else
		factor = def->scale / dist;
	size.x = absi((t_i32)(game->render.height * factor));
	size.y = absi((t_i32)(game->render.height * factor));
	return (size);
}

static void	decal_init_proj(t_proj *proj, t_decal *decal, t_decaldef *def,
	t_vec2 trans)
{
	proj->pos = decal->pos;
	proj->trans = vec3_new(trans.x, trans.y, 0.0f);
	proj->dist = trans.y;
	proj->sheet_id = def->sheet_id;
	proj->frame = decal->frame;
	proj->use_sheet = true;
}

bool	decal_project(t_game *game, t_decal *decal, t_proj *proj)
{
	t_decaldef	*def;
	t_vec2		trans;
	t_f32		wall_h;

	def = decal_get_def(&game->decals, decal->type);
	if (!def)
		return (false);
	trans = trans_world_to_cam(&game->camera,
			vec2_new(decal->pos.x, decal->pos.y));
	if (trans_behind_camera(trans.y))
		return (false);
	decal_init_proj(proj, decal, def, trans);
	proj->screen = decal_calc_screen(game, trans);
	wall_h = (t_f32)game->render.height / maxf(trans.y, EPSILON);
	proj->screen.y -= (t_i32)(decal->pos.z * wall_h);
	proj->size = decal_calc_size(game, def, trans.y);
	proj->bounds = rect_centered(proj->screen, proj->size);
	rect_clip(&proj->bounds, game->render.width, game->render.height);
	return (!rect_is_offscreen(proj->bounds));
}

t_u32	decals_collect(t_game *game, t_proj *projs)
{
	t_decalmgr	*mgr;
	t_decal		*decal;
	t_u32		count;
	t_u32		i;

	mgr = &game->decals;
	count = 0;
	i = 0;
	while (i < mgr->pool.capacity && count < DEFAULT_POOL_SIZE)
	{
		if (!mgr->pool.active_flags[i])
		{
			i++;
			continue ;
		}
		decal = decal_get(mgr, i);
		if (decal && decal->is_active)
		{
			if (decal_project(game, decal, &projs[count]))
				count++;
		}
		i++;
	}
	return (count);
}
