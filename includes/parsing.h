#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>


typedef enum e_bash_op
{
	VAR = 0,
	VAR_IN_QUOTE,
	OP,
	STRING
} e_token_type;

typedef struct s_token
{
	char *str;
	e_token_type type;
	struct s_token *next;
} t_list;

typedef struct s_inter
{
	char			**arr;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	char			*append;
	struct s_inter	*next;
}					t_inter;


t_inter	*_parse(t_list **token);
void _print_inter(const t_inter *node);
t_inter *_parse_add_back(t_list **token);
#endif 
