/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:35:12 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/25 13:44:32 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Sans options : affiche env dans l'ordre ASCII, avec les variables sans valeur, met des "" autour de la valeur
// Avec option : ajoute l'option au contenu
// Si on a un = la cree gentiment, meme si contenu estnul
// Si il n y a pas de = ajoute le nom sans contenu assoie donc pas de =""
// Si plusieurs arg traite tous les arg individuellement ...
// Accepte en 1er caractere un alpha ou unixcase, pas un chiffre

// prend en compte arg[0] = export
// a verifier avec la PEC de plusieurs args

// ATTENTION : ajouter le fait que i on a VAL="    hey le monde    " on enleve les espaces a la fin et au debut

int	check_name(char *name, char *f)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) == 1 || ft_strlen(name) == 0)
	{
		printf("%s: `%s': not a valid identifier\n", f, name);
		return (1);
	}
	while (name[i])
	{
		if (ft_strchr(EXP_CHAR, name[i]) == NULL)
			return (printf("%s: `%s': not a valid identifier\n", f, name), 1);
		i++;
	}
	return (0);
}

int	apply_export(t_data *data, char *name, char *val)
{
	t_env	*env_node;

	env_node = search_env_node(data->env, name);
	if (env_node)
	{
		free(env_node->val);
		env_node->val = val;
		env_node->val_len = ft_strlen(val);
		free(name);
	}
	else
	{
		if (check_name(name, "export") == 0)
			return (env_add_back(&data->env, env_new(val, name)));
		else
		{
			free(name);
			free(val);
			return (1);
		}
	}
	return (0);
}

int	export_arg(t_data *data, char *arg)
{
	char	*name;
	char	*val;

	val = ft_strchr(arg, '=');
	if (val != NULL && ft_strlen(arg) > 1 && val != arg)
	{
		name = ft_substr(arg, 0, val - arg);
		if (!name)
			return (1);
		val = ft_strdup(val + 1);
		if (!val)
			return (free(name), 1);
	}
	else
	{
		name = ft_strdup(arg);
		if (!name)
			return (1);
		if (ft_strlen(arg) <= 1 || val == arg)
			val = NULL;
	}
	return (apply_export(data, name, val));
}

int	print_export(t_data *data)
{
	char	**names;
	t_env	*env;
	int		i;

	i = 0;
	names = sort_env(data);
	if (names == NULL)
		return (1);
	while (names[i])
	{
		env = search_env_node(data->env, names[i]);
		printf("declare -x %s", env->name);
		if (env->val)
			printf("=\"%s\"\n", env->val);
		else
			printf("\n");
		i++;
	}
	free(names);
	return (0);
}

int	export(t_data *data, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (args[i] && export_arg(data, args[i]) != 0)
			return (1);
		i++;
	}
	if (i == 1)
	{
		if (print_export(data) != 0)
			return (1);
	}
	return (0);
}
