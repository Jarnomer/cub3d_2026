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

static void	parse_partdef_values(t_partdef *def, char **f)
{
	def->speed_min = ft_atof(f[3]);
	def->speed_max = ft_atof(f[4]);
	def->life_min = ft_atof(f[5]);
	def->life_max = ft_atof(f[6]);
	def->gravity = ft_atof(f[7]);
	def->spread = ft_atof(f[8]);
	def->size = ft_atof(f[9]);
	def->bounce = ft_atof(f[10]);
	def->is_faded = (ft_atoi(f[11]) != 0);
}

static void	process_particle(char **fields, void *ctx)
{
	t_partdef	*defs;
	t_partdef	def;
	t_i32		id;

	defs = (t_partdef *)ctx;
	id = config_str_to_id(fields[0]);
	if (id <= PARTICLE_NONE || id >= PARTICLE_COUNT)
		return ;
	def = (t_partdef){.id = id};
	def.color_start = parse_hex_color(fields[1]);
	def.color_end = parse_hex_color(fields[2]);
	parse_partdef_values(&def, fields);
	defs[id] = def;
}

void	config_load_particles(t_partdef *defs)
{
	t_cfgload	cfg;

	cfg = (t_cfgload){
		.path = PATH_CONFIG_PARTICLE,
		.fields = PARTDEF_FIELD_COUNT,
		.process = process_particle,
		.ctx = defs
	};
	config_parse_file(&cfg);
}
