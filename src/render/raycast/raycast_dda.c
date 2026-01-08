/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/08 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_dir	get_wall_direction(t_ray *ray, int axis)
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

static t_f32	calc_wall_hit_x(t_ray *ray, t_f32 dist, int axis)
{
	t_f32	wall_x;

	if (axis == AXIS_X)
		wall_x = ray->origin.y + dist * ray->dir.y;
	else
		wall_x = ray->origin.x + dist * ray->dir.x;
	return (wall_x - floorf(wall_x));
}

t_f32	calc_dist(t_ray *ray, int axis)
{
	t_f32	dist;

	if (axis == AXIS_X)
		dist = ray->dist.x - ray->delta.x;
	else
		dist = ray->dist.y - ray->delta.y;
	return (maxf(dist, EPSILON));
}

static void	fill_hit(t_hit *hit, t_ray *ray, int axis)
{
	hit->axis = axis;
	hit->dist = calc_dist(ray, axis);
	hit->wall_x = calc_wall_hit_x(ray, hit->dist, axis);
	hit->dir = get_wall_direction(ray, axis);
	hit->grid = ray->grid;
}

t_hit	perform_dda(t_ray *ray, t_game *game, t_f32 max_dist)
{
	t_cell	cell;
	t_i32	entity;
	int		axis;
	t_hit	hit;

	hit = (t_hit){.entity = ENTITY_VOID};
	axis = 0;
	while (!hit.hit)
	{
		ray_step(ray, &axis);
		cell = grid_check_cell(game, ray->grid, &entity);
		if (cell == CELL_WALL)
			hit.hit = true;
		else if (cell == CELL_DOOR && grid_door_block(game, entity))
			hit.hit = true;
		if (hit.hit)
		{
			hit.cell = (t_u8)cell;
			hit.entity = entity;
		}
		if (calc_dist(ray, axis) > max_dist)
			break ;
	}
	fill_hit(&hit, ray, axis);
	return (hit);
}

static void	record_door_hit(t_hit *door_out, t_ray *ray, int axis, t_i32 entity)
{
	if (door_out->entity != ENTITY_VOID)
		return ;
	door_out->hit = true;
	door_out->cell = CELL_DOOR;
	door_out->entity = entity;
	fill_hit(door_out, ray, axis);
}

t_hit	passthr_dda(t_ray *ray, t_game *game, t_f32 max_dist, t_hit *door_out)
{
	t_cell	cell;
	t_i32	entity;
	int		axis;
	t_hit	hit;

	hit = (t_hit){.entity = ENTITY_VOID};
	*door_out = (t_hit){.entity = ENTITY_VOID};
	axis = 0;
	while (!hit.hit)
	{
		ray_step(ray, &axis);
		cell = grid_check_cell(game, ray->grid, &entity);
		if (cell == CELL_WALL)
			hit.hit = true;
		else if (cell == CELL_DOOR)
		{
			record_door_hit(door_out, ray, axis, entity);
			if (grid_door_block(game, entity))
				hit.hit = true;
		}
		if (hit.hit)
		{
			hit.cell = (t_u8)cell;
			hit.entity = entity;
		}
		if (calc_dist(ray, axis) > max_dist)
			break ;
	}
	fill_hit(&hit, ray, axis);
	return (hit);
}
