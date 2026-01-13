/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_f32	camera_floor_offset(t_game *game, t_i32 y)
{
	t_f32	pos;
	t_i32	offset;
	t_i32	horizon;
	t_i32	width;

	pos = camera_get_height(game);
	offset = (t_i32)(game->camera.pitch * game->render.height);
	horizon = game->render.height / 2 + offset;
	width = y - horizon;
	if (width == 0)
		width = 1;
	if (width > 0)
		return ((1.0f - pos) * game->render.height / (t_f32)width);
	return (pos * game->render.height / (t_f32)(-width));
}

t_i32	camera_wall_offset(t_game *game, t_f32 dist)
{
	t_f32	pos;
	t_f32	offset;
	t_f32	height;

	pos = camera_get_height(game);
	offset = CAMERA_HEIGHT - pos;
	if (dist < EPSILON)
		return (0);
	height = (t_f32)game->render.height / dist;
	return ((t_i32)(offset * height));
}

t_i32	camera_sprite_offset(t_game *game, t_f32 dist)
{
	return (camera_wall_offset(game, dist));
}

t_f32	camera_get_height(t_game *game)
{
	return (crouch_height(&game->player.motion) + CAMERA_HEIGHT);
}
