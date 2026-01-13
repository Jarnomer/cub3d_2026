/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_fov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	fov_init(t_fov *fov)
{
	*fov = (t_fov){.base = BASE_FOV, .current = BASE_FOV, .target = BASE_FOV};
}

void	fov_set_target(t_fov *fov, t_f32 target)
{
	fov->target = target;
}

void	fov_reset(t_fov *fov)
{
	fov->target = fov->base;
}

void	fov_update(t_fov *fov, t_motion *motion, t_f32 dt)
{
	if (motion->is_sprinting)
		fov->target = fov->base + FOV_SPRINT_OFFSET;
	else
		fov->target = fov->base;
	fov->current = lerpf(fov->current, fov->target, FOV_LERP_SPEED * dt);
}

t_f32	fov_get_current(t_fov *fov)
{
	return (fov->current);
}
