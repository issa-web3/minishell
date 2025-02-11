// test



#include "../minishell.h"

t_2_exec	*parser(int ac, char **av, t_env *my_env, t_garbage **my_garbage, char *line)
{
	t_2_exec	*head;
	t_2_exec	data;
	char		**cmds;
	int			i;
	int			j;

	if (line == NULL)
		return (NULL);
	cmds = ft_split(line, '|', my_garbage);
	i = 0;
	head = NULL;
	while (cmds[i])
	{
		data.cmd = ft_split(cmds[i++], ' ', my_garbage);
		j = 0;
		data.infile = NULL;
		data.outfile = NULL;
		data.append = 0;
		while (data.cmd && data.cmd[j])
		{
			if (ft_strcmp(data.cmd[j], "<") == 0)
				(data.infile = data.cmd[j + 1], data.cmd[j] = NULL);
			else if (ft_strcmp(data.cmd[j], ">") == 0)
				(data.outfile = data.cmd[j + 1], data.cmd[j] = NULL);
			else if (ft_strcmp(data.cmd[j], ">>") == 0)
				(data.outfile = data.cmd[j + 1], data.cmd[j] = NULL, data.append = 1);
			j++;
		}
		ft_lstadd_back(&head, ft_lstnew(data, my_garbage), my_garbage);
	}
	return head;
}
