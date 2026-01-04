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

static bool	is_valid_pos(t_map *map, t_vec2 pos)
{
	t_i32	x;
	t_i32	y;

	x = (t_i32)pos.x;
	y = (t_i32)pos.y;
	if (map_is_wall(map, x, y))
		return (false);
	if (map_is_wall(map, (t_i32)(pos.x + PLAYER_RADIUS), y))
		return (false);
	if (map_is_wall(map, (t_i32)(pos.x - PLAYER_RADIUS), y))
		return (false);
	if (map_is_wall(map, x, (t_i32)(pos.y + PLAYER_RADIUS)))
		return (false);
	if (map_is_wall(map, x, (t_i32)(pos.y - PLAYER_RADIUS)))
		return (false);
	return (true);
}

static void	player_move(t_game *game, t_vec2 move)
{
	t_vec2	new_pos;

	new_pos = vec2_new(game->camera.pos.x + move.x, game->camera.pos.y);
	if (is_valid_pos(game->map, new_pos))
		game->camera.pos.x = new_pos.x;
	new_pos = vec2_new(game->camera.pos.x, game->camera.pos.y + move.y);
	if (is_valid_pos(game->map, new_pos))
		game->camera.pos.y = new_pos.y;
}

static t_vec2	get_move_input(t_game *game, t_f32 dt)
{
	t_vec2	input;
	t_vec2	move;

	input = vec2_zero();
	if (input_key_down(&game->input, MLX_KEY_W))
		input.y += 1.0f;
	if (input_key_down(&game->input, MLX_KEY_S))
		input.y -= 1.0f;
	if (input_key_down(&game->input, MLX_KEY_A))
		input.x -= 1.0f;
	if (input_key_down(&game->input, MLX_KEY_D))
		input.x += 1.0f;
	if (input.x == 0.0f && input.y == 0.0f)
		return (vec2_zero());
	move = vec2_add(vec2_mul(game->camera.dir, input.y),
			vec2_mul(vec2_perp(game->camera.dir), input.x));
	return (vec2_mul(vec2_normalize(move), PLAYER_SPEED * dt));
}

static void	player_rotate(t_game *game, t_f32 dt)
{
	t_f32	rot_speed;

	rot_speed = PLAYER_LOOK_SPEED * dt;
	if (input_key_down(&game->input, MLX_KEY_LEFT))
		game->camera.angle -= rot_speed;
	if (input_key_down(&game->input, MLX_KEY_RIGHT))
		game->camera.angle += rot_speed;
	game->camera.angle += game->input.mouse_delta.x * PLAYER_MOUSE_SENS;
	game->camera.pitch -= game->input.mouse_delta.y * PLAYER_MOUSE_SENS;
	game->camera.angle = angle_normalize(game->camera.angle);
	game->camera.pitch = clampf(game->camera.pitch, -PLAYER_MAX_PITCH,
			PLAYER_MAX_PITCH);
	camera_update(&game->camera);
}

void	player_update(t_game *game, t_f32 dt)
{
	player_rotate(game, dt);
	player_move(game, get_move_input(game, dt));
}
