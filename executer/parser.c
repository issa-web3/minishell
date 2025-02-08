// test



#include "../minishell.h"

t_2_exec	*parser(int ac, char **av, t_env *my_env, char *line)
{
	t_2_exec	*head;
	t_2_exec	data;
	char		**cmds;
	// char		*cmds[5] = {"/bin/ls", "/bin/cat -e", "/bin/cat -e", "/bin/cat -e", NULL};
	// char		*cmds[3] = {"/bin/ls", "/bin/cat -e", NULL};
	int			i;

	cmds = ft_split(line, '|', NULL);
	if (cmds == NULL)
		perror("split1");
	i = 0;
	head = NULL;
	while (cmds[i])
	{
		data.cmd = ft_split(cmds[i++], ' ', NULL);
		if (data.cmd == NULL)
			perror("split2");
		ft_lstadd_back(&head, ft_lstnew(data));
	}
	return head;
}
