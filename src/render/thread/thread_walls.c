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

static void	init_wall_ctx(t_thread *thread, t_game *game, t_i32 count)
{
	t_i32	cols_per_thread;
	t_i32	i;

	cols_per_thread = game->render.width / count;
	i = 0;
	while (i < count)
	{
		thread[i] = (t_thread){.game = game, .id = i};
		thread[i].start = i * cols_per_thread;
		if (i == count - 1)
			thread[i].end = game->render.width;
		else
			thread[i].end = (i + 1) * cols_per_thread;
		i++;
	}
}

static void	*wall_worker(void *arg)
{
	t_thread	*thread;
	t_i32		x;

	thread = (t_thread *)arg;
	x = thread->start;
	while (x < thread->end)
	{
		render_wall_column(thread->game, x);
		x++;
	}
	return (NULL);
}

void	render_walls(t_game *game)
{
	pthread_t	threads[THREAD_COUNT];
	t_thread	thread[THREAD_COUNT];
	int			err;
	t_i32		i;

	init_wall_ctx(thread, game, THREAD_COUNT);
	i = 0;
	while (i < THREAD_COUNT)
	{
		err = pthread_create(&threads[i], NULL, wall_worker, &thread[i]);
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
