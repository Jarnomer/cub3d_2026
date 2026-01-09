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

static void	init_floor_ctx(t_thd *thd, t_game *game, t_i32 count)
{
	t_i32	rows_per_thread;
	t_i32	i;

	rows_per_thread = game->render.height / count;
	i = 0;
	while (i < count)
	{
		thd[i] = (t_thd){.game = game, .id = i};
		thd[i].start = i * rows_per_thread;
		if (i == count - 1)
			thd[i].end = game->render.height;
		else
			thd[i].end = (i + 1) * rows_per_thread;
		i++;
	}
}

static void	*floor_worker(void *arg)
{
	t_thd	*thd;
	t_i32	y;

	thd = (t_thd *)arg;
	y = thd->start;
	while (y < thd->end)
	{
		render_floor_row(thd->game, y);
		y++;
	}
	return (NULL);
}

void	render_floor(t_game *game)
{
	pthread_t	threads[THREAD_COUNT];
	t_thd		thd[THREAD_COUNT];
	int			err;
	t_i32		i;

	init_floor_ctx(thd, game, THREAD_COUNT);
	i = 0;
	while (i < THREAD_COUNT)
	{
		err = pthread_create(&threads[i], NULL, floor_worker, &thd[i]);
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
