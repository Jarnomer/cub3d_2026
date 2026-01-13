/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/14 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_f32	calc_bob_idle(t_bob *bob)
{
	return (sinf(bob->phase * 2.0f) * WEAPON_BOB_IDLE_AMP);
}

static t_f32	calc_bob_move(t_bob *bob, t_f32 crouch_mult)
{
	t_f32	amp;

	amp = WEAPON_BOB_MOVE_AMP * crouch_mult;
	return (sinf(bob->phase) * amp);
}

void	weapon_bob_update(t_weapon *wpn, t_motion *motion, t_f32 dt)
{
	t_f32	target;
	t_f32	speed;
	t_f32	crouch_mult;

	speed = vec2_len(motion->velocity);
	crouch_mult = 1.0f;
	if (motion->is_crouching)
		crouch_mult = WEAPON_BOB_CROUCH_MULT;
	if (speed < MOVE_STOP_THRESHOLD)
		target = calc_bob_idle(&motion->bob);
	else
		target = calc_bob_move(&motion->bob, crouch_mult);
	wpn->bob = lerpf(wpn->bob, target, WEAPON_BOB_LERP * dt);
}
