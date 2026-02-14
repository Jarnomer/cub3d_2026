/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_health.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	player_take_damage(t_player *player, t_i32 amount)
{
	t_i32	absorb;

	if (!player->is_alive || amount <= 0)
		return ;
	if (player->armor > 0)
	{
		absorb = mini(player->armor, amount / 2);
		player->armor -= absorb;
		amount -= absorb;
	}
	player->health -= amount;
	if (player->health <= 0)
	{
		player->health = 0;
		player->is_alive = false;
	}
}

void	player_add_health(t_player *player, t_i32 amount)
{
	if (!player->is_alive || amount <= 0)
		return ;
	player->health += amount;
	if (player->health > PLAYER_MAX_HEALTH)
		player->health = PLAYER_MAX_HEALTH;
}

void	player_add_armor(t_player *player, t_i32 amount)
{
	if (!player->is_alive || amount <= 0)
		return ;
	player->armor += amount;
	if (player->armor > PLAYER_MAX_ARMOR)
		player->armor = PLAYER_MAX_ARMOR;
}
