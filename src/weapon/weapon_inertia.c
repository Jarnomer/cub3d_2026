/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_inertia.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/14 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	inertia_integrate(t_sway *sway, t_f32 dt)
{
	t_f32	decay;

	sway->inertia.x += sway->velocity.x * dt;
	sway->inertia.y += sway->velocity.y * dt;
	decay = 1.0f - (INERTIA_VEL_DECAY * dt);
	decay = maxf(decay, 0.0f);
	sway->velocity.x *= decay;
	sway->velocity.y *= decay;
}

void	weapon_inertia_update(t_sway *sway, t_vec2 mouse_delta, t_f32 dt)
{
	t_f32	factor;

	sway->velocity.x -= mouse_delta.x * INERTIA_STRENGTH;
	sway->velocity.y -= mouse_delta.y * INERTIA_STRENGTH;
	inertia_integrate(sway, dt);
	sway->inertia.x = clampf(sway->inertia.x, -INERTIA_MAX_X, INERTIA_MAX_X);
	sway->inertia.y = clampf(sway->inertia.y, -INERTIA_MAX_Y, INERTIA_MAX_Y);
	factor = INERTIA_POS_DECAY * dt;
	sway->inertia.x = lerpf(sway->inertia.x, 0.0f, factor);
	sway->inertia.y = lerpf(sway->inertia.y, 0.0f, factor);
}
