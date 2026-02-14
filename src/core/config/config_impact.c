/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_impact.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/17 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	process_impact(char **fields, void *ctx)
{
	t_decalmgr	*mgr;
	t_impactdef	def;

	mgr = (t_decalmgr *)ctx;
	def.ammo = config_str_to_id(fields[0]);
	def.target = config_str_to_id(fields[1]);
	def.decal = config_str_to_id(fields[2]);
	if (def.ammo < 0 || def.decal <= DECAL_NONE)
		return ;
	mgr->impacts[mgr->impact_count] = def;
	mgr->impact_count++;
}

void	config_load_impacts(t_decalmgr *mgr)
{
	t_cfgload	cfg;

	cfg = (t_cfgload){
		.path = PATH_CONFIG_IMPACT,
		.fields = IMPACTDEF_FIELD_COUNT,
		.process = process_impact,
		.ctx = mgr
	};
	config_parse_file(&cfg);
}

static void	process_decal(char **fields, void *ctx)
{
	t_decaldef	*defs;
	t_decaldef	def;
	t_i32		id;

	defs = (t_decaldef *)ctx;
	id = config_str_to_id(fields[0]);
	if (id <= DECAL_NONE || id >= DECAL_COUNT)
		return ;
	def = (t_decaldef){.id = id};
	def.sheet_id = config_str_to_id(fields[1]);
	def.anim_id = config_str_to_id(fields[2]);
	def.decal_frame = ft_atoi(fields[3]);
	def.scale = ft_atof(fields[4]);
	def.lifespan = ft_atof(fields[5]);
	def.fade_time = ft_atof(fields[6]);
	defs[id] = def;
}

void	config_load_decals(t_decaldef *defs)
{
	t_cfgload	cfg;

	cfg = (t_cfgload){
		.path = PATH_CONFIG_DECAL,
		.fields = DECALDEF_FIELD_COUNT,
		.process = process_decal,
		.ctx = defs
	};
	config_parse_file(&cfg);
}
