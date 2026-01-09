/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_proj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	calc_sprite_bounds(t_proj *proj, t_render *render)
{
	proj->start.x = proj->screen.x - proj->size.x / 2;
	proj->start.y = proj->screen.y - proj->size.y / 2;
	proj->end.x = proj->screen.x + proj->size.x / 2;
	proj->end.y = proj->screen.y + proj->size.y / 2;
	proj->start.x = maxi(proj->start.x, 0);
	proj->start.y = maxi(proj->start.y, 0);
	proj->end.x = mini(proj->end.x, render->width - 1);
	proj->end.y = mini(proj->end.y, render->height - 1);
}

static void	calc_screen_pos(t_game *game, t_entity *ent, t_proj *proj)
{
	t_i32	z_shift;

	proj->screen.x = proj_screen_x(proj, &game->render);
	proj->screen.y = game->render.height / 2;
	proj->screen.y = proj_apply_pitch(proj, &game->camera, &game->render);
	z_shift = proj_z_offset(ent, proj, &game->render);
	proj->screen.y -= z_shift;
	proj->size = proj_sprite_size(ent, proj, &game->render);
}

static void	init_sprite_ent_ctx(t_entity *ent, t_proj *proj)
{
	proj->dist = proj->trans.y;
	proj->tex_id = ent->tex_id;
	proj->use_sheet = ent->use_sheet;
	proj->sheet_id = ent->sheet_id;
	proj->frame = 0;
}

bool	sprite_project(t_game *game, t_entity *ent, t_proj *proj)
{
	proj->trans = trans_world_to_cam(&game->camera, ent->pos);
	if (trans_behind_camera(proj->trans.y))
		return (false);
	init_sprite_ent_ctx(ent, proj);
	calc_screen_pos(game, ent, proj);
	calc_sprite_bounds(proj, &game->render);
	if (proj->end.x < 0 || proj->start.x >= game->render.width)
		return (false);
	return (true);
}
