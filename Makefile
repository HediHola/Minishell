
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htizi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 15:14:35 by htizi             #+#    #+#              #
#    Updated: 2021/12/29 15:25:53 by htizi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		minishell
SRCS			=		minishell.c							\
						minishell_utils.c					\
						manage_list.c						\
						ms_substr.c							\
						operators.c							\
						char_is_valid.c						\
						expanser.c							\
						create_list.c						\
						utils.c								\
						tab.c								\
						free_tab.c							\
						patch.c								\
						del_quotes.c						\
						del_quotes_or_brackets.c			\
						isolate_var_in_list.c				\
						attribute_and_clear_type.c			\
						check_syntax.c						\
						merge_strings.c						\
						ft_list_last.c						\
						parser.c							\
						set_redir.c							\
						init_nodes.c						\
						nodes.c								\
						set_args_tab.c						\
						isolate_redir.c						\
						set_fd_lists.c						\
						builtin.c							\
						libft.c								\
						libft_2.c							\
						pwd_builtin.c						\
						echo_builtin.c						\
						cd_builtin.c						\
						env_builtin.c						\
						exit_builtin.c						\
						print_utils.c						\
						cmds_utils.c						\
						ft_split.c							\
						ms_itoa.c							\
						env.c								\
						env_utils.c							\
						export_builtin.c					\
						exit_free.c							\
						data.c								\
						files.c								\
						forking.c							\
						get_path.c							\
						get_cmd.c							\
						here_doc.c							\
						execve_error.c						\
						ft_signal.c							\
						ft_shlvl.c							\
						first_mid_last_forks.c				\
						export_utils.c						\
						get_next_line.c						\
						get_next_line_utils.c				\
						create_env.c						\
						unset.c								\
						heredoc_utils.c						\
						export.c							\

INC_DIR			=		./inc/
SRCS_DIR		=		srcs/
OBJS_DIR		=		objs/

OBJS			=		$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEP				=		${OBJS:.o=.d}

CC				=		clang
FLAGS			=		-Werror
FLAGS			+=		-Wall -Wextra -g3 -MMD -MP
FLAGS			+=		-I $(INC_DIR) -I /usr/local/opt/readline/include

all				:	$(NAME)

-include $(DEP)
$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
				@mkdir -p $(@D)
				$(CC) $(FLAGS) -c $< -o $@



$(NAME)			:	$(OBJS)
				$(CC) $(FLAGS) $(OBJS) -o $@ -lreadline -L /usr/local/opt/readline/lib
				@echo [$(NAME)] : Created !

clean			:
				rm -rf $(OBJS_DIR)
				@echo "[OBJS] Deleted"

fclean			:	clean
				rm -f $(NAME)
				@echo "[$(NAME)]: Deleted"

re				:	fclean all
