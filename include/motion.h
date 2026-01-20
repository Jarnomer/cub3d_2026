/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOTION_H
# define MOTION_H

# include <types.h>
# include <vector.h>
# include <calc.h>

typedef struct s_game	t_game;

typedef struct s_bob
{
	t_f32	phase;
	t_vec2	amount;
	t_track	freq;
	t_trans	amp;
}	t_bob;

typedef struct s_fov
{
	t_f32	base;
	t_f32	current;
	t_f32	target;
}	t_fov;

typedef struct s_jump
{
	t_f32	offset;
	t_f32	velocity;
}	t_jump;

typedef struct s_motion
{
	t_vec2	velocity;
	t_f32	stamina;
	t_track	crouch;
	t_jump	jump;
	t_bob	bob;
	t_fov	fov;
	bool	is_grounded;
	bool	is_jumping;
	bool	is_crouching;
	bool	is_sprinting;
}	t_motion;

void	motion_init(t_motion *motion);
void	motion_update(t_motion *motion, t_f32 dt);

void	move_apply_acceleration(t_motion *motion, t_vec2 target, t_f32 dt);
void	move_apply_friction(t_motion *motion, t_f32 dt);

void	bob_update(t_motion *motion, t_f32 dt);

void	fov_init(t_fov *fov);
void	fov_update(t_motion *motion, t_f32 dt);

void	crouch_start(t_motion *motion);
void	crouch_end(t_motion *motion);
void	crouch_update(t_motion *motion, t_f32 dt);
t_f32	crouch_get_height(t_motion *motion);
t_f32	crouch_get_mult(t_motion *motion);

void	sprint_start(t_motion *motion);
void	sprint_end(t_motion *motion);
void	sprint_update(t_motion *motion, t_f32 dt);
t_f32	sprint_get_mult(t_motion *motion);

void	jump_start(t_motion *motion);
void	jump_end(t_motion *motion);
void	jump_update(t_motion *motion, t_f32 dt);
t_f32	jump_get_height(t_motion *motion);

#endif
