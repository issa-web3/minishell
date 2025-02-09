# cc executer/built-ins/src/echo.c utils/*.c -o executer/built-ins/obj/echo
# cc executer/built-ins/src/exit.c utils/*.c -o executer/built-ins/obj/exit
# cc executer/built-ins/src/pwd.c utils/*.c -o executer/built-ins/obj/pwd
# cc executer/built-ins/src/env.c utils/*.c -o executer/built-ins/obj/env

cc *.c utils/*.c executer/*.c executer/get_path/*.c executer/helpers/*.c executer/built-ins/*.c garbage/*.c -lreadline -o minishell && ./minishell