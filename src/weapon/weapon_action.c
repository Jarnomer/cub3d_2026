/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_vec2	apply_spread(t_vec2 dir, t_f32 spread, t_f32 *z_off)
{
	t_f32	angle;
	t_f32	radius;

	*z_off = 0.0f;
	if (spread <= 0.0f)
		return (dir);
	angle = rand_float() * TAU;
	radius = rand_float() * spread;
	*z_off = sinf(angle) * radius * SPREAD_VERT_SCALE;
	angle = atan2f(dir.y, dir.x) + cosf(angle) * radius * SPREAD_HORIZ_SCALE;
	return (vec2_from_angle(angle));
}

static void	fire_pellet(t_game *game, t_wpndef *def)
{
	t_ray	ray;
	t_hit	hit;
	t_vec2	dir;
	t_f32	z_off;

	dir = apply_spread(game->camera.dir, def->spread, &z_off);
	ray_init(&ray, game->camera.pos, dir);
	hit = perform_dda(&ray, game, def->range);
	if (!hit.hit)
		return ;
	hit.z_offset = z_off;
	if (hit.entity != INVALID_ID)
		entity_damage(game, hit.entity, def->damage);
	particle_emit_impact(game, &hit);
	decal_spawn(game, &hit, def->ammo_type);
}

static void	weapon_fire_pellets(t_game *game, t_wpndef *def)
{
	t_i32	i;

	i = 0;
	while (i < def->pellets)
	{
		fire_pellet(game, def);
		i++;
	}
}

void	weapon_fire(t_weapon *wpn, t_game *game)
{
	t_wpndef	*def;
	t_player	*player;
	t_f32		recoil;

	if (!weapon_can_fire(wpn, game))
		return ;
	def = weapon_get_def(game, wpn->id);
	player = &game->player;
	if (!player_use_ammo(player, def->ammo_type, 1))
		return ;
	weapon_set_state(wpn, STATE_FIRING, game);
	recoil = wpn->recoil + WEAPON_RECOIL_MAX;
	wpn->recoil = minf(recoil, WEAPON_RECOIL_MAX);
	wpn->timer = def->fire_rate;
	wpn->ready = false;
	weapon_fire_pellets(game, def);
}

void	weapon_reload(t_weapon *wpn, t_game *game)
{
	if (!weapon_can_reload(wpn, game))
		return ;
	weapon_set_state(wpn, STATE_RELOADING, game);
	wpn->ready = false;
}
