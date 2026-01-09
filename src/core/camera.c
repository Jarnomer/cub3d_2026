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

void	camera_init(t_camera *cam, t_map *map, t_f32 fov)
{
	*cam = (t_camera){0};
	cam->pos = map->spawn_pos;
	cam->angle = map->spawn_angle;
	cam->fov = fov * DEG2RAD;
	camera_update(cam);
}

void	camera_update(t_camera *cam)
{
	t_f32	plane_len;

	cam->dir = vec2_from_angle(cam->angle);
	plane_len = tanf(cam->fov / 2.0f);
	cam->plane = vec2_mul(vec2_perp(cam->dir), plane_len);
}
