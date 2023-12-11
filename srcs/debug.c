/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:57:09 by uminomae          #+#    #+#             */
/*   Updated: 2023/03/03 20:20:07 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	debug_lexer(t_shell *sh)
// {
// 	t_token	*token;

// 	token = sh->token_list.head;
// 	printf ("=== lex ===\n");
// 	while (token != NULL)
// 	{
// 		printf ("token:[%s]\tkind:[%d]\n", token->data, token->kind);
// 		token = token->next;
// 	}
// }

void	debug_inorder_stx_tree(t_st_node *node)
{
	if (node == NULL)
		return ;
	if (node->left != NULL)
		debug_inorder_stx_tree(node->left);
	if (node->kind == ST_OP_LIST || node->kind == ST_PIPE)
		printf("meta:[%s]\tkind:%d\t", node->data, node->kind);
	else if (node->kind != ST_IN_FILENAME && node->kind != ST_OUT_FILENAME && \
	node->kind != ST_HEREDOC_DELIMITER && node->kind != ST_OUT_ADD_FILENAME)
		printf("word:[%s]\tkind:%d\t", node->data, node->kind);
	else if (node->kind == ST_IN_FILENAME || node->kind == ST_OUT_FILENAME || \
		node->kind == ST_HEREDOC_DELIMITER || node->kind == ST_OUT_ADD_FILENAME)
		printf("file:[%s]\tkind:%d\t", node->data, node->kind);
	if (node->red_fd)
		printf("red_fd:[%d]\t", node->red_fd);
	if (node->parent)
		printf("parent:[%s]\n", node->parent->data);
	else
		printf("this node is top\n");
	if (node->right != NULL)
		debug_inorder_stx_tree(node->right);
}

void	debug_convert_char_dp(size_t count, size_t cmd_id, char **argv)
{
	size_t	i;

	i = 0;
	printf("\n=== convert to char **argv ===\n\n");
	while (i < count)
	{
		printf ("【cmd id %zu】argv[%zu]:%s\n", cmd_id, i, argv[i]);
		i++;
	}
	puts("");
}

void	debug_exe_cmdline(t_shell *sh, t_st_node *node)
{
	if (node->kind == ST_OP_LIST || node->kind == ST_PIPE)
		printf("meta:[%s]\n", node->data);
	else if (node->kind == ST_WORD)
	{
		printf("\x1b[38;5;198m");
		printf("word:[%s]\tkind:%d\tnum:%zu\tidx:%zu\targc:%zu\n", \
			node->data, node->kind, node->word_num, node->idx, sh->arg.argc);
		printf("\x1b[39;5;198m");
	}
	else if (node->kind == ST_IN_FILENAME || node->kind == ST_OUT_FILENAME || \
		node->kind == ST_HEREDOC_DELIMITER || node->kind == ST_OUT_ADD_FILENAME)
		printf("file:[%s]\tkind:%d\tidx:%zu\t\n", \
			node->data, node->kind, node->idx);
}

// void	print_token(t_token *tok)
// {
// 	int	kind;

// 	printf("\n===lexer token===\n\n");
// 	while (tok)
// 	{
// 		kind = tok->kind;
// 		printf("[%s]", tok->data);
// 		if (kind == TK_NONE)
// 			printf("\tkind: NONE\n");
// 		else if (kind == TK_WORD)
// 			printf("\tkind: WORD\n");
// 		else if (kind == TK_OP)
// 			printf("\tkind: OP\n");
// 		else if (kind == TK_OP_PIPE)
// 			printf("\tkind: OP_PIPE\n");
// 		else if (kind == TK_OP_LIST)
// 			printf("\tkind: OP_LIST\n");
// 		else if (kind == TK_RED)
// 			printf("\tkind: RED\n");
// 		else if (kind == TK_QUOTE)
// 			printf("\tkind: QUOTE\n");
// 		else if (kind == TK_DQUOTE)
// 			printf("\tkind: DQUOTE\n");
// 		else if (kind == TK_EOF)
// 			printf("\tkind: EOF\n");
// 		else if (kind == TK_TYPE_END)
// 			printf("\tkind: TYPE_END\n");
// 		else
// 			printf("lexerが悪いw\n");
// 		tok = tok->next;
// 	}
// 	printf("\n===lexer token===\n\n");
// }
