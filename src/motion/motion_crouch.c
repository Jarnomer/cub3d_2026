/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_crouch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	crouch_start(t_motion *motion)
{
	if (motion->is_crouching)
		return ;
	motion->is_crouching = true;
	motion->crouch.target = 1.0f;
}

void	crouch_end(t_motion *motion)
{
	if (!motion->is_crouching)
		return ;
	motion->is_crouching = false;
	motion->crouch.target = 0.0f;
}

void	crouch_update(t_motion *motion, t_f32 dt)
{
	t_f32	diff;

	diff = motion->crouch.target - motion->crouch.current;
	if (absf(diff) < CROUCH_THRESHOLD)
		motion->crouch.current = motion->crouch.target;
	else
		motion->crouch.current += diff * CROUCH_LERP_SPEED * dt;
	motion->crouch.current = clampf(motion->crouch.current, 0.0f, 1.0f);
}

t_f32	crouch_get_height(t_motion *motion)
{
	return (motion->crouch.current * CROUCH_HEIGHT_OFFSET);
}

t_f32	crouch_get_mult(t_motion *motion)
{
	if (!motion->is_crouching && motion->crouch.current < CROUCH_THRESHOLD)
		return (1.0f);
	return (1.0f - motion->crouch.current * (1.0f - CROUCH_SPEED_MULT));
}
