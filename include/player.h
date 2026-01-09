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

typedef struct s_player_player
{
	t_i32		health;
	t_i32		armor;
	t_i32		ammo[AMMO_COUNT];
	t_weapon	weapon;
	t_u32		kills;
	t_u32		secrets;
	bool		alive;
}	t_player;

void	player_init(t_player *player, t_game *game);

void	player_take_damage(t_player *player, t_i32 amount);
void	player_add_health(t_player *player, t_i32 amount);
void	player_add_armor(t_player *player, t_i32 amount);

bool	player_use_ammo(t_player *player, t_ammo type, t_i32 amount);
void	player_add_ammo(t_player *player, t_ammo type, t_i32 amount);
t_i32	player_get_ammo(t_player *player, t_ammo type);
t_i32	player_max_ammo(t_ammo type);

#endif
