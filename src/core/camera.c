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

void	camera_init(t_camera *cam, t_vec2 pos, t_f32 angle, t_f32 fov)
{
	ft_bzero(cam, sizeof(t_camera));
	cam->pos = pos;
	cam->angle = angle;
	cam->fov = fov * DEG2RAD;
	cam->pitch = 0.0f;
	camera_update(cam);
}

void	camera_update(t_camera *cam)
{
	t_f32	plane_len;

	cam->dir = vec2_from_angle(cam->angle);
	plane_len = tanf(cam->fov / 2.0f);
	cam->plane = vec2_mul(vec2_perp(cam->dir), plane_len);
}
