/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	move_accelerate(t_motion *motion, t_vec2 target, t_f32 dt)
{
	t_vec2	diff;
	t_f32	accel;

	diff = vec2_sub(target, motion->velocity);
	accel = MOVE_ACCEL * dt;
	if (vec2_len(diff) < accel)
		motion->velocity = target;
	else
		motion->velocity = vec2_add(motion->velocity, vec2_mul(diff, accel));
}

void	move_apply_friction(t_motion *motion, t_f32 dt)
{
	t_f32	speed;
	t_f32	drop;

	speed = vec2_len(motion->velocity);
	if (speed < MOVE_STOP_THRESHOLD)
	{
		motion->velocity = vec2_zero();
		return ;
	}
	drop = speed * MOVE_FRICTION * dt;
	if (drop > speed)
		motion->velocity = vec2_zero();
	else
		motion->velocity = vec2_mul(motion->velocity, (speed - drop) / speed);
}

t_vec2	move_get_velocity(t_motion *motion)
{
	return (motion->velocity);
}
