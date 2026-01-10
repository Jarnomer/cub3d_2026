/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shake.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	shake_init(t_shake *shake)
{
	*shake = (t_shake){.decay = SHAKE_DECAY};
}

void	shake_add(t_shake *shake, t_f32 intensity, t_f32 duration)
{
	if (intensity > shake->intensity)
		shake->intensity = intensity;
	if (duration > shake->timer)
		shake->timer = duration;
	shake->duration = shake->timer;
}

void	shake_update(t_shake *shake, t_f32 dt)
{
	t_f32	progress;
	t_f32	current;

	if (shake->timer <= 0.0f)
	{
		shake->offset_x = 0.0f;
		shake->offset_y = 0.0f;
		shake->intensity = 0.0f;
		return ;
	}
	shake->timer -= dt;
	progress = shake->timer / shake->duration;
	current = shake->intensity * progress * progress;
	shake->offset_x = rand_range(-1.0f, 1.0f) * current;
	shake->offset_y = rand_range(-1.0f, 1.0f) * current;
}

t_vec2	shake_get_offset(t_shake *shake)
{
	return (vec2_new(shake->offset_x, shake->offset_y));
}
