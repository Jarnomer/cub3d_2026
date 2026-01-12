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

static void	init_floor_ctx(t_thread *thread, t_game *game, t_i32 count)
{
	t_i32	rows_per_thread;
	t_i32	i;

	rows_per_thread = game->render.height / count;
	i = 0;
	while (i < count)
	{
		thread[i] = (t_thread){.game = game, .id = i};
		thread[i].start = i * rows_per_thread;
		if (i == count - 1)
			thread[i].end = game->render.height;
		else
			thread[i].end = (i + 1) * rows_per_thread;
		i++;
	}
}

static void	*floor_worker(void *arg)
{
	t_thread	*thread;
	t_i32		y;

	thread = (t_thread *)arg;
	y = thread->start;
	while (y < thread->end)
	{
		render_floor_row(thread->game, y);
		y++;
	}
	return (NULL);
}

void	render_floor(t_game *game)
{
	pthread_t	threads[THREAD_COUNT];
	t_thread	thread[THREAD_COUNT];
	int			err;
	t_i32		i;

	init_floor_ctx(thread, game, THREAD_COUNT);
	i = 0;
	while (i < THREAD_COUNT)
	{
		err = pthread_create(&threads[i], NULL, floor_worker, &thread[i]);
		if (err != 0)
			err_exit_context(MSG_THREAD, strerror(err));
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
