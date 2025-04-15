




cc *.c */*.c */*/*.c  */*/*/*.c  -L/home/kali/.brew/opt/readline/lib -I/home/kali/.brew/opt/readline/include -g -fsanitize=address -lreadline -o minishell && ./minishell