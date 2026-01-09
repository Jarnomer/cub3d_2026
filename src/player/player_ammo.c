/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_ammo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_i32	player_max_ammo(t_ammo type)
{
	if (type == AMMO_SHELL)
		return (AMMO_MAX_SHELL);
	if (type == AMMO_BULLET)
		return (AMMO_MAX_BULLET);
	if (type == AMMO_CELL)
		return (AMMO_MAX_CELL);
	if (type == AMMO_EXP)
		return (AMMO_MAX_EXP);
	return (0);
}

t_i32	player_get_ammo(t_player *player, t_ammo type)
{
	if (type < 0 || type >= AMMO_COUNT)
		return (0);
	return (player->ammo[type]);
}

void	player_add_ammo(t_player *player, t_ammo type, t_i32 amount)
{
	t_i32	max;

	if (type < 0 || type >= AMMO_COUNT || amount <= 0)
		return ;
	max = player_max_ammo(type);
	player->ammo[type] += amount;
	if (player->ammo[type] > max)
		player->ammo[type] = max;
}

bool	player_use_ammo(t_player *player, t_ammo type, t_i32 amount)
{
	if (type < 0 || type >= AMMO_COUNT)
		return (false);
	if (player->ammo[type] < amount)
		return (false);
	player->ammo[type] -= amount;
	return (true);
}
