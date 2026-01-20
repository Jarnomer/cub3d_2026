/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_vec2	apply_spread(t_vec2 dir, t_f32 spread)
{
	t_f32	angle;
	t_f32	offset;

	if (spread <= 0.0f)
		return (dir);
	offset = (rand_float() - 0.5f) * spread;
	angle = atan2f(dir.y, dir.x) + offset;
	return (vec2_from_angle(angle));
}

static void	fire_pellet(t_game *game, t_wpndef *def)
{
	t_ray	ray;
	t_hit	hit;
	t_vec2	dir;

	dir = apply_spread(game->camera.dir, def->spread);
	ray_init(&ray, game->camera.pos, dir);
	hit = perform_dda(&ray, game, def->range);
	if (!hit.hit)
		return ;
	if (hit.entity != INVALID_ID)
		entity_damage(game, hit.entity, def->damage);
	particle_emit_impact(game, &hit);
}

void	weapon_fire_pellets(t_game *game, t_wpndef *def)
{
	t_i32	i;

	i = 0;
	while (i < def->pellets)
	{
		fire_pellet(game, def);
		i++;
	}
}

t_vec2	sprint_get_offset(t_sway *sway, t_bob *bob)
{
	t_vec2	offset;
	t_f32	thrust;

	offset.x = 0.0f;
	offset.y = sway->sprint * SPRINT_DROP_Y;
	offset.y += sway->sprint * SPRINT_TILT_Y;
	if (SPRINT_THRUST_MULT <= 0.0f)
		thrust = 0.0f;
	else
		thrust = (1.0f - absf(sinf(bob->phase))) * SPRINT_THRUST_AMP;
	offset.y += thrust * sway->sprint * SPRINT_THRUST_MULT;
	return (offset);
}
