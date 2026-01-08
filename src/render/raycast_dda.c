/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_dir	get_dir(t_ray *ray, int axis)
{
	if (axis == AXIS_X)
	{
		if (ray->step.x > 0)
			return (WALL_WEST);
		return (WALL_EAST);
	}
	if (ray->step.y > 0)
		return (WALL_SOUTH);
	return (WALL_NORTH);
}

static t_f32	calc_wall_x(t_ray *ray, t_f32 dist, int axis)
{
	t_f32	wall_x;

	if (axis == AXIS_X)
		wall_x = ray->origin.y + dist * ray->dir.y;
	else
		wall_x = ray->origin.x + dist * ray->dir.x;
	return (wall_x - floorf(wall_x));
}

static t_f32	calc_dist(t_ray *ray, int axis)
{
	t_f32	dist;

	if (axis == AXIS_X)
		dist = ray->dist.x - ray->delta.x;
	else
		dist = ray->dist.y - ray->delta.y;
	return (maxf(dist, EPSILON));
}

static void	fill_hit_result(t_hit *hit, t_ray *ray, int axis)
{
	hit->axis = axis;
	hit->dist = calc_dist(ray, axis);
	hit->wall_x = calc_wall_x(ray, hit->dist, axis);
	hit->dir = get_dir(ray, axis);
	hit->grid = ray->grid;
}

t_hit	perform_dda(t_ray *ray, t_game *game, t_f32 max_dist)
{
	t_cell	cell_type;
	t_i32	ent_idx;
	int		axis;
	t_hit	hit;

	hit = (t_hit){.ent_idx = CELL_EMPTY};
	axis = 0;
	while (!hit.hit)
	{
		ray_step(ray, &axis);
		cell_type = cellgrid_check_cell(game, ray->grid, &ent_idx);
		if (cell_type != CELLTYPE_EMPTY)
		{
			hit.hit = true;
			hit.cell = (t_u8)cell_type;
			hit.ent_idx = ent_idx;
		}
		if (calc_dist(ray, axis) > max_dist)
			break ;
	}
	fill_hit_result(&hit, ray, axis);
	return (hit);
}
