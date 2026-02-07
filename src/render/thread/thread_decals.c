/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_decals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/17 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	init_decal_ctx(t_thread *ctx, t_game *game, t_proj *projs,
	t_u32 count)
{
	t_i32	cols;
	t_i32	i;

	cols = game->render.width / THREAD_COUNT;
	i = 0;
	while (i < THREAD_COUNT)
	{
		ctx[i] = (t_thread){.game = game, .projs = projs, .id = i};
		ctx[i].count = count;
		ctx[i].start = i * cols;
		if (i == THREAD_COUNT - 1)
			ctx[i].end = game->render.width;
		else
			ctx[i].end = (i + 1) * cols;
		i++;
	}
}

static void	render_decal_range(t_thread *ctx, t_proj *proj, t_i32 x)
{
	t_render	render;
	t_i32		end;

	render = ctx->game->render;
	end = mini(rect_right(proj->bounds), ctx->end);
	while (x < end)
	{
		if (x > 0 || x <= render.width)
		{
			if (proj->dist <= render.z_buffer[x] + DECAL_ZBUF_BIAS)
				render_sheet_column(ctx->game, proj, x);
		}
		x++;
	}
}

static void	*decal_worker(void *arg)
{
	t_thread	*ctx;
	t_proj		*proj;
	t_i32		x;
	t_u32		i;

	ctx = (t_thread *)arg;
	i = 0;
	while (i < ctx->count)
	{
		proj = &ctx->projs[i];
		x = maxi(proj->bounds.x, ctx->start);
		render_decal_range(ctx, proj, x);
		i++;
	}
	return (NULL);
}

static void	thread_decals(t_game *game, t_proj *projs, t_u32 count)
{
	pthread_t	threads[THREAD_COUNT];
	t_thread	ctx[THREAD_COUNT];
	int			err;
	t_i32		i;

	init_decal_ctx(ctx, game, projs, count);
	i = 0;
	while (i < THREAD_COUNT)
	{
		err = pthread_create(&threads[i], NULL, decal_worker, &ctx[i]);
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

void	render_decals(t_game *game)
{
	t_proj	*projs;
	t_u32	count;
	size_t	bytes;

	if (game->decals.active == 0)
		return ;
	bytes = sizeof(t_proj) * game->decals.pool.capacity;
	projs = arena_alloc(&game->arena, bytes);
	if (!projs)
		return ;
	count = decals_collect(game, projs);
	if (count == 0)
		return ;
	sprites_sort(projs, count);
	thread_decals(game, projs, count);
}
