/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_emit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_vec3	calc_reflect_dir(t_vec2 shot_dir, t_hit *hit)
{
	t_vec3	dir;

	if (hit->axis == AXIS_X)
		dir = vec3_new(-shot_dir.x, shot_dir.y, 0.0f);
	else
		dir = vec3_new(shot_dir.x, -shot_dir.y, 0.0f);
	return (dir);
}

static t_vec3	calc_impact_pos(t_hit *hit)
{
	t_vec3	pos;

	pos.z = hit->z_offset;
	if (hit->dir == WALL_NORTH || hit->dir == WALL_SOUTH)
		pos.x = (t_f32)hit->grid.x + hit->wall_x;
	else
		pos.y = (t_f32)hit->grid.y + hit->wall_x;
	if (hit->dir == WALL_NORTH)
		pos.y = (t_f32)hit->grid.y + 1.0f - PARTICLE_WALL_OFFSET;
	else if (hit->dir == WALL_SOUTH)
		pos.y = (t_f32)hit->grid.y + PARTICLE_WALL_OFFSET;
	else if (hit->dir == WALL_EAST)
		pos.x = (t_f32)hit->grid.x + 1.0f - PARTICLE_WALL_OFFSET;
	else
		pos.x = (t_f32)hit->grid.x + PARTICLE_WALL_OFFSET;
	return (pos);
}

static void	emit_particles(t_game *game, t_surfdef *def, t_hit *hit)
{
	t_vec3	pos;
	t_vec3	dir;
	t_i32	count;
	t_i32	i;

	pos = calc_impact_pos(hit);
	dir = calc_reflect_dir(game->camera.dir, hit);
	count = rangei_random(def->count);
	i = 0;
	while (i < count)
	{
		particle_spawn(&game->particles, def->particle, pos, dir);
		i++;
	}
}

void	particle_emit_impact(t_game *game, t_hit *hit)
{
	t_surfdef	*def;

	if (!hit->hit)
		return ;
	def = surface_get_def(&game->particles, hit);
	if (!def || def->particle <= PARTICLE_NONE)
		return ;
	emit_particles(game, def, hit);
}
