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

/*
** Determines wall texture direction from ray hit
**
** The texture direction is opposite to ray travel direction:
**   - Ray traveling +X hits WEST-facing wall
**   - Ray traveling -X hits EAST-facing wall
**   - Ray traveling +Y hits NORTH-facing wall (remember: +Y is south in world)
**   - Ray traveling -Y hits SOUTH-facing wall
**
**              N (WALL_NORTH faces south, visible from south)
**              |
**        W ----+---- E
**              |
**              S
*/
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

/*
** Calculates fractional hit position along wall (0.0 to 1.0)
**
** This is used for texture mapping - wall_x determines which
** column of the texture to sample.
**
** If ray hit vertical wall (AXIS_X):
**   wall_x = Y position of hit point
**
** If ray hit horizontal wall (AXIS_Y):
**   wall_x = X position of hit point
**
** We take only fractional part to get position within cell
*/
static t_f32	calc_wall_hit_x(t_ray *ray, t_f32 dist, int axis)
{
	t_f32	wall_x;

	if (axis == AXIS_X)
		wall_x = ray->origin.y + dist * ray->dir.y;
	else
		wall_x = ray->origin.x + dist * ray->dir.x;
	return (wall_x - floorf(wall_x));
}

/*
** Calculates perpendicular distance to avoid fisheye distortion
**
** Instead of Euclidean distance, we use perpendicular distance:
**   perp_dist = dist.axis - delta.axis
**
** This is the distance we've traveled minus one step, because
** dist.axis was already updated after the hit.
**
**       Euclidean          Perpendicular
**       (fisheye)          (correct)
**           /|                 |
**          / |                 |
**         /  |  wall           |  wall
**        /   |                 |
**       *    |                 |
**      cam                    cam looks straight
**
** The perpendicular distance gives uniform wall height across screen
*/
t_f32	calc_dist(t_ray *ray, int axis)
{
	t_f32	dist;

	if (axis == AXIS_X)
		dist = ray->dist.x - ray->delta.x;
	else
		dist = ray->dist.y - ray->delta.y;
	return (maxf(dist, EPSILON));
}

/*
** Fills hit result structure with calculated values
*/
static void	fill_hit(t_hit *hit, t_ray *ray, int axis)
{
	hit->axis = axis;
	hit->dist = calc_dist(ray, axis);
	hit->wall_x = calc_wall_hit_x(ray, hit->dist, axis);
	hit->dir = get_wall_direction(ray, axis);
	hit->grid = ray->grid;
}

/*
** Standard DDA - stops at first solid surface
**
** Steps through grid until hitting:
**   - A wall (CELL_WALL)
**   - A blocking door (closed or closing)
**   - Maximum distance reached
**
** Returns hit information for the solid surface found
*/
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

/*
** Records first door hit during passthrough DDA
*/
static void	record_door_hit(t_hit *door_out, t_ray *ray, int axis, t_i32 entity)
{
	if (door_out->entity != ENTITY_VOID)
		return ;
	door_out->hit = true;
	door_out->cell = CELL_DOOR;
	door_out->entity = entity;
	fill_hit(door_out, ray, axis);
}

/*
** Passthrough DDA - continues through open/opening doors
**
** This variant is used for wall rendering to handle the case where
** a door is open and we need to render both:
**   1. The wall behind the door
**   2. The door as a transparent overlay
**
**       Camera ---> |Open Door| ---> |Wall|
**                   ^                ^
**                   door_out         return value
**
** The first non-blocking door encountered is saved to door_out.
** The ray continues until hitting a solid wall or blocking door.
**
** This allows correct rendering of:
**   - Walls visible through open doors
**   - Door frames/edges as overlay
**   - Sprites between camera and wall
*/
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
