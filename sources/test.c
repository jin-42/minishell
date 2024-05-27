#include "../includes/minishell.h"

void	print_data(t_data *data)
{
	int		i;

	printf("cmd_count = %d\n\n", data->cmd_count);
	printf("ret_val = %d\n\n", data->ret_val);

	t_env *env = data->env; // --------------------------------- PRINT ENVIRONNEMENT
	i = 0;
	// while (data->env && env != 0) 
	// {
	// 	printf("Env nb %d : \n - name (len %d) /%s/ \n - val (len %d) --%s--\n", i,  env->name_len, env->name, env->val_len, env->val);
	// 	printf("node address %x / next = %x \n\n", env, env->next);
	// 	env = env->next;
	// 	i++;
	// }
	printf("\n\n");

	i = 0; // ------------------------------------------ PRINT PATHS
	// while (data->paths && data->paths[i])
	// {
	// 	printf("path %d = --%s--\n", i, data->paths[i]);
	// 	i++;
	// }
	// printf("\n\n");

	t_block *block; // ------------------------------------------ PRINT BLOCKS
	if (data->block)
	{
		block = data->block;
		while (block)
		{
			printf("-- NEW BLOCK %x --\n\n", block);
			printf("in_fd = %d / out_fd = %d\n", block->in_fd, block->out_fd);
			printf("bools : here_doc %d / builtin %d \n", block->here_doc, block->builtin);
			printf("path = %s (should be NULL before exec) \n args (first one is the command, rest is args) :\n", block->path);
			i = 0;
			while (block->args && block->args[i])
			{
				printf("   (%d) = /%s/\n", i, block->args[i]);
				i++;
			}
			printf("next block = %x\n", block->next);
			block = block->next;
		}
	}
	printf("\n\n");
}


void print_block(t_block *block) {

while(block != NULL)
{
    printf("in_fd: %d\n", block->in_fd);
    printf("out_fd: %d\n", block->out_fd);
    printf("here_doc: %s\n", block->here_doc ? "true" : "false");
    printf("hd_quote: %s\n", block->hd_quote ? "true" : "false");
    printf("limiter: %s\n", block->limiter != NULL ? block->limiter : "NULL");
	for (int i = 0; block->args[i] != NULL; ++i) {
        printf("agrs[%i] = //%s//\n",i, block->args[i]);
    }
	printf("\n");
	block = block->next;
}
}
