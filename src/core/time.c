/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	time_init(t_time *time)
{
	*time = (t_time){0};
}

void	time_update(t_time *time, t_f32 dt)
{
	time->delta = dt;
	if (time->delta > MAX_DELTA)
		time->delta = MAX_DELTA;
	time->current += time->delta;
	time->accumulator += time->delta;
	time->frames++;
	time->samples++;
	if (time->accumulator >= 1.0)
	{
		time->fps = (t_f32)time->samples / time->accumulator;
		time->accumulator = 0.0;
		time->samples = 0;
	}
}
