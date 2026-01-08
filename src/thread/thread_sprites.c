/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	init_sprite_ctx(t_thd *ctx, t_game *game, t_proj *projs, t_u32 cnt)
{
	t_i32	cols_per_thread;
	t_i32	i;

	cols_per_thread = game->render.width / THREAD_COUNT;
	i = 0;
	while (i < THREAD_COUNT)
	{
		ctx[i] = (t_thd){.game = game, .projs = projs, .id = i, .count = cnt};
		ctx[i].start = i * cols_per_thread;
		if (i == THREAD_COUNT - 1)
			ctx[i].end = game->render.width;
		else
			ctx[i].end = (i + 1) * cols_per_thread;
		i++;
	}
}

static void	*sprite_worker(void *arg)
{
	t_thd	*ctx;
	t_i32	x;
	t_u32	i;

	ctx = (t_thd *)arg;
	i = 0;
	while (i < ctx->count)
	{
		x = maxi(ctx->projs[i].start.x, ctx->start);
		while (x < ctx->projs[i].end.x && x < ctx->end)
		{
			if (zbuf_test(&ctx->game->render, x, ctx->projs[i].dist))
			{
				if (ctx->projs[i].use_sheet)
					render_sheet_column(ctx->game, &ctx->projs[i], x);
				else
					render_sprite_column(ctx->game, &ctx->projs[i], x);
			}
			x++;
		}
		i++;
	}
	return (NULL);
}

static void	thread_sprites(t_game *game, t_proj *projs, t_u32 count)
{
	pthread_t	threads[THREAD_COUNT];
	t_thd		ctx[THREAD_COUNT];
	int			err;
	t_i32		i;

	init_sprite_ctx(ctx, game, projs, count);
	i = 0;
	while (i < THREAD_COUNT)
	{
		err = pthread_create(&threads[i], NULL, sprite_worker, &ctx[i]);
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

void	render_sprites(t_game *game)
{
	t_proj	*projs;
	t_u32	count;

	if (game->entities.size == 0)
		return ;
	projs = arena_alloc(&game->arena, sizeof(t_proj) * game->entities.size);
	if (!projs)
		return ;
	count = collect_sprites(game, projs);
	if (count == 0)
		return ;
	sort_sprites(projs, count);
	thread_sprites(game, projs, count);
}
