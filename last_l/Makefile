NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb
LDFLAGS = -lm -lz -L$(MLX) -lmlx_Linux -lXext -lX11

SRCDIR = src
BONUSDIR = src_bonus
LIBFTDIR = Libft
MLX = minilibx-linux

MANDATORY_SRCS = $(SRCDIR)/main.c \
                 $(SRCDIR)/parsing_1.c \
                 $(SRCDIR)/parsing_2.c \
                 $(SRCDIR)/parsing_3.c \
                 $(SRCDIR)/helper_fun.c \
                 $(SRCDIR)/execution.c \
                 $(SRCDIR)/execution_1.c \
                 $(SRCDIR)/execution_2.c \

BONUS_SRCS = $(BONUSDIR)/main_bonus.c \
             $(BONUSDIR)/execution_bonus.c \
             $(BONUSDIR)/execution_1_bonus.c \
             $(BONUSDIR)/execution_2_bonus.c \
             $(BONUSDIR)/parsing_1_bonus.c \
             $(BONUSDIR)/parsing_2_bonus.c \
             $(BONUSDIR)/parsing_3_bonus.c \
             $(BONUSDIR)/helper_fun_bonus.c

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT = $(LIBFTDIR)/libft.a
MLX_LIB = $(MLX)/libmlx_Linux.a

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(LIBFT) $(MLX) $(MANDATORY_OBJS)
	$(CC) $(MANDATORY_OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

bonus: $(LIBFT) $(MLX) $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFTDIR)

$(MLX):
	@make -C $(MLX)

%.o: %.c
	$(CC) $(CFLAGS) -I$(SRCDIR) -I$(BONUSDIR) -I$(LIBFTDIR) -I$(MLX) -O3 -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	@make -C $(LIBFTDIR) clean
	@make -C $(MLX) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean
	@make -C $(MLX) clean

re: fclean all

