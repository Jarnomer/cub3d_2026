# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by jmertane          #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#    VARIABLES
# **************************************************************************** #

NAME := cub3D

SOURCEDIR := src
HEADERDIR := include
BUILDDIR  := build
BUILDLOG  := build.log

LIBFTDIR  := lib/libft
LIBFTBIN  := libft.a

MLXDIR    := lib/MLX42
MLXBIN    := libmlx42.a

TESTMAP   := assets/maps/test.cub
TESTCASE  := ./$(NAME) $(TESTMAP)

# **************************************************************************** #
#    COMMANDS
# **************************************************************************** #

RM          := rm -rf
SCREENCLEAR := printf "\033c"

# **************************************************************************** #
#    COMPILATION
# **************************************************************************** #

CC         := cc
CFLAGS     := -Wall -Werror -Wextra -O2
CPPFLAGS   := -c -MMD -MP
DEBUGFLAGS := -g -fsanitize=address -DDEBUG
MAKEFLAGS  += --no-print-directory -j4
MLXFLAGS   := -ldl -lglfw -pthread -lm

# **************************************************************************** #
#    VALGRIND
# **************************************************************************** #

LEAKSLOG := leaks.log
SUPPFILE := mlx.supp
VLGFLAGS := --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --track-fds=yes \
            --suppressions=$(SUPPFILE) \
            --log-file=$(LEAKSLOG) \
            --verbose

# **************************************************************************** #
#    SOURCES
# **************************************************************************** #

MODULES := core \
           input \
           render \
           thread \
           parse \
           pool \
           calc \
           vector \
           utils

SOURCES := main \
           game \
           time \
           input \
           input_keys \
           input_mouse \
           player \
           camera \
           map \
           parse \
           parse_file \
           parse_elem \
           parse_asset \
           parse_map \
           parse_map_valid \
           parse_map_walls \
           parse_utils \
           render \
           render_walls \
           render_floor \
           raycast \
           raycast_dda \
           raycast_utils \
           texture \
           thread_floor \
           thread_walls \
           calc_color \
           calc_angle \
           calc_scalar \
           calc_scalar_int \
           calc_scalar_ops \
           vec2 \
           vec2_arith \
           vec2_prod \
           vec2_trans \
           vec2i \
           err_exit \
           err_print \
           safe_mlx \
           safe_str

SOURCES := $(addsuffix .c, $(SOURCES))

OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:.c=.o))

SOURCEDIR += $(addprefix $(SOURCEDIR)/, $(MODULES))

INCS := $(addprefix -I, $(HEADERDIR) $(LIBFTDIR)/$(HEADERDIR))
INCS += $(addprefix -I, $(MLXDIR)/$(HEADERDIR)/MLX42)

DEPS := $(OBJECTS:.o=.d)

vpath %.c $(SOURCEDIR)

# **************************************************************************** #
#    RULES
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCS) $^ $(LIBFTDIR)/$(LIBFTBIN) \
	$(MLXFLAGS) $(MLXDIR)/$(BUILDDIR)/$(MLXBIN) -o $(NAME)
	printf "$(V)$(B)Binary:$(T)$(Y) $(NAME) $(T)\n"

$(OBJECTS): $(LIBFTDIR)/$(LIBFTBIN)

$(LIBFTDIR)/$(LIBFTBIN): $(MLXDIR)/$(BUILDDIR)/$(MLXBIN)
	@make -C $(LIBFTDIR) all

$(MLXDIR)/$(BUILDDIR)/$(MLXBIN):
	@cmake $(MLXDIR) -B $(MLXDIR)/$(BUILDDIR) && \
	make -C $(MLXDIR)/$(BUILDDIR) -j4

libft: $(LIBFTDIR)/$(LIBFTBIN)

mlx: $(MLXDIR)/$(BUILDDIR)/$(MLXBIN)

run: all
	$(SCREENCLEAR)
	$(TESTCASE)

re: fclean
	make all

reb: fclean
	make bonus

debug: CFLAGS += $(DEBUGFLAGS)
debug: re

nm:
	$(foreach d, $(HEADERDIR), $(foreach h, $(wildcard $(d)/*), \
		norminette -R CheckDefine $(h);))
	$(foreach d, $(SOURCEDIR), $(foreach s, $(wildcard $(d)/**/*), \
		norminette -R CheckForbiddenSourceHeader $(s);))

leaks: all
	valgrind $(VLGFLAGS) $(TESTCASE)
	$(call report_cmd, $(LEAKSLOG))

define report_cmd
	$(SCREENCLEAR)
	cat $1 | tail -n +4 | cut --complement -d' ' -f1
endef

bonus: all

# **************************************************************************** #
#    BUILD
# **************************************************************************** #

define build_cmd
$1/%.o: %.c | $(BUILDDIR)
	if ! $(CC) $(CFLAGS) $(CPPFLAGS) $(INCS) $$< -o $$@ 2> $(BUILDLOG); then \
		printf "$(R)$(B)\nError: \
		$(V)Unable to create object file: \
		$(R)$(B)$$@$(Y)\n\n"; \
		sed '$$d' $(BUILDLOG); exit 1 ; \
	else \
		printf "$(C)$(B)Object: $(G)$$@ $(T)\n"; \
	fi
endef

# **************************************************************************** #
#    CLEAN
# **************************************************************************** #

clean:
	@make -C $(LIBFTDIR) fclean
	$(call delete_cmd, $(BUILDDIR), $(BUILDLOG), $(LEAKSLOG))

fclean: clean
	$(call delete_cmd, $(NAME))

define delete_cmd
	printf "$(R)$(B)Delete:$(T)$(Y)$1$2$3$4$5$(T)\n"
	$(RM) $1 $2 $3 $4 $5
endef

# **************************************************************************** #
#    COLORS
# **************************************************************************** #

T = \033[0m
B = \033[1m
G = \033[32m
V = \033[35m
C = \033[36m
Y = \033[33m
R = \033[31m

# **************************************************************************** #
#    UTILS
# **************************************************************************** #

-include $(DEPS)

$(BUILDDIR):
	mkdir -p $@

$(foreach build, $(BUILDDIR), $(eval $(call build_cmd, $(build))))

# **************************************************************************** #
#    PHONY
# **************************************************************************** #

.PHONY: all libft bonus re reb
.PHONY: mlx debug leaks nm run
.PHONY: clean fclean

.SILENT:
