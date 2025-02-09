// test



#include "../minishell.h"

t_2_exec	*parser(int ac, char **av, t_env *my_env, t_garbage **my_garbage, char *line)
{
	t_2_exec	*head;
	t_2_exec	data;
	char		**cmds;
	int			i;

	if (line == NULL)
		return (NULL);
	cmds = ft_split(line, '|', my_garbage);
	i = 0;
	head = NULL;
	while (cmds[i])
	{
		data.cmd = ft_split(cmds[i++], ' ', my_garbage);
		ft_lstadd_back(&head, ft_lstnew(data, my_garbage), my_garbage);
	}
	return head;
}
