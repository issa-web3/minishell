#!/bin/bash

MINISHELL=./minishell 
LOGFILE=crash_log.txt   
OUTPUT_DIR=test_outputs 
ITERATIONS=1000        

touch "$LOGFILE"
mkdir -p "$OUTPUT_DIR"
COMMANDS=(
    "ls -la"
    "echo Hello world"
    "cd .."
    "pwd"
    "cat /etc/passwd"
    "grep root /etc/passwd"
    "ls | grep a"
    "ls > output.txt"
    "cat < input.txt"
    "export TEST=value"
    "env"
    "unset PATH"
    "echo $HOME"
    "echo $USER"
    "echo $PATH"
    "echo $PWD"
)

DIRS=("/" "/tmp" "/etc" "~" "." ".." "./src" "../include" "/usr/bin" "/usr/local")
FILES=("file1" "file2" "*.txt" "*.c" "/etc/passwd" "/dev/null" "Makefile" ".gitignore" "*.h" "*.o")
PIPES=("ls" "grep a" "wc -l" "sort" "uniq" "head" "tail" "sed 's/a/b/g'" "awk '{print \$1}'")
ENV_VARS=("HOME" "USER" "PATH" "PWD" "SHELL" "TERM" "LANG")

PIPE_COMMANDS=(
    "ls -la | grep d"
    "ls -la | grep d | wc -l"
    "cat /etc/passwd | grep root"
    "cat /etc/passwd | head -5 | tail -3"
    "echo hello | tr 'a-z' 'A-Z'"
    "ls | sort | uniq"
    "ls -la | grep -v ^d | wc -l"
    "ps | grep bash"
    "env | grep PATH"
    "ls -la | sort -k5 -n"
)

REDIRECTION_COMMANDS=(
    "ls > ls_output.txt"
    "cat < /etc/passwd"
    "ls -la > dir_content.txt"
    "echo hello > hello.txt"
    "cat < hello.txt > hello_copy.txt"
    "wc -l < /etc/passwd"
    "grep root < /etc/passwd > root_info.txt"
    "ls -la > results.txt 2> errors.txt"
    "ls non_existent_file 2> error.log"
    "cat < input.txt > output.txt"
)

ENV_COMMANDS=(
    "echo $HOME"
    "echo $USER"
    "echo $PATH"
    "echo $PWD"
    "echo My home is $HOME"
    "echo User: $USER, Shell: $SHELL"
    "echo $PATH | tr ':' '\n'"
    "echo Working directory: $PWD"
    "export TEST_VAR=hello_world"
    "export NEW_VAR=test && echo $NEW_VAR"
    "echo $TERM and $LANG"
    "echo $HOME/documents"
    "echo ${USER}_files"
    "export TEST_PATH=$HOME/bin:$PATH"
    "echo $NON_EXISTENT_VAR"
)

compare_outputs() {
    local cmd="$1"
    local test_num="$2"
    local bash_output_file="${OUTPUT_DIR}/bash_${test_num}.out"
    local bash_error_file="${OUTPUT_DIR}/bash_${test_num}.err"
    local mini_output_file="${OUTPUT_DIR}/mini_${test_num}.out"
    local mini_error_file="${OUTPUT_DIR}/mini_${test_num}.err"
    local bash_exit_code_file="${OUTPUT_DIR}/bash_${test_num}.exit"
    local mini_exit_code_file="${OUTPUT_DIR}/mini_${test_num}.exit"
    
    # Run in bash
    echo "$cmd" | bash > "$bash_output_file" 2> "$bash_error_file"
    echo $? > "$bash_exit_code_file"
    
    # Run in minishell
    echo "$cmd" | $MINISHELL > "$mini_output_file" 2> "$mini_error_file"
    local mini_exit="$?"
    echo $mini_exit > "$mini_exit_code_file"
    
    # Check for crashes
    if [ $mini_exit -gt 128 ]; then
        echo "[CRASH DETECTED] Test #$test_num with input: $cmd"
        echo "Test #$test_num: $cmd (Exit code: $mini_exit)" >> "$LOGFILE"
        echo "Crash detected. Check $LOGFILE for details."
        return 1
    fi
    
    # Display outputs
    echo "----------------------------------------"
    echo "Test #$test_num: $cmd"
    echo "----------------------------------------"
    echo "BASH OUTPUT:"
    cat "$bash_output_file"
    echo "----------------------------------------"
    echo "MINISHELL OUTPUT:"
    cat "$mini_output_file"
    echo "----------------------------------------"
    echo "BASH EXIT CODE: $(cat $bash_exit_code_file)"
    echo "MINI EXIT CODE: $(cat $mini_exit_code_file)"
    echo "----------------------------------------"
    echo
    
    return 0
}

echo "Starting minishell crash test with $ITERATIONS iterations..."
echo "Outputs will be saved in $OUTPUT_DIR directory"

for ((i = 1; i <= ITERATIONS; i++)); do
    if (( i % 4 == 0 )); then
        TEST_INPUT=${ENV_COMMANDS[$RANDOM % ${#ENV_COMMANDS[@]}]}
    elif (( i % 3 == 0 )); then
        TEST_INPUT=${REDIRECTION_COMMANDS[$RANDOM % ${#REDIRECTION_COMMANDS[@]}]}
    elif (( i % 2 == 0 )); then
        TEST_INPUT=${PIPE_COMMANDS[$RANDOM % ${#PIPE_COMMANDS[@]}]}
    elif (( i % 5 == 0 )); then
        NUM_PIPES=$((RANDOM % 3 + 1))  # 1-3 pipes
        COMPLEX_CMD=""
        
        for ((p = 0; p < NUM_PIPES; p++)); do
            PIPE_CMD=${PIPES[$RANDOM % ${#PIPES[@]}]}
            COMPLEX_CMD+="$PIPE_CMD"
            if (( p < NUM_PIPES - 1 )); then
                COMPLEX_CMD+=" | "
            fi
        done
        
        TEST_INPUT="$COMPLEX_CMD"
    elif (( i % 7 == 0 )); then
        CMD=${COMMANDS[$RANDOM % ${#COMMANDS[@]}]}
        ENV_VAR=${ENV_VARS[$RANDOM % ${#ENV_VARS[@]}]}
        TEST_INPUT="echo $"$ENV_VAR" > output_$"$ENV_VAR".txt"
    else
        TEST_INPUT=${COMMANDS[$RANDOM % ${#COMMANDS[@]}]}
    fi
    
    if (( i % 100 == 0 )); then
        echo "Progress: $i/$ITERATIONS"
    fi
    TEST_INPUT=$(echo "$TEST_INPUT" | sed 's/&&/;/g' | sed 's/||/;/g' | awk -F';' '{print $1}')
    compare_outputs "$TEST_INPUT" "$i" || exit 1
done

echo "Test completed: No crashes detected after $ITERATIONS iterations."
echo "All outputs have been saved to the $OUTPUT_DIR directory."