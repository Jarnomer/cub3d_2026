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

void	fov_update(t_motion *motion, t_f32 dt)
{
	t_fov	*fov;

	fov = &motion->fov;
	if (motion->is_sprinting)
		fov->target = fov->base + FOV_SPRINT_OFFSET;
	else
		fov->target = fov->base;
	fov->current = lerpf(fov->current, fov->target, FOV_LERP_SPEED * dt);
}
