/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:35:12 by sponthus          #+#    #+#             */
/*   Updated: 2024/05/23 15:46:49 by sponthus         ###   ########lyon.fr   */
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

int	export_apply(t_data *data, char *name, char *val, bool add)
{
	t_env	*env_node;

	env_node = search_env_node(data->env, name);
	if (env_node)
	{
		if (export_replace_val(env_node, name, val, add) != 0)
			return (1);
	}
	else
	{
		if (check_var_name(name, "export") == 0)
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

char	*export_name(char *arg, char *equal, bool add, bool val)
{
	char	*name;

	if (val == true)
	{
		if (add == true)
			name = ft_substr(arg, 0, equal - arg - 1);
		else
			name = ft_substr(arg, 0, equal - arg);
		if (!name)
			return (NULL);
	}
	if (val == false)
	{
		name = ft_strdup(arg);
		if (!name)
			return (NULL);
	}
	return (name);
}

int	export_arg(t_data *data, char *arg)
{
	char	*name;
	char	*val;
	bool	add;

	add = false;
	val = ft_strchr(arg, '=');
	if (val > arg && *(val - 1) == '+')
		add = true;
	if (val != NULL && ft_strlen(arg) > 1 && val != arg)
	{
		name = export_name(arg, val, add, true);
		if (!name)
			return (1);
		val = ft_strdup(val + 1);
		if (!val)
			return (free(name), 1);
	}
	else
	{
		name = export_name(arg, val, add, false);
		if (!name)
			return (1);
		val = NULL;
	}
	return (export_apply(data, name, val, add));
}

	// if (val != NULL && ft_strlen(arg) > 1 && val != arg)
	// {
	// 	if (add == true)
	// 		name = ft_substr(arg, 0, val - arg - 1);
	// 	else
	// 		name = ft_substr(arg, 0, val - arg);
	// 	if (!name)
	// 		return (1);
	// 	val = ft_strdup(val + 1);
	// 	if (!val)
	// 		return (free(name), 1);
	// }
	// else
	// {
	// 	name = ft_strdup(arg);
	// 	if (!name)
	// 		return (1);
	// 	if (ft_strlen(arg) < 1 || val == arg)
	// 		val = NULL;
	// }

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
		if (export_print(data) != 0)
			return (1);
	}
	return (0);
}
