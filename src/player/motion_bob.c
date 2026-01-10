/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_bob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	bob_update(t_motion *motion, t_f32 dt, bool is_moving)
{
	t_f32	target_bob;

	motion->is_moving = is_moving;
	if (is_moving && motion->is_grounded)
	{
		motion->bob_timer += dt * HEAD_BOB_SPEED;
		target_bob = sinf(motion->bob_timer) * HEAD_BOB_AMOUNT;
	}
	else
	{
		target_bob = 0.0f;
		motion->bob_timer = 0.0f;
	}
	motion->bob_offset += (target_bob - motion->bob_offset) * BOB_LERP * dt;
}

void	idle_update(t_motion *motion, t_f32 dt)
{
	motion->idle_timer += dt * IDLE_SPEED;
	motion->idle_offset = sinf(motion->idle_timer) * IDLE_AMOUNT;
}

t_f32	bob_get_weapon_offset(t_motion *motion)
{
	t_f32	bob;
	t_f32	idle;

	bob = 0.0f;
	if (motion->is_moving && motion->is_grounded)
		bob = sinf(motion->bob_timer * 2.0f) * WEAPON_BOB_AMOUNT;
	idle = sinf(motion->idle_timer) * WEAPON_IDLE_AMOUNT;
	return (bob + idle);
}

t_f32	bob_get_camera_offset(t_motion *motion)
{
	return (motion->bob_offset + motion->idle_offset * 0.3f);
}
