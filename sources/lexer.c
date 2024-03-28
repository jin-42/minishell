#include <stdio.h>
#include <string.h>
#include <type.h>

// // Voici une explication détaillée du fonctionnement du lexer dans le contexte de Bash :

// //     Entrée : Le lexer prend en entrée une séquence de caractères, qui peut être un script 
// Bash ou une commande tapée directement dans le terminal.

// //     Division en jetons : Le lexer parcourt la séquence de caractères et 
// la divise en jetons, qui sont des unités lexicales de base ayant une signification particulière dans le langage. Dans le cas de Bash, les jetons peuvent être des mots-clés (comme 'if', 'then' ou 'else'), des identifiants (noms de variables ou de fonctions), des chaînes de caractères, des nombres, des opérateurs, des délimiteurs (comme les parenthèses ou les virgules) ou des symboles spéciaux (comme '&', '|' ou ';').

// //     Élimination des espaces blancs et des commentaires : Pendant la division en 
// jetons, le lexer ignore généralement les espaces blancs (espaces, tabulations et sauts de ligne) 
// et les commentaires, car ils ne font pas partie de la structure du langage et n'ont pas d'incidence sur l'exécution du script ou de la commande.

// //     Analyse des littéraux : Le lexer identifie également les littéraux présents dans l'entrée, 
// tels que les chaînes de caractères (délimitées par des guillemets simples ou doubles) et les nombres (entiers ou à virgule flottante).

// //     Gestion des caractères d'échappement : Dans certains cas, des caractères spéciaux 
// peuvent être précédés d'un antislash () pour indiquer au lexer qu'ils doivent être traités 
// comme des caractères littéraux plutôt que comme des délimiteurs ou des symboles spéciaux. Le lexer doit gérer correctement ces caractères d'échappement.

// //     Sortie : Une fois que tous les jetons ont été identifiés, le lexer transmet la liste des 
// jetons à l'analyseur syntaxique (parser), qui vérifie si la séquence de jetons forme une structure valide 
// dans le langage Bash et génère un arbre de syntaxe abstraite (AST) pour représenter la commande ou le script.




// Division en jetons 
#include <stdbool.h>
#include <stdlib.h>

typedef enum class bassh_operator {
    // Quote
    SIMPLE_QUOTE,
    DOUBLE_QUOTE,

    //EXPAND   
    VAR,
    //Redirection
    OPERATOR // REDIR PIPE

    END, // TOKEN END \0 HEREDOC
    
    //STRING
    STRING
} e_token_type;


typedef struct s_token {
    const char *str;
    e_token_type type;
    bool join;
    struct s_token *next;
} t_list;

t_list *_cp_simple_quote(char *s, int *i)
{
    int j;
    t_list *tok;

    j = *i;
    while ((s[j] != '\'') && s[j])
        j++;
    tok = malloc(sizeof(t_list));
    if (!tok)
        return NULL;
    tok->str = malloc(sizeof(char) * (1 + j));
    if (!tok->str)
        return free(tok), NULL;
    j = 0;
    while ((s[*i] != '\'') && s[*i])
    {
        tok->str[j] = s[*i];
        (*i)++;
        j++;
    }
    tok->type = STRING;
	tok->str[j] = '\0';
    return tok;
}

t_list *_cp_double_quote(char *s, int *i)
{
    int j;
    t_list *tok;

    j = *i;
    tok = malloc(sizeof(t_list));
    if (!tok)
        return NULL;
    while ((s[j] != '\"') && (s[j] != '$') && s[j])
        j++;
    tok->str = malloc(sizeof(char) * (1 + j));
    if (!tok->str)
        return free(tok), NULL;
    j = 0;
    while ((s[*i] != '\"') && (s[j] != '$') && s[*i])
    {
        if (s[*i] == '$')
            tok->type = VAR;
        tok->str[j] = s[*i];
        (*i)++;
        j++;
    }
    tok->type = STRING;
	tok->str[j] = '\0';
    return tok;
    //  expand vers le parsing
}

t_list *_cp_dollar(char *s, int *i)
{
	int j;
	t_list *tok;
	
	j = *i;
    tok = malloc(sizeof(t_list));
	if(!tok)
		return (NULL);
	while ((s[j] != '\"') && (s[j] != '\'') 
		&& (s[j] != ' ') && (s[j] != '|') && s[j] != '\0')
		j++;
	tok->str = malloc(sizeof(char) * (1 + j));
    if (!tok->str)
        return (free(tok), NULL);
    j = 0;
	while ((s[j] != '\"') && (s[j] != '\'') 
		&& (s[j] != ' ') && (s[j] != '|') && s[j] != '\0')
	{
        tok->str[j] = s[*i];
        (*i)++;
        j++;
    }
	tok->str[j] = '\0';
	tok->type = VAR;
	return tok;
}

t_token *_cp_pipe(char *s, int *i)
{
	t_list *tok;

	tok = malloc(sizeof(t_list));
	if(!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * 2);
	if (!tok->str)
        return (free(tok), NULL);
	tok->str[0] = '|';
	tok->str[1] = '\0';
	tok->type = OPERATOR
	(*i)+=1;
	return (tok);
}

t_token *_cp_redir(char *s, int *i)
{
	
}
void _lexer(char *s)
{
	int i;
	t_list *token;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			ft_lstadd_back(&token, _cp_simple_quote(s, &i));
		else if (s[i] == '\"')
			ft_lstadd_back(&token, _cp_double_quote(s, &i));
		else if (s[i] == '$')
			ft_lstadd_back(&token, _cp_dollar(s, &i));
		else if (s[i] == '|')
			ft_lstadd_back(&token, _cp_pipe(s, &i));
		else if (s[i]  == '<' || s[i] == '>')
			
		else
			// espace
		i++;
	}
} 



// EXPSND VERS PSRSING