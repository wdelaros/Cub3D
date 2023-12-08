#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

NAME		=	cub3d
LIBFT		=	libft.a
LDIR		=	libft/

# Style
BOLD		=	\033[1m
ITALIC		=	\033[3m
UNDERLINE	=	\033[4m

# Color text
RESET		=	\033[0m
BLACK		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
PURPLE		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m
DEFAULT		=	\033[39m
ERASE_LINE	=	\033[2K\r

# Compiler and flags
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf

# Sources are all .c files
#base_file
#parsing
SRCS		=	cub3d.c \
				init_image.c \
				map.c \
				map_utils.c \
				parsing.c \
\
				parsing_data.c \
				parsing_data_utils.c \
				parsing_utils.c \
				valid_map.c \
\
				calculate.c\
				raycast.c \
				camera.c \
				error.c \
				utils.c \
				move.c \
				init.c \
				draw.c \

OBJS_DIR	=	obj/
OBJS_LST	=	$(patsubst %.c, %.o, $(SRCS))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LST))

#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: dependdown dir $(NAME)

# Generates output file
$(NAME): $(OBJS)
	@cd LIBFT/ && make && cd ..
	@printf "\n$(CYAN)MLX42: $(RESET)\n" && cd MLX42/ && make && cd ..
	@$(CC) $(CFLAGS) $(OBJS) MLX42/libmlx42.a $(LDIR)$(LIBFT) -I include -lglfw -L "$(shell brew --prefix glfw)/lib/" -o $(NAME) -g
	@echo "$(ERASE_LINE)$(GREEN)✔︎ $(ITALIC)$(NAME) successfully compile.$(RESET)\
	$(GREEN) ✔︎$(RESET)"

# Compiles sources into objects
$(OBJS_DIR)%.o: src/*/%.c
	@printf "$(ERASE_LINE)⚙️ $(PURPLE)Compiling $(DEFAULT)⚙️$(YELLOW) $(notdir $<)\
	$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

test:
	@$(CC) $(CFLAGS) src/raycaster.c src/error.c MLX42/libmlx42.a $(LDIR)$(LIBFT) -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

# install brew and glfw
dependdown:
	@if [ -x "$$HOME/homebrew/bin/brew" ] || [ -x "$$HOME/.brew/bin/brew" ]; then \
		echo "$(GREEN)✔︎ $(ITALIC)Brew is already installed$(RESET)$(GREEN) ✔︎$(RESET)"; \
	else \
		echo "$(RED)✗ $(ITALIC)Brew not found$(RESET)$(RED) ✗"; \
		read -p "Do you want to install brew? y/n: "  brewchoice; \
		printf "$(RESET)"; \
		if [ "$$brewchoice" = "y" ]; then \
			rm -rf $$HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $$HOME/.brew && \
			echo 'export PATH=$$HOME/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc && brew update; \
			echo "$(GREEN)✔︎ $(ITALIC)Brew successfully installed$(RESET)$(GREEN) ✔︎$(RESET)"; \
		else \
			echo "Exit"; \
			exit 2; \
		fi \
	fi
	@if [ -d "$$HOME/homebrew/opt/glfw/lib" ] || [ -d "$$HOME/.brew/opt/glfw/lib" ]; then \
		echo "$(GREEN)✔︎ $(ITALIC)glfw is already installed$(RESET)$(GREEN) ✔︎$(RESET)"; \
	else \
		echo "$(RED)✗ $(ITALIC)glfw not found$(RESET)$(RED) ✗"; \
		read -p "Do you want to install glfw? y/n: " glfwchoice; \
		printf "$(RESET)"; \
		if [ "$$glfwchoice" = "y" ]; then \
			brew install glfw; \
			echo "$(GREEN)✔︎ $(ITALIC)glfw successfully installed$(RESET)$(GREEN) ✔︎$(RESET)"; \
		else \
			echo "Exit"; \
			exit 2; \
		fi \
	fi

# create objects directory
dir:
	@mkdir -p $(OBJS_DIR)

# Removes objects
clean:
	@cd LIBFT/ && make clean && cd ..
	@printf "💣 $(RED)Removing MLX42 objects...$(RESET) 💥\n"
	@cd MLX42/ && make clean && cd ..
	@printf "💣 $(RED)Removing $(NAME) objects...$(RESET) 💥\n"
	@$(RM) $(OBJS_DIR)

# Removes objects and executables
fclean: clean
	@printf "💣 $(RED)Removing libft executable$(RESET) 💥\n"
	@$(RM) $(LDIR)$(LIBFT)
	@printf "💣 $(RED)Removing MLX42 executable$(RESET) 💥\n"
	@$(RM) MLX42/libmlx42.a
	@printf "💣 $(RED)Removing $(NAME) executable$(RESET) 💥\n"
	@$(RM) $(NAME)

# Removes objects and executables and remakes
re: fclean all
	@echo "$(ERASE_LINE)$(GREEN)✔︎ $(ITALIC)Remake complete$(RESET)\
	$(GREEN) ✔︎$(RESET)"
