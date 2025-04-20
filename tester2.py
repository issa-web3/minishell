#!/usr/bin/env python3
"""
Minishell Tester - A comprehensive testing tool for the minishell project.
This script tests various aspects of the minishell shell implementation,
comparing its output with bash.
"""

import subprocess
import os
import sys
import argparse
import time
from pathlib import Path
from minishell_tests import *

TEST_DIR = "/tmp/minishell_test"

class Color:
    """ANSI color codes for terminal output"""

    RED = "\033[1;31m"
    GREEN = "\033[1;32m"
    YELLOW = "\033[1;33m"
    BLUE = "\033[1;34m"
    PURPLE = "\033[1;35m"
    CYAN = "\033[0;36m"
    BOLD = "\033[1m"
    RESET = "\033[0m"


class TestResult:
    def __init__(self):
        self.total = 0
        self.passed = 0
        self.failed = 0
        self.failures = []

    def add_result(
        self, key, success, command, expected, actual, expected_rv, actual_rv
    ):
        self.total += 1
        if success:
            self.passed += 1
        else:
            self.failed += 1
            self.failures.append(
                {
                    "key": key,
                    "command": command,
                    "expected": expected,
                    "actual": actual,
                    "expected_rv": expected_rv,
                    "actual_rv": actual_rv,
                }
            )

    def summary(self):
        """Return a summary of test results"""
        success_rate = (self.passed / self.total) * 100 if self.total > 0 else 0
        return (
            f"{Color.BOLD}Test Summary:{Color.RESET}\n"
            f"  {Color.BOLD}Total:{Color.RESET} {self.total}\n"
            f"  {Color.GREEN}Passed:{Color.RESET} {self.passed}\n"
            f"  {Color.RED}Failed:{Color.RESET} {self.failed}\n"
            f"  {Color.BOLD}Success Rate:{Color.RESET} {success_rate:.2f}%"
        )


class MinishellTester:
    def __init__(self, cwd, minishell_path="./minishell",  lines=1):
        self.minishell_path = minishell_path
        self.lines = lines
        self.oldwd = cwd
        self.test_result = TestResult()
        self.temp_dir = TEST_DIR 

        self.tests = {
            "builtin": get_builtin_tests(),
            "redirection": get_redirection_tests(),
            "syntax": get_syntax_tests(),
            "wildcard": get_wildcard_tests(),
            "andor": get_andor_tests(),
            "mix": get_mix_tests(),
        }

    def setup(self):
        self._clean_up()
        try:
            # Create test directories
            Path(f"{self.temp_dir}/outfiles").mkdir(parents=True, exist_ok=True)

            # Copy test files
            subprocess.run(["cp", "-r", "test_files", self.temp_dir], check=True)
            subprocess.run(
                ["cp", self.minishell_path, f"{self.temp_dir}/minishell"], check=True
            )

            # Change to test directory
            os.chdir(self.temp_dir)
            return True
        except Exception as e:
            print(f"{Color.RED}Failed to set up test environment: {e}{Color.RESET}")
            return False

    def _clean_up(self):
        """Clean up the test environment"""
        try:
            subprocess.run(["rm", "-rf", self.temp_dir], check=False)
        except Exception as e:
                print(f"{Color.YELLOW}Warning during cleanup: {e}{Color.RESET}")

    def run_test_category(self, category):
        if category not in self.tests:
            print(f"{Color.RED}Error: Unknown test category '{category}'{Color.RESET}")
            return False

        tests = self.tests[category]
        print(self.get_category_header(category))

        for key in tests:
            self._run_single_test(key, tests[key])

        return True

    def run_all_tests(self, include_bonus=False):
        mandatory = """
            ███╗░░░███╗░█████╗░███╗░░██╗██████╗░░█████╗░████████╗░█████╗░██████╗░██╗░░░██╗
            ████╗░████║██╔══██╗████╗░██║██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗██╔══██╗╚██╗░██╔╝
            ██╔████╔██║███████║██╔██╗██║██║░░██║███████║░░░██║░░░██║░░██║██████╔╝░╚████╔╝░
            ██║╚██╔╝██║██╔══██║██║╚████║██║░░██║██╔══██║░░░██║░░░██║░░██║██╔══██╗░░╚██╔╝░░
            ██║░╚═╝░██║██║░░██║██║░╚███║██████╔╝██║░░██║░░░██║░░░╚█████╔╝██║░░██║░░░██║░░░
            ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░░╚════╝░╚═╝░░╚═╝░░░╚═╝░░░ 
        """
        print(self.get_banner(mandatory))

        # Run mandatory test categories
        for category in ["builtin", "redirection", "syntax"]:
            self.run_test_category(category)

        # Run bonus test categories if requested
        if include_bonus:
            bonus = """
                ██████╗░░█████╗░███╗░░██╗██╗░░░██╗░██████╗
                ██╔══██╗██╔══██╗████╗░██║██║░░░██║██╔════╝
                ██████╦╝██║░░██║██╔██╗██║██║░░░██║╚█████╗░
                ██╔══██╗██║░░██║██║╚████║██║░░░██║░╚═══██╗
                ██████╦╝╚█████╔╝██║░╚███║╚██████╔╝██████╔╝
                ╚═════╝░░╚════╝░╚═╝░░╚══╝░╚═════╝░╚═════╝░
            """
            print(self.get_banner(bonus))
            for category in ["wildcard", "andor", "mix"]:
                self.run_test_category(category)
        print("\n" + self.test_result.summary())

        if self.test_result.failed > 0:
            self._write_failed_tests_to_file()

        return self.test_result.failed == 0

    def _run_single_test(self, key, cmd):
        # Skip special cases 
        skip = ["test 21", "test 22"]
        special_rv_cases = [
            "test 36",
            "test 38",
            "Exit 2",
            "Exit 4",
            "Exit 5",
            "Exit 6",
            "Exit 7",
            "Exit 8",
            "Exit 9",
            "Exit 10",
            "Exit 14",
            "Exit 15",
            "Exit 18",
            "Exit 21",
        ]

        # Apply special handling for certain commands
        command = cmd if key in skip else self._escape_special_chars(cmd)

        # Get expected output from bash
        expected_stdout, expected_stderr, expected_rv = self.get_bash_output(command)
        self._cleanup_after_test(key)

        # Get actual output from minishell
        actual_stdout, actual_stderr, actual_rv = self.get_minishell_output(command)
        self._cleanup_after_test(key)

        # Special handling for certain return values
        if key in special_rv_cases and actual_rv == expected_rv:
            actual_rv = 0
            expected_rv = 0

        # Compare results
        success = (
            actual_stdout == expected_stdout
            and actual_rv == expected_rv
            and (actual_rv == 0 or (actual_stderr and expected_stderr))
        )

        # Store the result
        self.test_result.add_result(
            key, success, cmd, expected_stdout, actual_stdout, expected_rv, actual_rv
        )

        # Print result
        if success:
            print(f"{key}: {Color.GREEN}✅{Color.RESET}")
        else:
            cmd = cmd.replace('\\', '')
            print(f"{Color.RED}{key} ❌ {Color.RESET}{cmd}")
            print(
                f"{Color.RED}===>Expected return -- value: {expected_rv}\n{expected_stdout}"
            )
            print(f"===>Actual return -- value: {actual_rv}\n{actual_stdout}{Color.RESET}")
            if  actual_stdout != expected_stdout:
                print(1)
                print(f"--{expected_stdout}--")
                print(f"--{actual_stdout}--")


        time.sleep(0.02)

    def get_bash_output(self, command):
        try:
            result = subprocess.run(
                f"echo {command} | bash", shell=True, capture_output=True,
            )
            return (
                result.stdout.decode('utf-8'),
                result.stderr.decode('utf-8'),
                127 if command == "." else result.returncode,
            )
        except Exception as e:
            print(f"{Color.YELLOW}Error getting bash output: {e}{Color.RESET}")
            return "", "", 1

    def get_minishell_output(self, command):
        try:
            result = subprocess.run(
                f"echo {command} | ./minishell",
                shell=True,
                capture_output=True,
            )
            # print(result.stdout.decode('utf-8'))
            # print(result.stderr.decode('utf-8'))
            # print(result.returncode)
            return (
                self._remove_prompt_lines(result.stdout.decode('utf-8')),
                result.stderr.decode('utf-8'),
                result.returncode,
            )
        except Exception as e:
            print(f"{Color.YELLOW}Error getting minishell output: {e}{Color.RESET}")
            return "", "", 1

    def _remove_prompt_lines(self, text):
        lines = text.split("\n")
        if len(lines) <= 2:
            return ""
        return "\n".join(lines[self.lines:-1]) + "\n"

    def _escape_special_chars(self, s):
        for char in "$&|'*><();#":
            s = s.replace(char, f"\\{char}")
        return s

    def _cleanup_after_test(self, key):
        cleanup_keys = ["mix test 95", "mix test 96", "mix test 77"]
        if key in cleanup_keys:
            subprocess.run(
                "rm -fr /tmp/tmp/test00 /tmp/tmp/test22",
                shell=True,
                capture_output=True,
            )

    def _write_failed_tests_to_file(self, filename="failed_tests.txt"):
        file_path = self.oldwd + "/" + filename
        try:
            with open(file_path, 'w') as file:
                file.write("\nFailed Tests:\n")
                for i, failure in enumerate(self.test_result.failures, 1):
                    file.write(f"\nFailure #{i}: {failure['key']}\n")
                    cmd = failure['command'].replace('\\', '')
                    file.write(f"Command: {cmd}\n")
                    file.write(f"Expected (rv={failure['expected_rv']}):\n{failure['expected']}\n")
                    file.write(f"Actual (rv={failure['actual_rv']}):\n{failure['actual']}\n")
                    file.write("-" * 60 + "\n")
            print(f"Content successfully written to '{file_path}'.")
        except Exception as e:
            print(f"An error occurred while writing to the file: {e}")

    def get_banner(self, text):
        width = 60
        return f"""
                    {Color.PURPLE}{'=' * width}
                    {text.center(width)}
                    {'=' * width}{Color.RESET}
                """

    def get_category_header(self, category):
        builtins = """
        █▄▄ █░█ █ █░░ ▀█▀ █▀   █ █▄░█
        █▄█ █▄█ █ █▄▄ ░█░ ▄█   █ █░▀█
            """

        redirections = """
        █▀█ █▀▀ █▀▄ █ █▀█ █▀▀ █▀▀ ▀█▀ █ █▀█ █▄░█
        █▀▄ ██▄ █▄▀ █ █▀▄ ██▄ █▄▄ ░█░ █ █▄█ █░▀█
        """

        syntaxerror = """
        █▀ █▄█ █▄░█ ▄▀█ ▀█▀ ▄▀█ ▀▄▀
        ▄█ ░█░ █░▀█ █▀█ ░█░ █▀█ █░█
        """
        wildcards = """
        █░█░█ █ █░░ █▀▄ █▀▀ ▄▀█ █▀█ █▀▄
        ▀▄▀▄▀ █ █▄▄ █▄▀ █▄▄ █▀█ █▀▄ █▄▀
        """
        mixed = """
        ▄▀█ █▄░█ █▀▄     █▀█ █▀█
        █▀█ █░▀█ █▄▀     █▄█ █▀▄
        """

        andorwilds = """
        ▄▀█ █▄░█ █▀▄   █▀█ █▀█   █░█░█ █ █░░ █▀▄ █▀▀ ▄▀█ █▀█ █▀▄
        █▀█ █░▀█ █▄▀   █▄█ █▀▄   ▀▄▀▄▀ █ █▄▄ █▄▀ █▄▄ █▀█ █▀▄ █▄▀
        """
        headers = {
            "builtin": f"{Color.CYAN}{builtins}{Color.RESET}",
            "redirection": f"{Color.CYAN}{redirections}{Color.RESET}",
            "syntax": f"{Color.CYAN}{syntaxerror}{Color.RESET}",
            "wildcard": f"{Color.CYAN}{wildcards}{Color.RESET}",
            "andor": f"{Color.CYAN}{andorwilds}{Color.RESET}",
            "mix": f"{Color.CYAN}{mixed}{Color.RESET}",
        }
        return headers.get(category, f"{Color.CYAN}{category.upper()}{Color.RESET}")



def main():
    parser = argparse.ArgumentParser(description="Test minishell implementation")
    parser.add_argument(
        "-p", "--path", type=str,default="./minishell", help="Path to minishell executable"
    )
    parser.add_argument(
        "-b", "--bonus", action="store_true", help="Run bonus tests too"
    )
    parser.add_argument(
        "-l", "--lines", type=int, default=1, help="Number of lines to skip"
    )
    parser.add_argument(
        "-c",
        "--category",
        type=str,
        choices=["builtin", "redirection", "syntax", "wildcard", "andor", "mix"],
        help="Run only tests from this category",
    )

    args = parser.parse_args()

    if not os.path.exists(args.path):
        print(
            f"{Color.RED}Error: No minishell executable found at '{args.path}'{Color.RESET}"
        )
        return 1

    cwd = os.getcwd()
    tester = MinishellTester(cwd, args.path,  args.lines)

    if not tester.setup():
        return 1

    if args.category:
        success = tester.run_test_category(args.category)
    else:
        success = tester.run_all_tests(args.bonus)

    return 0 if success else 1


if __name__ == "__main__":
    sys.exit(main())
