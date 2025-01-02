NAME = minishell

MAC =

MAC_B =

LIBFT = srcs/libft

FLAGS 	= -g3 -Wall -Wextra

LIB =  -L/usr/include -lreadline

SRCS =  	srcs/main_file/main.c											\
			srcs/main_file/free_main.c										\
			srcs/main_file/free_end_stc.c									\
			srcs/parsing/ft_is_builtin.c							\
			srcs/parsing/creat_fill_lst/get_cmd_line.c			\
			srcs/parsing/lst_fonction/cmdl_add_back.c			\
			srcs/parsing/lst_fonction/len_cmd.c					\
			srcs/parsing/parsing_utils.c							\
			srcs/parsing/free_utils.c							\
			srcs/parsing/free_utils_2.c							\
			srcs/parsing/creat_fill_lst/split_arg.c				\
			srcs/parsing/lst_fonction/init_token.c				\
			srcs/parsing/expend_word/expend_word.c				\
			srcs/parsing/expend_word/expend_word_utils.c			\
			srcs/parsing/expend_word/expend_word_utils_two.c		\
			srcs/parsing/expend_word/devellope_limitor.c			\
			srcs/parsing/expend_word/word_will_single.c			\
			srcs/parsing/expend_word/word_will_double.c			\
			srcs/parsing/expend_word/word_will_unquote.c			\
			srcs/parsing/get_env.c								\
			srcs/parsing/expend_word/fake_env.c					\
			srcs/parsing/expend_word/word_unquote_inter.c		\
			srcs/parsing/creat_fill_lst/organise_arg.c			\
			srcs/parsing/lst_fonction/token_add_back.c			\
			srcs/exec/ft_exec.c									\
			srcs/exec/ft_exist.c									\
			srcs/exec/ft_lst_to_str.c							\
			srcs/exec/pipe.c										\
			srcs/exec/open_fd.c									\
			srcs/exec/utils.c									\
			srcs/exec/exec_free_utils.c							\
			srcs/exec/exec_free_utils_two.c						\
			srcs/exec/exec_utils.c								\
			srcs/built_in/ft_add_value.c							\
			srcs/built_in/ft_built_in_export_fd.c				\
			srcs/built_in/ft_get_value.c							\
			srcs/built_in/ft_env_singletone.c					\
			srcs/built_in/ft_built_in.c							\
			srcs/built_in/ft_built_in_env_fd.c					\
			srcs/built_in/ft_built_in_echo.c						\
			srcs/built_in/ft_free_env.c							\
			srcs/built_in/ft_built_in_export.c					\
			srcs/built_in/ft_built_in_pwd.c						\
			srcs/built_in/ft_built_in_unset.c					\
			srcs/built_in/ft_built_in_cd.c						\
			srcs/built_in/ft_built_in_env.c						\
			srcs/built_in/ft_init_env.c							\
			srcs/built_in/ft_delete_key.c						\
			srcs/built_in/ft_gestion_error.c						\
			srcs/built_in/ft_built_in_pwd_fd.c					\
			srcs/built_in/ft_push_front.c						\
			srcs/built_in/ft_built_in_echo_fd.c					\
			srcs/built_in/builin_free.c							\
			srcs/limitor/creat_file.c							\
			srcs/limitor/open_heredoc.c

CC 		= gcc
OBJ 	= ${SRCS:.c=.o}
OBJS 	= *.o

all :
	@make -C $(LIBFT)
	@make $(NAME)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I include/

get_src:
	@find built_in -type f -name "*.c" | tr "\n" "|" | sed -r 's/["|"]+/\\ \n/g'


$(NAME)	: $(OBJ)
	$(CC) $(FLAGS) -I srcs/libft/includes/ -I include/. $(OBJ) srcs/libft/libft.a -o $(NAME) $(LIB)

clean :
		@make clean -C $(LIBFT)
		@rm -rf $(OBJ)

fclean : clean
		@rm -rf libft.a
		@make fclean -C $(LIBFT)
		@rm -rf $(OBJS)
		@rm -rf $(NAME)

re : fclean all

valgrind :
	 make && clear && valgrind --trace-children=yes --suppressions=valgrind_readline_leaks_ignore.txt -s --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell > resultat_valgrind.txt 2>&1 && echo $? || echo $?
