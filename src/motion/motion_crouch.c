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
	motion->crouch_target = 1.0f;
}

void	crouch_end(t_motion *motion)
{
	if (!motion->is_crouching)
		return ;
	motion->is_crouching = false;
	motion->crouch_target = 0.0f;
}

void	crouch_update(t_motion *motion, t_f32 dt)
{
	t_f32	diff;

	diff = motion->crouch_target - motion->crouch_amount;
	if (absf(diff) < CROUCH_THRESHOLD)
		motion->crouch_amount = motion->crouch_target;
	else
		motion->crouch_amount += diff * CROUCH_LERP_SPEED * dt;
	motion->crouch_amount = clampf(motion->crouch_amount, 0.0f, 1.0f);
}

t_f32	crouch_height(t_motion *motion)
{
	return (motion->crouch_amount * CROUCH_HEIGHT_OFFSET);
}

t_f32	crouch_get_mult(t_motion *motion)
{
	if (!motion->is_crouching && motion->crouch_amount < CROUCH_THRESHOLD)
		return (1.0f);
	return (1.0f - motion->crouch_amount * (1.0f - CROUCH_SPEED_MULT));
}
