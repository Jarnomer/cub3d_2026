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
	t_vec2	dir;
	t_hit	hit;

	dir = apply_spread(game->camera.dir, def->spread);
	ray_init(&ray, game->camera.pos, dir);
	hit = perform_dda(&ray, game, def->range);
	if (hit.hit && hit.entity != INVALID_ID)
		entity_damage(game, hit.entity, def->damage);
}

void	weapon_fire_all_pellets(t_game *game, t_wpndef *def)
{
	t_i32	i;

	i = 0;
	while (i < def->pellets)
	{
		fire_pellet(game, def);
		i++;
	}
}
