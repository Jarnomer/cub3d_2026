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

static void	inertia_apply_input(t_sway *sway, t_vec2 mouse_delta)
{
	sway->velocity.x -= mouse_delta.x * INERTIA_STRENGTH;
	sway->velocity.y -= mouse_delta.y * INERTIA_STRENGTH;
}

static void	inertia_clamp(t_sway *sway)
{
	sway->inertia.x = clampf(sway->inertia.x, -INERTIA_MAX_X, INERTIA_MAX_X);
	sway->inertia.y = clampf(sway->inertia.y, -INERTIA_MAX_Y, INERTIA_MAX_Y);
}

static void	inertia_decay(t_sway *sway, t_f32 dt)
{
	t_f32	decay;

	sway->inertia.x += sway->velocity.x * dt;
	sway->inertia.y += sway->velocity.y * dt;
	decay = maxf(1.0f - (INERTIA_VEL_DECAY * dt), 0.0f);
	sway->velocity.x *= decay;
	sway->velocity.y *= decay;
	sway->inertia.x = lerpf(sway->inertia.x, 0.0f, INERTIA_POS_DECAY * dt);
	sway->inertia.y = lerpf(sway->inertia.y, 0.0f, INERTIA_POS_DECAY * dt);
}

void	inertia_update(t_sway *sway, t_vec2 mouse_delta, t_f32 dt)
{
	inertia_apply_input(sway, mouse_delta);
	inertia_clamp(sway);
	inertia_decay(sway, dt);
}

t_vec2	inertia_get_offset(t_sway *sway)
{
	return (sway->inertia);
}
