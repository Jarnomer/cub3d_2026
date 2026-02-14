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

static t_f32	get_bob_mult(t_sway *sway, t_motion *motion)
{
	t_f32	mult;

	mult = 1.0f;
	if (motion->is_crouching)
		mult *= WEAPON_BOB_CROUCH_MULT;
	mult += sway->sprint * SPRINT_BOB_MULT;
	return (mult);
}

void	weapon_bob_update(t_weapon *wpn, t_motion *motion, t_f32 dt)
{
	t_f32	target;
	t_f32	speed;
	t_f32	amp;

	speed = vec2_len(motion->velocity);
	amp = get_bob_mult(&wpn->sway, motion) * WEAPON_BOB_MOVE_AMP;
	if (speed < MOVE_STOP_THRESHOLD)
		target = sinf(motion->bob.phase * 2.0f) * WEAPON_BOB_IDLE_AMP;
	else
		target = (1.0f - absf(sinf(motion->bob.phase))) * amp;
	wpn->bob = lerpf(wpn->bob, target, WEAPON_BOB_LERP * dt);
}
