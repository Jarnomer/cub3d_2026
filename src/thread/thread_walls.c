/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/04 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	init_wall_ctx(t_thd *data, t_game *game, t_i32 count)
{
	t_i32	cols_per_thread;
	t_i32	i;

	cols_per_thread = game->render.width / count;
	i = 0;
	while (i < count)
	{
		data[i].game = game;
		data[i].id = i;
		data[i].start = i * cols_per_thread;
		if (i == count - 1)
			data[i].end = game->render.width;
		else
			data[i].end = (i + 1) * cols_per_thread;
		i++;
	}
}

static void	*wall_worker(void *arg)
{
	t_thd	*data;
	t_i32	x;

	data = (t_thd *)arg;
	x = data->start;
	while (x < data->end)
	{
		render_wall_column(data->game, x);
		x++;
	}
	return (NULL);
}

void	render_walls(t_game *game)
{
	pthread_t	threads[THREAD_COUNT];
	t_thd		data[THREAD_COUNT];
	t_i32		i;
	int			err;

	init_wall_ctx(data, game, THREAD_COUNT);
	i = 0;
	while (i < THREAD_COUNT)
	{
		err = pthread_create(&threads[i], NULL, wall_worker, &data[i]);
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
