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

- readlines not yet added to makefile. Review makefile if any compilation issue.

Tasks
- Implement a command prompt
- Read user input
- Handle memory correctly
- Implement a working history feature

Member 1:

**Implement a command prompt**: This involves creating a loop that will continuously display a prompt for the user to enter their commands.

**Read user input**: After the prompt is displayed, the next step is to read the command entered by the user. This can be done using functions like readline().

**Implement a working history feature**: This involves keeping track of the commands entered by the user. The GNU Readline library provides functions for working with history, which can be used to add the user's input to the history list after it's processed.

Member 2:

**Handle memory correctly**: This involves managing the memory allocated during the program, especially the memory allocated by readline(). The member will need to ensure that all allocated memory is properly freed to avoid memory leaks.

**Parsing User Input**: This involves breaking down the user input into commands and their arguments. Handling spaces, tabs, newline characters as delimiters, and correctly handling quotes and metacharacters are part of this task.