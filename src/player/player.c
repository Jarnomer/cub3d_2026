/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	init_player_ammo(t_player *player)
{
	player->ammo[AMMO_SHELL] = AMMO_START_SHELL;
	player->ammo[AMMO_BULLET] = AMMO_START_BULLET;
	player->ammo[AMMO_CELL] = AMMO_START_CELL;
	player->ammo[AMMO_EXPLOSIVE] = AMMO_START_EXPLOSIVE;
}

void	player_init(t_player *player, t_game *game)
{
	*player = (t_player){.alive = true};
	player->health = PLAYER_START_HEALTH;
	player->armor = PLAYER_START_ARMOR;
	init_player_ammo(player);
	weapon_init(&player->weapon, WEAPON_SHOTGUN, game);
	motion_init(&player->motion);
}

static void	handle_inputs(t_game *game)
{
	if (input_key_pressed(&game->input, KEY_INTERACT))
		player_interact(game);
	if (input_mouse_pressed(&game->input, KEY_MOUSE_FIRE))
		weapon_fire(&game->player.weapon, game);
	if (input_key_pressed(&game->input, KEY_RELOAD))
		weapon_reload(&game->player.weapon, game);
}

void	player_update(t_game *game, t_f32 dt)
{
	player_rotate(game, dt);
	player_move(game, dt);
	player_actions(game);
	handle_inputs(game);
}
