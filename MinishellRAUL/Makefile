# **************************************************************************** #
#                                   Minishell                                  #
# **************************************************************************** #

NAME        := minishell

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

# ---- Folders ----
INC_DIR     := inc
SRC_DIR     := src
OBJ_DIR     := obj

# ---- Libft (inside inc/) ----
LIBFT_DIR   := $(INC_DIR)/libft
LIBFT_A     := $(LIBFT_DIR)/libft.a

# ---- Includes ----
INCLUDES    := -I$(INC_DIR) -I$(LIBFT_DIR)

# ---- Sources ----
SRCS        := $(SRC_DIR)/main.c \
               $(SRC_DIR)/signals.c \
               $(SRC_DIR)/env/env_init.c \
               $(SRC_DIR)/env/env_ops.c \
               $(SRC_DIR)/env/env_utils.c \
               $(SRC_DIR)/lexer/tokenize.c \
               $(SRC_DIR)/lexer/token_utils.c \
               $(SRC_DIR)/lexer/syntax_check.c \
               $(SRC_DIR)/expander/expander.c \
               $(SRC_DIR)/expander/expander_utils.c \
               $(SRC_DIR)/parser/parser.c \
               $(SRC_DIR)/parser/parser_utils.c \
               $(SRC_DIR)/builtins/builtins.c \
               $(SRC_DIR)/builtins/builtin_echo.c \
               $(SRC_DIR)/builtins/builtin_cd.c \
               $(SRC_DIR)/builtins/builtin_pwd.c \
               $(SRC_DIR)/builtins/builtin_export.c \
               $(SRC_DIR)/builtins/builtin_unset.c \
               $(SRC_DIR)/builtins/builtin_env.c \
               $(SRC_DIR)/builtins/builtin_exit.c \
               $(SRC_DIR)/executor/executor.c \
               $(SRC_DIR)/executor/pipeline.c \
               $(SRC_DIR)/executor/redirections.c \
               $(SRC_DIR)/executor/heredoc.c \
               $(SRC_DIR)/executor/path_resolve.c \
               $(SRC_DIR)/executor/exec_utils.c \
               $(SRC_DIR)/utils/free_utils.c \
               $(SRC_DIR)/utils/utils.c

OBJS        := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# ---- Readline (Linux) ----
# Many Linux setups need ncurses; some need tinfo. We try both safely.
READLINE_LIBS := -lreadline

# Test if -ltinfo is available; otherwise fallback to -lncurses
TINFO_OK := $(shell printf 'int main(){return 0;}\n' | $(CC) -x c - -ltinfo -o /tmp/.tinfo_test 2>/dev/null && echo yes)
ifeq ($(TINFO_OK),yes)
	TERM_LIB := -ltinfo
else
	TERM_LIB := -lncurses
endif

# ---- Rules ----
all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(READLINE_LIBS) $(TERM_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
