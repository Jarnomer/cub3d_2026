/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/17 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <types.h>
# include <defs.h>

typedef struct s_assets		t_assets;
typedef struct s_entdef		t_entdef;
typedef struct s_prtcldef	t_prtcldef;
typedef struct s_surfdef	t_surfdef;
typedef struct s_anidef		t_anidef;
typedef struct s_wpndef		t_wpndef;
typedef struct s_decaldef	t_decaldef;
typedef struct s_decalmgr	t_decalmgr;

# define TEXDEF_FIELD_COUNT		3
# define SHEETDEF_FIELD_COUNT	4
# define ENTDEF_FIELD_COUNT		6
# define ANIMDEF_FIELD_COUNT	7
# define PRTCLDEF_FIELD_COUNT	12
# define SURFDEF_FIELD_COUNT	4
# define DECALDEF_FIELD_COUNT	7
# define IMPACTDEF_FIELD_COUNT	3
# define WPNDEF_FIELD_COUNT		12

# define CONFIG_FILE_EXT		".conf"

# define PATH_CONFIG_TEXTURE	"config/texture.conf"
# define PATH_CONFIG_SHEET		"config/sheet.conf"
# define PATH_CONFIG_ENTITY		"config/entity.conf"
# define PATH_CONFIG_ANIM		"config/anim.conf"
# define PATH_CONFIG_PARTICLE	"config/particle.conf"
# define PATH_CONFIG_SURFACE	"config/surface.conf"
# define PATH_CONFIG_DECAL		"config/decal.conf"
# define PATH_CONFIG_IMPACT		"config/impact.conf"
# define PATH_CONFIG_WEAPON		"config/weapon.conf"

typedef void	(*t_cfgproc)(char **fields, void *ctx);

typedef struct s_str_id
{
	const char	*str;
	t_i32		id;
}	t_str_id;

typedef struct s_cfgload
{
	const char	*path;
	t_i32		fields;
	t_cfgproc	process;
	void		*ctx;
}	t_cfgload;

void	config_load_assets(t_assets *assets);
void	config_parse_file(t_cfgload *cfg);
t_i32	config_str_to_id(const char *str);

void	config_load_textures(t_assets *assets);
void	config_load_sheets(t_assets *assets);

void	config_load_entities(t_entdef *defs);
void	config_load_anims(t_anidef *defs);

void	config_load_particles(t_prtcldef *defs);
void	config_load_surfaces(t_surfdef *defs);

void	config_load_impacts(t_decalmgr *mgr);
void	config_load_decals(t_decaldef *defs);

void	config_load_weapons(t_wpndef *defs);

#endif
