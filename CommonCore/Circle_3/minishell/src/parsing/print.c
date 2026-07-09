/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:35:53 by staverni          #+#    #+#             */
/*   Updated: 2025/05/19 10:58:35 by mpoesy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void print_indent(int level)
{
	for (int i = 0; i < level; ++i)
		printf("  ");
}

void print_cmd_tree(t_cmd *cmd, int indent)
{
	if (!cmd)
	{
		print_indent(indent);
		printf("(null)\n");
		return;
	}

	print_indent(indent);

	switch (cmd->type)
	{
		case CMD:
			printf("CMD:\n");
			for (int i = 0; i < cmd->u.exec.argc; ++i)
			{
				if (i == 0)
				{
					print_indent(indent + 1);
					printf("path: %s\n", cmd->u.exec.path);
				}
				print_indent(indent + 1);
				printf("arg[%d]: %s\n", i, cmd->u.exec.argv[i]);
			}
			break;

		case PIPE:
			printf("PIPE:\n");
			print_indent(indent + 1);
			printf("Left:\n");
			print_cmd_tree(cmd->u.pipe.left, indent + 2);
			print_indent(indent + 1);
			printf("Right:\n");
			print_cmd_tree(cmd->u.pipe.right, indent + 2);
			break;

		case REDIR_IN:
			printf("REDIR_IN < : %s\n", cmd->u.redir.file);
			print_indent(indent + 1);
			printf("Cmd:\n");
			print_cmd_tree(cmd->u.redir.cmd, indent + 2);
			break;

		case REDIR_OUT:
			printf("REDIR_OUT > : %s\n", cmd->u.redir.file);
			print_indent(indent + 1);
			printf("Cmd:\n");
			print_cmd_tree(cmd->u.redir.cmd, indent + 2);
			break;

		case REDIR_APPEND:
			printf("REDIR_APPEND >> : %s\n", cmd->u.redir.file);
			print_indent(indent + 1);
			printf("Cmd:\n");
			print_cmd_tree(cmd->u.redir.cmd, indent + 2);
			break;

		case REDIR_HEREDOC:
			printf("REDIR_HEREDOC << : %s\n", cmd->u.redir.file);
			print_indent(indent + 1);
			printf("Cmd:\n");
			print_cmd_tree(cmd->u.redir.cmd, indent + 2);
			break;

		default:
			print_indent(indent);
			printf("UNKNOWN TYPE: %d\n", cmd->type);
			break;
	}
}
*/
