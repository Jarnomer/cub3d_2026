/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	init_ammo(t_pstats *stats)
{
	stats->ammo[AMMO_SHELL] = AMMO_START_SHELL;
	stats->ammo[AMMO_BULLET] = AMMO_START_BULLET;
	stats->ammo[AMMO_CELL] = AMMO_START_CELL;
	stats->ammo[AMMO_EXPLOSIVE] = AMMO_START_EXPLOSIVE;
}

void	pstats_init(t_pstats *stats, t_game *game)
{
	ft_bzero(stats, sizeof(t_pstats));
	stats->health = PLAYER_START_HEALTH;
	stats->armor = PLAYER_START_ARMOR;
	stats->alive = true;
	init_ammo(stats);
	weapon_init(&stats->weapon, WEAPON_SHOTGUN, game);
}

void	pstats_damage(t_pstats *stats, t_i32 amount)
{
	t_i32	armor_absorb;

	if (!stats->alive || amount <= 0)
		return ;
	if (stats->armor > 0)
	{
		armor_absorb = mini(stats->armor, amount / 2);
		stats->armor -= armor_absorb;
		amount -= armor_absorb;
	}
	stats->health -= amount;
	if (stats->health <= 0)
	{
		stats->health = 0;
		stats->alive = false;
	}
}

void	pstats_heal(t_pstats *stats, t_i32 amount)
{
	if (!stats->alive || amount <= 0)
		return ;
	stats->health += amount;
	if (stats->health > PLAYER_MAX_HEALTH)
		stats->health = PLAYER_MAX_HEALTH;
}

void	pstats_add_armor(t_pstats *stats, t_i32 amount)
{
	if (amount <= 0)
		return ;
	stats->armor += amount;
	if (stats->armor > PLAYER_MAX_ARMOR)
		stats->armor = PLAYER_MAX_ARMOR;
}
