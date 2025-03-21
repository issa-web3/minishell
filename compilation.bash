




cc -Wall -Wextra -Werror *.c */*.c */*/*.c  -L/home/kali/.brew/opt/readline/lib -I/home/kali/.brew/opt/readline/include -lreadline -o minishell && ./minishell