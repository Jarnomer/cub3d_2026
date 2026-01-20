/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	camera_init(t_game *game, t_f32 fov)
{
	game->camera = (t_camera){.fov = fov * DEG2RAD};
	game->camera.angle = game->map->angle;
	game->camera.pos = game->map->position;
	game->camera.dir.x = cosf(game->camera.angle);
	game->camera.dir.y = sinf(game->camera.angle);
	camera_update(game);
}

void	camera_update(t_game *game)
{
	t_f32	fov;
	t_f32	plane;

	fov = deg_to_rad(game->player.motion.fov.current);
	plane = tanf(fov * CAMERA_HEIGHT);
	game->camera.dir.x = cosf(game->camera.angle);
	game->camera.dir.y = sinf(game->camera.angle);
	game->camera.plane = vec2_mul(vec2_perp(game->camera.dir), plane);
}
