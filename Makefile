#=============================
#flags
#=============================
NAME		:= minishell
CC			:= cc 
RM			:= rm -f
CFLAGS		:= -Wall -Wextra -Werror -O 
DFLAGS		:= -MMD -MP
LFLAGS      := -lreadline -lhistory -L$(shell brew --prefix readline)/lib
#=============================
#src
#=============================
# VPATH = srcs:srcs/UTIL
SRCDIR    = srcs
SRCS	:= 	\
srcs/sig.c \
srcs/endline.c \
srcs/exe/ft_execvp.c \
srcs/exe/ft_get_abs_path.c \
srcs/util/util_malloc.c \
srcs/util/ft_strtol.c \
srcs/util/util_free_list.c \
srcs/util/util_libft.c \
srcs/util/util_classify.c \
srcs/init.c \
srcs/parse/lexer2.c \
srcs/parse/tree_util.c \
srcs/parse/lexer1.c \
srcs/parse/lexer_util2.c \
srcs/parse/parser.c \
srcs/parse/lexer_util1.c \
srcs/builtin/env_make.c \
srcs/builtin/env_edit_func.c \
srcs/exe/wait_pid.c \
srcs/exe/exe_func.c \
srcs/exe/expansion.c \
srcs/exe/expansion_sub.c \
srcs/exe/dequotes.c \
srcs/exe/restore_stdio.c \
srcs/exe/heredoc.c \
srcs/exe/open_io_file.c \
srcs/exe/cmdline.c \
srcs/exe/cmd_elem.c \
srcs/exe/exe_prepare.c \
srcs/exe/cmd_pipe.c \
srcs/exe/cmd_single.c \
srcs/builtin/exit.c \
srcs/builtin/unset.c \
srcs/builtin/env.c \
srcs/builtin/pwd.c \
srcs/builtin/export.c \
srcs/builtin/cd.c \
srcs/builtin/echo.c \
srcs/builtin/declare.c \
srcs/minishell.c

# find srcs -type  f -name '*.c'
#=============================
#directory
#=============================
PARSE_DIR	= srcs/parse
UTIL_DIR	= srcs/util
EXE_DIR		= srcs/exe
BUILTIN_DIR = srcs/builtin
ENV_DIR 	= srcs/env
# ------
INCDIR		= include/
INCLUDE		= -I$(INCDIR) -I $(shell brew --prefix readline)/include
OBJDIR		= obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR	= .
endif
OBJECTS    :=  $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCS:%.c=%.o))
DEPENDS    :=  $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCS:%.c=%.d))
LIBDIR		= libft
LIBFT		= $(LIBDIR)/libft.a
#=============================
#rule
#=============================
all: $(NAME) 

$(NAME): $(OBJECTS) $(LIBFT)
	@echo $(BLUE)"----- $(NAME) $(CC) start-----"$(RESET)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(INCLUDE) $(MFLAGS) $(LFLAGS)
	@echo $(GREEN)"----- $(NAME) $(CC) done-----"$(RESET)
	@echo $(SKYBLUE) "make .o" $(RESET)
#-----
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	 -mkdir -p $(@D) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@ 


$(LIBFT): FORCE
	$(MAKE) -C $(LIBDIR)
	@echo $(GREEN)"----- $(LIBFT) $(CC) done-----"$(RESET)
FORCE:



clean:
	$(MAKE) clean -C $(LIBDIR)
	@echo $(YELLOW)"----- $(LIBFT) clean done-----"$(RESET)
	$(RM) $(OBJECTS) $(DEPENDS)
	@echo $(YELLOW)"----- $(NAME) clean done-----"$(RESET)

fclean:	clean
	# $(MAKE) fclean -C $(LIBDIR)
	@echo $(RED)"----- $(LIBFT) fclean done-----"$(RESET)
	$(RM) $(NAME)
	@echo $(RED)"----- $(NAME) fclean done-----"$(RESET)

re: fclean all

-include $(DEPENDS)

#=============================
#make option
#=============================
s:	CFLAGS +=  -g  -fsanitize=address -fsanitize=undefined 
s:	re
	bash test_all.sh
run: 
	make re
	./minishell
	
m:
	make
	bash test_assert.sh

c:
	make 
	bash test_all.sh

v: 
	make
	valgrind --tool=memcheck --leak-check=yes ./minishell
# valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all clean fclean re bonus sani run sani2

#=============================
#color
#=============================
RED			=	"\033[31m"
GREEN		=	"\033[32m"
YELLOW		=	"\033[33m"
BLUE		=	"\033[34m"
PURPLE		=	"\033[35m"
SKYBLUE		=	"\033[36m"
RESET		=	"\033[0m"