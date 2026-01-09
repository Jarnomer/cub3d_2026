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

void	time_update(t_time *time, mlx_t *mlx)
{
	time->delta = mlx->delta_time;
	if (time->delta > MAX_DELTA)
		time->delta = MAX_DELTA;
	time->current += time->delta;
	time->fps_timer += time->delta;
	time->frame_count++;
	time->fps_frames++;
	if (time->fps_timer >= 1.0)
	{
		time->fps = (t_f32)time->fps_frames / time->fps_timer;
		time->fps_timer = 0.0;
		time->fps_frames = 0;
	}
}
