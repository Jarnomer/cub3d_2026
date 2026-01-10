/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	handle_inputs(t_game *game, t_f32 dt)
{
	t_f32	delta;

	delta = PLAYER_LOOK_SPEED * dt;
	if (input_key_down(&game->input, MLX_KEY_LEFT))
		game->camera.angle -= delta;
	if (input_key_down(&game->input, MLX_KEY_RIGHT))
		game->camera.angle += delta;
}

void	player_rotate(t_game *game, t_f32 dt)
{
	t_camera	*cam;
	t_f32		pitch;

	cam = &game->camera;
	handle_inputs(game, dt);
	cam->angle += game->input.mouse_delta.x * PLAYER_MOUSE_SENS;
	cam->pitch -= game->input.mouse_delta.y * PLAYER_MOUSE_SENS;
	cam->angle = angle_normalize(cam->angle);
	pitch = clampf(cam->pitch, -PLAYER_MAX_PITCH, PLAYER_MAX_PITCH);
	cam->pitch = pitch;
	camera_update(&game->camera);
}
