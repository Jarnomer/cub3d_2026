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

static void	init_wall_ctx(t_thd *ctx, t_game *game, t_i32 count)
{
	t_i32	cols_per_thread;
	t_i32	i;

	cols_per_thread = game->render.width / count;
	i = 0;
	while (i < count)
	{
		ctx[i].game = game;
		ctx[i].projs = NULL;
		ctx[i].count = 0;
		ctx[i].id = i;
		ctx[i].start = i * cols_per_thread;
		if (i == count - 1)
			ctx[i].end = game->render.width;
		else
			ctx[i].end = (i + 1) * cols_per_thread;
		i++;
	}
}

static void	*wall_worker(void *arg)
{
	t_thd	*ctx;
	t_i32	x;

	ctx = (t_thd *)arg;
	x = ctx->start;
	while (x < ctx->end)
	{
		render_wall_column(ctx->game, x);
		x++;
	}
	return (NULL);
}

void	render_walls(t_game *game)
{
	pthread_t	threads[THREAD_COUNT];
	t_thd		ctx[THREAD_COUNT];
	int			err;
	t_i32		i;

	init_wall_ctx(ctx, game, THREAD_COUNT);
	i = 0;
	while (i < THREAD_COUNT)
	{
		err = pthread_create(&threads[i], NULL, wall_worker, &ctx[i]);
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
