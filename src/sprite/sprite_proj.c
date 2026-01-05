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

static void	transform_to_camera(t_game *game, t_vec2 rel, t_proj *proj)
{
	t_vec2	dir;
	t_vec2	plane;
	t_f32	inv_det;

	dir = game->camera.dir;
	plane = game->camera.plane;
	inv_det = 1.0f / (plane.x * dir.y - dir.x * plane.y);
	proj->trans.x = inv_det * (dir.y * rel.x - dir.x * rel.y);
	proj->trans.y = inv_det * (-plane.y * rel.x + plane.x * rel.y);
}

static void	calc_screen_pos(t_game *game, t_f32 scale, t_proj *proj)
{
	t_i32	pitch_offset;

	pitch_offset = (t_i32)(game->camera.pitch * game->render.height);
	proj->screen.x = (t_i32)((game->render.width / 2)
			* (1.0f + proj->trans.x / proj->trans.y));
	proj->screen.y = game->render.height / 2 + pitch_offset;
	proj->size.y = absi((t_i32)(game->render.height / proj->trans.y * scale));
	proj->size.x = absi((t_i32)(game->render.width / proj->trans.y * scale));
}

static void	calc_draw_bounds(t_game *game, t_proj *proj)
{
	proj->start.x = proj->screen.x - proj->size.x / 2;
	proj->start.y = proj->screen.y - proj->size.y / 2;
	proj->end.x = proj->screen.x + proj->size.x / 2;
	proj->end.y = proj->screen.y + proj->size.y / 2;
	proj->start.x = maxi(proj->start.x, 0);
	proj->start.y = maxi(proj->start.y, 0);
	proj->end.x = mini(proj->end.x, game->render.width - 1);
	proj->end.y = mini(proj->end.y, game->render.height - 1);
}

bool	sprite_project(t_game *game, t_entity *ent, t_proj *proj)
{
	t_vec2	rel;

	rel = vec2_sub(ent->pos, game->camera.pos);
	transform_to_camera(game, rel, proj);
	if (proj->trans.y <= EPSILON)
		return (false);
	proj->dist = proj->trans.y;
	proj->tex_id = ent->tex_id;
	calc_screen_pos(game, ent->scale, proj);
	calc_draw_bounds(game, proj);
	if (proj->end.x < 0 || proj->start.x >= game->render.width)
		return (false);
	return (true);
}
