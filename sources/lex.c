#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	// Quote
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,

	// EXPAND
	VAR,
	// Redirection
	OPERATOR, // REDIR PIPE
	END,      // TOKEN END  HEREDOC
	STRING
}					e_token_type;

typedef struct s_token
{
	char			*str;
	e_token_type	type;
	struct s_token	*next;
}					t_list;

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	return ;
}

t_list	*_cp_simple_quote(char *s, int *i)
{
	int		j;
	t_list	*tok;

	j = *i;
	while ((s[j] != '\'') && s[j])
		j++;
	tok = malloc(sizeof(t_list));
	if (!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * (1 + j));
	if (!tok->str)
		return (free(tok), NULL);
	j = 0;
	while ((s[*i] != '\'') && s[*i])
	{
		tok->str[j] = s[*i];
		(*i)++;
		j++;
	}
	tok->str[j] = '\0';
	tok->type = STRING;
	return (tok);
}

t_list	*_cp_double_quote(char *s, int *i)
{
	int		j;
	t_list	*tok;

	j = *i;
	tok = malloc(sizeof(t_list));
	if (!tok)
		return (NULL);
	while ((s[j] != '\"') && (s[j] != '$') && s[j])
		j++;
	tok->str = malloc(sizeof(char) * (1 + j));
	if (!tok->str)
		return (free(tok), NULL);
	j = 0;
	while ((s[*i] != '\"') && (s[j] != '$') && s[*i])
	{
		if (s[*i] == '$')
			tok->type = VAR;
		tok->str[j] = s[*i];
		(*i)++;
		j++;
	}
	tok->str[j] = '\0';
	tok->type = STRING;
	return (tok);
}

t_list	*_cp_dollar(char *s, int *i)
{
	int		j;
	t_list	*tok;

	j = *i;
	tok = malloc(sizeof(t_list));
	if (!tok)
		return (NULL);
	while ((s[j] != '\"') && (s[j] != '\'') && (s[j] != ' ') && (s[j] != '|')
			&& s[j] != '\0')
		j++;
	tok->str = malloc(sizeof(char) * (1 + j));
	if (!tok->str)
		return (free(tok), NULL);
	j = 0;
	while ((s[j] != '\"') && (s[j] != '\'') && (s[j] != ' ') && (s[j] != '|')
			&& s[j] != '\0')
	{
		tok->str[j] = s[*i];
		(*i)++;
		j++;
	}
	tok->str[j] = '\0';
	tok->type = VAR;
	return (tok);
}

t_list	*_cp_pipe(int *i)
{
	t_list	*tok;

	tok = malloc(sizeof(t_list));
	if (!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * 2);
	if (!tok->str)
		return (free(tok), NULL);
	tok->str[0] = '|';
	tok->str[1] = '\0';
	tok->type = OPERATOR;
	(*i) += 1;
	return (tok);
}

t_list	*_cp_redir(char *s, int *i)
{
	t_list	*tok;

	tok = malloc(sizeof(t_list));
	if (!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * 2);
	if (!tok->str)
		return (free(tok), NULL);
	tok->str[0] = s[*i];
	tok->str[1] = '\0';
	tok->type = OPERATOR;
	(*i) += 1;
	return (tok);
}

t_list	*_cp_space(char *s, int *i)
{
	int		j;
	t_list	*tok;

	j = *i;
	tok = malloc(sizeof(t_list));
	if (!tok)
		return (NULL);
	while ((s[j] != '\"') && (s[j] != '\'') && (s[j] != ' ') && (s[j] != '|')
			&& (s[j] != '\0'))
		j++;
	printf("%d", j);
	tok->str = malloc(sizeof(char) * (j));
	if (!tok->str)
		return free(tok), NULL;
	j = 0;
	while ((s[j] != '\"') && (s[j] != '\'') && (s[j] != ' ') && (s[j] != '|')
			&& (s[j] != '\0'))
	{
		printf("a");
		tok->str[j] = s[*i];
		j++;
		(*i)++;
	}
	tok->str[j] = '\0';
	tok->type = STRING;
	tok->next = NULL;
	return tok;
}

t_list	*_lexer(char *s)
{
	int		i;
	t_list	*token;

	i = 0;
	token = NULL;
	while (s[i])
	{
		if (s[i] == '\'')
			ft_lstadd_back(&token, _cp_simple_quote(s, &i));
		else if (s[i] == '\"')
			ft_lstadd_back(&token, _cp_double_quote(s, &i));
		else if (s[i] == '$')
			ft_lstadd_back(&token, _cp_dollar(s, &i));
		else if (s[i] == '|')
			ft_lstadd_back(&token, _cp_pipe(&i));
		else if (s[i] == '<' || s[i] == '>')
			ft_lstadd_back(&token, _cp_redir(s, &i));
		else
			ft_lstadd_back(&token, _cp_space(s, &i));
	}
	return token;
}

void	print_tokens(t_list *tokens)
{
	t_list	*current;

	current = tokens;
	while (current != NULL)
	{
		printf("Token: %s\n", current->str);
		current = current->next;
	}
}

int	main(void)
{
	char	input[] = "echo bonj";
	t_list	*tokens;

	tokens = NULL;
	tokens = _lexer(input);
	print_tokens(tokens);
	return 0;
}
