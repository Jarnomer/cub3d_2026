/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_surface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/14 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_surfdef	*surface_get_def(t_emitter *emitter, t_surface type)
{
	if (type < 0 || type >= SURFACE_COUNT)
		return (&emitter->surfdefs[SURFACE_STONE]);
	return (&emitter->surfdefs[type]);
}

static t_surface	surface_from_entity(t_type entity_type)
{
	if (entity_type == ENTITY_DOOR)
		return (SURFACE_METAL);
	if (entity_type == ENTITY_BARREL)
		return (SURFACE_METAL);
	if (entity_type == ENTITY_ENEMY)
		return (SURFACE_FLESH);
	return (SURFACE_STONE);
}

static t_vec2	calc_hit_position(t_game *game, t_hit *hit)
{
	t_vec2	dir;

	dir = vec2_mul(game->camera.dir, hit->dist - PARTICLE_WALL_OFFSET);
	return (vec2_add(game->camera.pos, dir));
}

void	particle_emit_impact(t_game *game, t_hit *hit)
{
	t_surfdef	*def;
	t_vec2		pos;
	t_i32		count;

	if (!hit->hit)
		return ;
	def = surface_get_def(&game->emitter, SURFACE_STONE);
	if (!def || def->particle <= PARTICLE_NONE)
		return ;
	pos = calc_hit_position(game, hit);
	count = rand_rangei(def->count_min, def->count_max + 1);
	particle_spawn_all(&game->emitter, def->particle, pos, count);
}

void	particle_emit_entity(t_game *game, t_hit *hit, t_type type)
{
	t_surfdef	*def;
	t_surface	surface;
	t_vec2		pos;
	t_i32		count;

	if (!hit->hit)
		return ;
	surface = surface_from_entity(type);
	def = surface_get_def(&game->emitter, surface);
	if (!def || def->particle <= PARTICLE_NONE)
		return ;
	pos = calc_hit_position(game, hit);
	count = rand_rangei(def->count_min, def->count_max + 1);
	particle_spawn_all(&game->emitter, def->particle, pos, count);
}
