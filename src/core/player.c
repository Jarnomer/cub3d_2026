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

#include <cub3d.h>

static void	player_rotate(t_game *game, t_f32 dt)
{
	t_f32	rot_speed;

	rot_speed = PLAYER_LOOK_SPEED * dt;
	if (input_key_down(&game->input, MLX_KEY_LEFT))
		game->camera.angle -= rot_speed;
	if (input_key_down(&game->input, MLX_KEY_RIGHT))
		game->camera.angle += rot_speed;
	game->camera.angle = angle_normalize(game->camera.angle);
	camera_update(&game->camera);
}

static t_vec2	get_move_input(t_game *game)
{
	t_vec2	input;

	input = vec2_zero();
	if (input_key_down(&game->input, MLX_KEY_W))
		input.y += 1.0f;
	if (input_key_down(&game->input, MLX_KEY_S))
		input.y -= 1.0f;
	if (input_key_down(&game->input, MLX_KEY_A))
		input.x -= 1.0f;
	if (input_key_down(&game->input, MLX_KEY_D))
		input.x += 1.0f;
	return (input);
}

static void	player_move(t_game *game, t_f32 dt)
{
	t_vec2	input;
	t_vec2	move;
	t_vec2	forward;
	t_vec2	right;

	input = get_move_input(game);
	if (input.x == 0.0f && input.y == 0.0f)
		return ;
	forward = game->camera.dir;
	right = vec2_perp(forward);
	move = vec2_zero();
	move = vec2_add(move, vec2_mul(forward, input.y));
	move = vec2_add(move, vec2_mul(right, input.x));
	move = vec2_normalize(move);
	move = vec2_mul(move, PLAYER_SPEED * dt);
	game->camera.pos = vec2_add(game->camera.pos, move);
}

void	player_update(t_game *game, t_f32 dt)
{
	player_rotate(game, dt);
	player_move(game, dt);
}
