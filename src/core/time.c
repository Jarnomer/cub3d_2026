/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_f64	time_get_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((t_f64)tv.tv_sec + (t_f64)tv.tv_usec / 1000000.0);
}

void	time_init(t_time *time)
{
	ft_bzero(time, sizeof(t_time));
	time->current = time_get_seconds();
	time->previous = time->current;
}

void	time_update(t_time *time)
{
	time->previous = time->current;
	time->current = time_get_seconds();
	time->delta = time->current - time->previous;
	if (time->delta > MAX_DELTA)
		time->delta = MAX_DELTA;
	time->frame_count++;
	time->fps_timer += time->delta;
	time->fps_frames++;
	if (time->fps_timer >= 1.0)
	{
		time->fps = (t_f32)time->fps_frames / time->fps_timer;
		time->fps_timer = 0.0;
		time->fps_frames = 0;
	}
}
