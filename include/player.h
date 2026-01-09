/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <weapon.h>
# include <types.h>
# include <defs.h>

typedef struct s_game	t_game;

typedef struct s_player_stats
{
	t_i32		health;
	t_i32		armor;
	t_i32		ammo[AMMO_COUNT];
	t_weapon	weapon;
	t_u32		kills;
	t_u32		secrets;
	bool		alive;
}	t_pstats;

void	pstats_init(t_pstats *stats, t_game *game);

void	pstats_damage(t_pstats *stats, t_i32 amount);
void	pstats_heal(t_pstats *stats, t_i32 amount);
void	pstats_add_armor(t_pstats *stats, t_i32 amount);

bool	pstats_use_ammo(t_pstats *stats, t_ammo type, t_i32 amount);
void	pstats_add_ammo(t_pstats *stats, t_ammo type, t_i32 amount);
t_i32	pstats_get_ammo(t_pstats *stats, t_ammo type);
t_i32	pstats_max_ammo(t_ammo type);

#endif
