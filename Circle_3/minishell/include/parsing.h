/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staverni <staverni@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:38:32 by staverni          #+#    #+#             */
/*   Updated: 2025/05/15 20:48:02 by staverni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/********************************** DEFINES ***********************************/

# define MAX_ARGS 4096
# define WHITESPACES " \t\n"
# define ESCAPABLE_CHARS "$\\\""
# define METACHARS "|<>&();"

typedef enum e_toktype
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_UNKNOWN
}					t_toktype;

typedef struct s_token
{
	t_toktype		type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef enum e_cmdtype
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	SEMICOLON,
	AND,
	OR
}					t_cmdtype;

// for CMD type
typedef struct s_execcmd
{
	int				argc;
	char			*argv[MAX_ARGS];
	char			*path;
}					t_execcmd;

// for PIPE, AND, OR, SEMICOLON types
typedef struct s_binopcmd
{
	struct s_cmd	*left;
	struct s_cmd	*right;
}					t_pipecmd;

// for REDIR_IN, REDIR_OUT, REDIR_APPEND types
typedef struct s_redircmd
{
	struct s_cmd	*cmd;
	char			*file;
}					t_redircmd;

typedef struct s_cmd
{
	t_cmdtype		type;
	union			u_cmd
	{
		t_execcmd	exec;
		t_pipecmd	pipe;
		t_redircmd	redir;
	} u;
}					t_cmd;

void				print_token(t_token *token);
char				*read_input(t_list *env);

/********************************** LEXER *************************************/

char				*find_closing_quote(char *input, char quote);
int					is_supported_metachar(const char *c);
int					max_metachar_len(char c);
t_token				*extract_metachar(char **input);
t_token				*get_next_token(char **input);
t_token				*lexer(char *input);
char				*find_closing_single_quote(char *p_after);

/********************************* TOKENS *************************************/

t_token				*create_token(t_toktype type, char *value, size_t len);
char				*token_value(t_toktype type);
t_toktype			token_type(char *value);
void				free_token(t_token *head);
void				replace_token(t_token *token, char *new_value);
void				ft_token_iter(t_token *lst, void (*f)(t_token *));
void				ft_token_add_back(t_token **alst, t_token *new);

/******************************** EXPANDER ***********************************/

void				expand(t_token *tokens, t_list *env);
void				expander(t_token *token, t_list *env);
char				*expand_single_quote(char *token);
int					expand_single_quote_loop(t_buffer *buf, char *p);
char				*expand_double_quote(char *token, t_list *env);
int					expand_double_quote_loop(t_buffer *buf, char *p,
						t_list *env);
char				*expand_word(char *token, t_list *env);
size_t				get_dollar_len(const char *token_start);
char				*dollar_expansion(char *token, t_list *env);
char				*backslash_expansion(char *p, int in_quotes);
size_t				apply_dollar_expansion(t_buffer *buf, char *token,
						t_list *env);
size_t				apply_backslash_expansion(t_buffer *buf, char *token,
						int quotes);
char				*expand_unquoted(char *token, t_list *env);

/********************************* PARSER *************************************/

void				print_cmd_tree(t_cmd *cmd, int indent);
t_cmd				*parse_line(t_token *tokens);
t_cmd				*parse_exec(t_token **tokens);
t_cmd				*parse_pipe(t_token **tokens);
int					token_is_redir(t_toktype type);
int					node_is_redir(t_cmdtype t);
t_cmd				*parse_redirect(t_token **tokens);
// t_cmd		*parse_binop(t_token **tokens);
void				free_cmd_tree(t_cmd *cmd);

/******************************* VALIDATION ***********************************/

int					pre_validate(t_token *tokens);
int					post_validate(t_cmd *tree, t_list *env);
int					is_builtin(char *cmd);
void				test_perms(char *file_path);

#endif
