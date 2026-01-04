/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	init_floor_ctx(t_thd *data, t_game *game, t_i32 count)
{
	t_i32	rows_per_thread;
	t_i32	i;

	rows_per_thread = game->render.height / count;
	i = 0;
	while (i < count)
	{
		data[i].game = game;
		data[i].id = i;
		data[i].start = i * rows_per_thread;
		if (i == count - 1)
			data[i].end = game->render.height;
		else
			data[i].end = (i + 1) * rows_per_thread;
		i++;
	}
}

static void	*floor_worker(void *arg)
{
	t_thd	*data;
	t_i32	y;

	data = (t_thd *)arg;
	y = data->start;
	while (y < data->end)
	{
		render_floor_row(data->game, y);
		y++;
	}
	return (NULL);
}

void	render_floor(t_game *game)
{
	pthread_t	threads[THREAD_COUNT];
	t_thd		data[THREAD_COUNT];
	t_i32		i;
	int			err;

	init_floor_ctx(data, game, THREAD_COUNT);
	i = 0;
	while (i < THREAD_COUNT)
	{
		err = pthread_create(&threads[i], NULL, floor_worker, &data[i]);
		if (err != 0)
			err_exit_context("pthread_create", strerror(err));
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
