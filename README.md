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