/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	motion_init(t_motion *motion)
{
	*motion = (t_motion){.stamina = STAMINA_MAX, .is_grounded = true};
	fov_init(&motion->fov);
}

void	motion_update(t_motion *motion, t_f32 dt)
{
	crouch_update(motion, dt);
	jump_update(motion, dt);
	sprint_update(motion, dt);
	bob_update(motion, dt);
	fov_update(motion, dt);
}
