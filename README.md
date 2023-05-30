# minishell
42KL Minishell Project

File Structure Guide
- Store all .c program files under "src".
- Store all .h header files under "includes".
- All .o object files will be generted under "obj".
- Libft files are free to modified. Recommended to run a git commit after each modification.

Working with Git
***DO NOT WORK DIRECTLY IN MAIN BRANCH***
1. ```git checkout -b <new branch name> dev```
   - format follow "YYMMDD-branch_title".
   - This will create and checkout to a new branch, branching from <dev> branch.
2. ```git branch -a``` to confirm you are in the correct branch.
3. Work in your branch.
4. Once the function tested to be working in your branch, before merging to dev,
   merge FROM dev into your branch via
    
    ```git merge --no-ff main```
    
    Resolve all conflicts.
   Add, commit and push resolved branch.
5. ```git checkout dev``` to switch to develop branch.
6. ```git merge --no-ff <your branch>``` - merge your branch into develop branch.
7. ```git push origin dev```
8. You may OR may not needed to delete your branch with ```git branch -d <your branch>```.


################################################################################
#                                    UPDATES                                   #
################################################################################

- readlines not yet added to makefile. Review makefile if any compilation issue.
   
Reading Input
- Implement the readline function to read user input.
- Handle memory correctly.
- Implement a working history feature.
   
Parsing Input
- Parse the input into commands and arguments.
- Handle quotes and metacharacters correctly.
   
Executing Commands
- Execute the parsed commands using functions like fork, execve, wait, and waitpid.
- Handle errors correctly and print useful error messages using perror or strerror.
   
Implement Built-in Commands
- Implement the echo command with option -n.
- Implement the cd command with only a relative or absolute path.
- Implement the pwd command with no options.
- Implement the export command with no options.
- Implement the unset command with no options.
- Implement the env command with no options or arguments.
- Implement the exit command with no options.
   
Implement Redirection and Pipes
- Implement input redirection using <.
- Implement output redirection using >.
- Implement input redirection with a delimiter using <<.
- Implement output redirection in append mode using >>.
- Implement pipes using the | character.
   
Handle Environment Variables
- Implement the handling of environment variables that start with $.
   
Handle Control Sequences
- Implement the handling of ctrl-C, ctrl-D, and ctrl-\.
