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

t_i32	pstats_max_ammo(t_ammo type)
{
	if (type == AMMO_SHELL)
		return (AMMO_MAX_SHELL);
	if (type == AMMO_BULLET)
		return (AMMO_MAX_BULLET);
	if (type == AMMO_CELL)
		return (AMMO_MAX_CELL);
	if (type == AMMO_EXPLOSIVE)
		return (AMMO_MAX_EXPLOSIVE);
	return (0);
}

t_i32	pstats_get_ammo(t_pstats *stats, t_ammo type)
{
	if (type < 0 || type >= AMMO_COUNT)
		return (0);
	return (stats->ammo[type]);
}

void	pstats_add_ammo(t_pstats *stats, t_ammo type, t_i32 amount)
{
	t_i32	max;

	if (type < 0 || type >= AMMO_COUNT || amount <= 0)
		return ;
	max = pstats_max_ammo(type);
	stats->ammo[type] += amount;
	if (stats->ammo[type] > max)
		stats->ammo[type] = max;
}

bool	pstats_use_ammo(t_pstats *stats, t_ammo type, t_i32 amount)
{
	if (type < 0 || type >= AMMO_COUNT)
		return (false);
	if (stats->ammo[type] < amount)
		return (false);
	stats->ammo[type] -= amount;
	return (true);
}
