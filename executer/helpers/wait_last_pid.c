/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_last_pid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioulkhir <ioulkhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:09:18 by ioulkhir          #+#    #+#             */
/*   Updated: 2025/04/14 16:35:07 by ioulkhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void    wait_last_pid(pid_t last_pid)
{
    (void)last_pid;
    if (last_pid == 0)
        return ;
    // TODO
    // int        status;
    // pid_t    pid;

    // pid = waitpid(-1, &status, 0);
    // while (pid > 0)
    // {
    //     if (pid == *last_pid)
    //     {
    //         if (WIFEXITED(status))
    //             ft_set_exit_status(WEXITSTATUS(status));
    //         else if (WIFSIGNALED(status))
    //             ft_set_exit_status(128 + WTERMSIG(status));
    //     }
    //     pid = waitpid(-1, &status, 0);
    // }
    // restore_terminal_settings();
    // g_in_shell = 1;
}
