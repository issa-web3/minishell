#!/bin/bash

MINISHELL=./minishell  # Path to your minishell executable
LOGFILE=crash_log.txt   # File to store crashes
ITERATIONS=100          # Number of test cases before stopping

for ((i = 1; i <= ITERATIONS; i++)); do
    TEST_INPUT=$(head -c $((RANDOM % 100 + 1)) /dev/urandom | tr -dc '[:print:]')
    
    echo "$TEST_INPUT" | $MINISHELL >/dev/null 2>&1
    
    if [ $? -gt 128 ]; then  # Segfault or abnormal termination
        echo "[CRASH DETECTED] Input: $TEST_INPUT"
        echo "$TEST_INPUT" >> "$LOGFILE"
        exit 1
    fi
done

echo "Test completed: No crashes detected after $ITERATIONS iterations."
