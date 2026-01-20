/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_bob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	calc_idle(t_bob *bob, t_f32 dt)
{
	bob->phase += BOB_IDLE_FREQ * dt;
	bob->amp.target.y = BOB_IDLE_AMP;
	bob->amp.target.x = 0.0f;
	bob->freq.target = BOB_IDLE_FREQ;
}

static void	calc_move(t_bob *bob, t_motion *motion, t_f32 speed)
{
	t_f32	mult;

	mult = 1.0f;
	if (motion->is_crouching)
		mult = BOB_CROUCH_MULT;
	bob->amp.target.y = BOB_WALK_AMP_Y * mult;
	bob->amp.target.x = BOB_WALK_AMP_X * mult;
	bob->freq.target = BOB_WALK_FREQ * (speed / PLAYER_SPEED);
}

static void	calc_sprint(t_bob *bob, t_f32 speed)
{
	t_f32	mult;

	bob->amp.target.y = BOB_SPRINT_AMP_Y;
	bob->amp.target.x = BOB_SPRINT_AMP_X;
	mult = speed / (PLAYER_SPEED * SPRINT_SPEED_MULT);
	bob->freq.target = BOB_SPRINT_FREQ * mult;
}

static void	apply_offsets(t_bob *bob, t_motion *motion, t_f32 dt)
{
	t_vec2	offset;

	bob->phase += bob->freq.current * dt;
	if (bob->phase > TAU)
		bob->phase -= TAU;
	offset.y = sinf(bob->phase);
	if (motion->is_sprinting && offset.y > 0.0f)
		offset.y = powf(offset.y, BOB_SPRINT_ASYM);
	offset.x = cosf(bob->phase * 0.5f);
	bob->amount.y = offset.y * bob->amp.current.y;
	bob->amount.x = offset.x * bob->amp.current.x;
}

void	bob_update(t_motion *motion, t_f32 dt)
{
	t_bob	*bob;
	t_f32	factor;
	t_f32	speed;

	bob = &motion->bob;
	speed = vec2_len(motion->velocity);
	if (speed < MOVE_STOP_THRESHOLD)
		calc_idle(bob, dt);
	else if (motion->is_sprinting)
		calc_sprint(bob, speed);
	else
		calc_move(bob, motion, speed);
	factor = BOB_LERP_SPEED * dt;
	bob->amp.current.y = lerpf(bob->amp.current.y, bob->amp.target.y, factor);
	bob->amp.current.x = lerpf(bob->amp.current.x, bob->amp.target.x, factor);
	bob->freq.current = lerpf(bob->freq.current, bob->freq.target, factor);
	apply_offsets(bob, motion, dt);
}
