/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

bool	hitscan_dda(t_vec2 from, t_vec2 to, t_game *game)
{
	t_ray	ray;
	t_vec2	dir;
	t_f32	dist;
	t_hit	hit;

	dir = vec2_sub(to, from);
	dist = vec2_len(dir);
	if (dist < EPSILON)
		return (true);
	dir = vec2_normalize(dir);
	ray_init(&ray, from, dir);
	hit = perform_dda(&ray, game, dist);
	if (!hit.hit)
		return (true);
	if (hit.dist >= dist - EPSILON)
		return (true);
	return (false);
}

void	ray_step(t_ray *ray, int *axis)
{
	if (ray->dist.x < ray->dist.y)
	{
		ray->dist.x += ray->delta.x;
		ray->grid.x += ray->step.x;
		*axis = AXIS_X;
	}
	else
	{
		ray->dist.y += ray->delta.y;
		ray->grid.y += ray->step.y;
		*axis = AXIS_Y;
	}
}
