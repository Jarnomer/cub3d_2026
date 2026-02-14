/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
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
	t_vec2i	dst;

	dst.x = (t_i32)pos.x;
	dst.y = (t_i32)pos.y;
	if (map_is_wall(map, dst.x, dst.y))
		return (false);
	if (map_is_wall(map, (t_i32)(pos.x + PLAYER_RADIUS), dst.y))
		return (false);
	if (map_is_wall(map, (t_i32)(pos.x - PLAYER_RADIUS), dst.y))
		return (false);
	if (map_is_wall(map, dst.x, (t_i32)(pos.y + PLAYER_RADIUS)))
		return (false);
	if (map_is_wall(map, dst.x, (t_i32)(pos.y - PLAYER_RADIUS)))
		return (false);
	return (true);
}

static void	apply_movement(t_camera *cam, t_map *map, t_vec2 move)
{
	t_vec2	dst;

	dst = vec2_new(cam->pos.x + move.x, cam->pos.y);
	if (is_valid_pos(map, dst))
		cam->pos.x = dst.x;
	dst = vec2_new(cam->pos.x, cam->pos.y + move.y);
	if (is_valid_pos(map, dst))
		cam->pos.y = dst.y;
}

static t_vec2	get_target_velocity(t_game *game)
{
	t_vec2	input;
	t_vec2	dir;
	t_f32	speed;

	input = vec2_zero();
	if (input_key_down(&game->input, MLX_KEY_W))
		input.y += MOVE_MAGNITUDE;
	if (input_key_down(&game->input, MLX_KEY_S))
		input.y -= MOVE_MAGNITUDE;
	if (input_key_down(&game->input, MLX_KEY_A))
		input.x -= MOVE_MAGNITUDE;
	if (input_key_down(&game->input, MLX_KEY_D))
		input.x += MOVE_MAGNITUDE;
	if (input.x == 0.0f && input.y == 0.0f)
		return (vec2_zero());
	dir = vec2_add(vec2_mul(game->camera.dir, input.y),
			vec2_mul(vec2_perp(game->camera.dir), input.x));
	speed = crouch_get_mult(&game->player.motion);
	speed *= sprint_get_mult(&game->player.motion);
	return (vec2_mul(vec2_normalize(dir), speed * PLAYER_SPEED));
}

void	player_move(t_game *game, t_f32 dt)
{
	t_motion	*motion;
	t_vec2		target;
	t_vec2		move;

	motion = &game->player.motion;
	target = get_target_velocity(game);
	if (vec2_len(target) > 0.0f)
		move_apply_acceleration(motion, target, dt);
	else
		move_apply_friction(motion, dt);
	move = vec2_mul(motion->velocity, dt);
	apply_movement(&game->camera, game->map, move);
}
