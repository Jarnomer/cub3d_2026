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

typedef struct s_game	t_game;

typedef struct s_motion
{
	t_vec2	velocity;
	t_f32	stamina;
	t_f32	crouch_amount;
	t_f32	crouch_target;
	bool	is_grounded;
	bool	is_crouching;
}	t_motion;

void	motion_init(t_motion *motion);
void	motion_update(t_motion *motion, t_f32 dt);

void	crouch_start(t_motion *motion);
void	crouch_end(t_motion *motion);
void	crouch_update(t_motion *motion, t_f32 dt);
t_f32	crouch_height(t_motion *motion);
t_f32	crouch_get_mult(t_motion *motion);

#endif
