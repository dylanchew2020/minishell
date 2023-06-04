# minishell
42KL Minishell Project

File Structure Guide
- Store all .c program files under "src".
- Store all .h header files under "includes".
- All .o object files will be generted under "obj".
- Libft files are free to modified. Recommended to run a git commit after each modification.

Working with Git
***DO NOT WORK DIRECTLY IN MAIN BRANCH***
1. "git checkout -b <new branch name> dev" - format follow "YYMMDD-branch_title".
    This will create and checkout to a new branch, branching from <dev> branch.
2. "git branch -a" to confirm you are in the correct branch.
3. Work in your branch.
4. Once the function tested to be working in your branch, before merging to dev,
   merge FROM dev into your branch via "git merge --no-ff main". 
   Resolve all conflicts.
   Add, commit and push resolved branch.
5. "git checkout dev" to switch to develop branch.
6. "git merge --no-ff <your branch>" - merge your branch into develop branch.
7. "git push origin dev"
8. You may OR may not needed to delete your branch with "git branch -d <your branch>".


################################################################################
#                                    UPDATES                                   #
################################################################################

***Person 1:***
**Setup the project:**
Create the project repository.
Create the necessary files: Makefile, *.h, *.c.
Write a basic Makefile with the rules $(NAME), all, clean, fclean, and re.

**Basic shell functionality:**
Write a function to display a prompt that waits for a new command. (Relevant functions: readline, printf)
Write a function to record and display a working history for the shell. (Relevant functions: add_history, rl_on_new_line)

**Executable handling:**
Write a function to search for the right executable based on the PATH variable. (Relevant functions: getenv, access)
Write a function to launch the executable using a relative or an absolute path. (Relevant functions: fork, execve)

**Quote and special character handling:**
Write a function to handle ’ (single quote) correctly.
Write a function to handle " (double quote) correctly.
Ensure the shell does not interpret unclosed quotes or special characters such as \ (backslash) or ; (semicolon).

**Built-in commands:**
Write a function to implement the 'echo' builtin with option -n. (Relevant functions: write)
Write a function to implement the 'cd' builtin with only a relative or absolute path. (Relevant functions: chdir)
Write a function to implement the 'pwd' builtin with no options. (Relevant functions: getcwd)

***Person 2:***
**Global variable:**
Decide on the purpose of the one allowed global variable.
Implement the necessary functionality using this global variable.

**Redirections and pipes:**
Write a function to implement the '<' redirection. (Relevant functions: open, dup2)
Write a function to implement the '>' redirection. (Relevant functions: open, dup2)
Write a function to implement the '<<' redirection. (Relevant functions: open, dup2)
Write a function to implement the '>>' redirection. (Relevant functions: open, dup2)
Write a function to implement pipes (| character). (Relevant functions: pipe, dup2)

**Environment variables and exit status:**
Write a function to handle environment variables ($ followed by a sequence of characters) which should expand to their values. (Relevant functions: getenv)
Write a function to handle $? which should expand to the exit status of the most recently executed foreground pipeline. (Relevant functions: wait, waitpid)

**Handling of control sequences:**
Write a function to handle ctrl-C. (Relevant functions: signal)
Write a function to handle ctrl-D. (Relevant functions: exit)
Write a function to handle ctrl-\. (Relevant functions: signal)

**More built-in commands:**
Write a function to implement the 'export' builtin with no options. (Relevant functions: setenv)
Write a function to implement the 'unset' builtin with no options. (Relevant functions: unsetenv)
Write a function to implement the 'env' builtin with no options or arguments. (Relevant functions: getenv)
Write a function to implement the 'exit' builtin with no options. (Relevant functions: exit)

0: Successful execution. This status indicates that the command or script completed without any errors.
1: General error. This status is typically used to indicate that an unspecified error occurred.
2: Misuse of shell built-ins. It is used to indicate that a command was not used correctly.
126: Command cannot be invoked. This status is used when the command or script is found but cannot be executed.
127: Command not found. It is used when the command or script is not found or cannot be executed.
128: Invalid argument to exit. This status is used when the exit command is used incorrectly, specifying an invalid argument.
130: Script terminated by Control+C. This status is used when a script or command is terminated by the user using the Control+C key combination.
137: Script terminated by a signal. This status is used when a script or command is terminated by a signal, usually indicating a fatal error.
255: Exit status out of range. It is used when the exit command is given an exit status that is outside the valid range of 0 to 255.