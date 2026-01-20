/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_particle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/14 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_u32	parse_hex_color(const char *str)
{
	t_u32	color;
	t_i32	i;
	char	c;

	color = 0;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	while (str[i] && i < 8)
	{
		c = str[i];
		color <<= 4;
		if (c >= '0' && c <= '9')
			color |= (c - '0');
		else if (c >= 'a' && c <= 'f')
			color |= (c - 'a' + 10);
		else if (c >= 'A' && c <= 'F')
			color |= (c - 'A' + 10);
		i++;
	}
	return (color);
}

static void	process_particle(char **fields, void *ctx)
{
	t_prtcldef	*defs;
	t_prtcldef	def;
	t_i32		id;

	defs = (t_prtcldef *)ctx;
	id = config_str_to_id(fields[0]);
	if (id <= PARTICLE_NONE || id >= PARTICLE_COUNT)
		return ;
	def = (t_prtcldef){.id = id};
	def.color.start = parse_hex_color(fields[1]);
	def.color.end = parse_hex_color(fields[2]);
	def.speed.min = ft_atof(fields[3]);
	def.speed.max = ft_atof(fields[4]);
	def.life.min = ft_atof(fields[5]);
	def.life.max = ft_atof(fields[6]);
	def.gravity = ft_atof(fields[7]);
	def.spread = ft_atof(fields[8]);
	def.size = ft_atof(fields[9]);
	def.bounce = ft_atof(fields[10]);
	def.is_faded = (ft_atoi(fields[11]) != 0);
	defs[id] = def;
}

void	config_load_particles(t_prtcldef *defs)
{
	t_cfgload	cfg;

	cfg = (t_cfgload){
		.path = PATH_CONFIG_PARTICLE,
		.fields = PRTCLDEF_FIELD_COUNT,
		.process = process_particle,
		.ctx = defs
	};
	config_parse_file(&cfg);
}

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
	def.count.min = ft_atoi(fields[2]);
	def.count.max = ft_atoi(fields[3]);
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
