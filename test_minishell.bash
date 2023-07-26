#!/bin/bash
#!/bin/bash

# Define the commands to test
commands=(
    "/bin/ls"
    "/bin/ls -l"
    "echo \"Hello, World!\""
    "echo -n \"Hello, World!\""
	"echo -nn \"Hello, World!\""
	"echo -n -n \"Hello, World!\""
    "echo \"cat lol.c | cat > lol.c\""
    "echo '\$USER'"
    "export TEST_VAR=hello"
    "env | grep TEST_VAR"
    "export TEST_VAR=hello"
    "unset TEST_VAR"
    "env | grep TEST_VAR"
    "cd .."
    "/bin/ls"
    "cd ."
    "/bin/ls"
    "pwd"
    "ls"
    "echo \"Hello, World!\" > output.txt"
    "cat < output.txt"
    "echo \"Hello again!\" >> output.txt"
    "cat < output.txt"
    "echo \"Hello, World!\" | cat | more"
    "echo \"This is a very long command with a ton of arguments\" | cat | more"
    "echo \$USER"
    "echo \"\$USER\""
    "echo '$USER'"
    "cd .."
    "cd ."
    "echo \"Hello, World!\" > output.txt"
    "cat < output.txt"
    "echo \"Hello again!\" >> output.txt"
    "cat < output.txt"
    "cat filethatdoesntexist | grep bla | more"
    "ls filethatdoesntexist | grep bla | more"
    "echo \"dsbksdgbksdghsd\""
)

# Define colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Start the minishell program
spawn ./minishell

# Loop over the commands
foreach cmd $commands {
    # Send the command to minishell
    send "$cmd\r"

    # Wait for the prompt to appear again
    expect "$ " ;# replace "prompt> " with your actual prompt

    # The output of the command is now in the variable $expect_out(buffer)
    set minishell_output $expect_out(buffer)

    # Now run the command in bash and capture the output
    set bash_output [exec bash -c $cmd]

    # Compare the outputs
    if [ "$bash_output" == "$minishell_output" ]; then
        echo -e "PASS: $cmd"
		echo -e "${GREEN}Expected: $bash_output${NC}"
        echo -e "${RED}Got: $minishell_output${NC}"
    else
        echo -e "FAIL: $cmd"
        echo -e "${GREEN}Expected: $bash_output${NC}"
        echo -e "${RED}Got: $minishell_output${NC}"
    fi
done

# Exit the minishell program
send "exit\r"
expect eof