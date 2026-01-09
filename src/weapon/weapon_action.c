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

static t_vec2	apply_spread(t_vec2 dir, t_f32 spread)
{
	t_f32	angle;
	t_f32	offset;

	if (spread <= 0.0f)
		return (dir);
	offset = ((t_f32)(rand() % 1000) / 1000.0f - 0.5f) * spread;
	angle = atan2f(dir.y, dir.x) + offset;
	return (vec2_from_angle(angle));
}

static void	fire_pellet(t_game *game, t_wpndef *def)
{
	t_ray	ray;
	t_vec2	dir;
	t_hit	hit;

	dir = apply_spread(game->camera.dir, def->spread);
	ray_init(&ray, game->camera.pos, dir);
	hit = perform_dda(&ray, game, def->range);
	if (hit.hit && hit.entity != ENTITY_VOID)
		entity_damage(game, hit.entity, def->damage);
}

static void	fire_all_pellets(t_game *game, t_wpndef *def)
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

	if (!weapon_can_fire(wpn, game))
		return ;
	def = weapon_get_def(game, wpn->id);
	player = &game->player;
	if (!player_use_ammo(player, def->ammo_type, 1))
		return ;
	weapon_set_state(wpn, STATE_FIRING, game);
	wpn->ready = false;
	wpn->fire_timer = def->fire_rate;
	wpn->recoil = minf(wpn->recoil + WEAPON_RECOIL_MAX, WEAPON_RECOIL_MAX);
	fire_all_pellets(game, def);
}

void	weapon_reload(t_weapon *wpn, t_game *game)
{
	if (!weapon_can_reload(wpn, game))
		return ;
	weapon_set_state(wpn, STATE_RELOADING, game);
	wpn->ready = false;
}
