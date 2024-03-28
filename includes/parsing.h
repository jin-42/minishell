#ifndef PARSING_H
# define PARSING_H

typedef enum
  {
    TOKEN_EAT,
    TOKEN_DQ,
    TOKEN_SQ,
    TOKEN_SEMI,
    TOKEN_DBL_SEMI,
    TOKEN_OPERATOR,
    TOKEN_NEG,
    TOKEN_DBLAND,
    TOKEN_DBLOR,
    TOKEN_PIPE,
    TOKEN_OP_ARITHM,
    TOKEN_AND,
    TOKEN_OP_BRA,
    TOKEN_CL_BRA,
    TOKEN_OP_PAR,
    TOKEN_CL_PAR,
    TOKEN_REDIR,
    TOKEN_ASS_WORD,
    TOKEN_OP_CMD,
    TOKEN_OP_CURLY,
    TOKEN_CL_CURLY,
    TOKEN_EQUAL,
    TOKEN_STRING,
    TOKEN_NAME,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_NULL
  } e_token_type;


typedef struct s_oplist
{
  const char* op;
  uint32_t size;
  e_token_type type;
} t_oplist;

typedef struct s_lexer_token
{
  char *content; 
  uint32_t size;
  e_token_type type;
} t_lexer_token;

typedef struct s_lexer
{
  t_lexer_token *tokens;
  uint32_t size;
} t_lexer;

#endif 
