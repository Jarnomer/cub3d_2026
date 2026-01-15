/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_surface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/14 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	process_surface(char **fields, void *ctx)
{
	t_surfdef	*defs;
	t_surfdef	def;
	t_i32		type;

	defs = (t_surfdef *)ctx;
	type = config_str_to_id(fields[0]);
	if (type < 0 || type >= SURFACE_COUNT)
		return ;
	def = (t_surfdef){.type = type};
	def.particle = config_str_to_id(fields[1]);
	def.count_min = ft_atoi(fields[2]);
	def.count_max = ft_atoi(fields[3]);
	defs[type] = def;
}

void	config_load_surfaces(t_surfdef *defs)
{
	t_cfgload	cfg;

	cfg = (t_cfgload){
		.path = PATH_CONFIG_SURFACE,
		.fields = SURFDEF_FIELD_COUNT,
		.process = process_surface,
		.ctx = defs
	};
	config_parse_file(&cfg);
}
