# Minishell
## Building the project
Use ```make BUILD=dev``` to use address sanitizer<br>
Use ```make BUILD=valgrind``` to use valgrind<br>
Use ```valgrind --leak-check=full --show-leak-kinds=definite ./minishell``` to not show readline errors<br>

## Development flags
During development, we use the flags `-g3 -fstack-protector-strong -Wvla -O1`, they are useful for debugging. We also link the fsanitize library with `-fsanitize=address,undefined,leak`. This is only true when the `BUILD` variable is set do `dev` as this library must not be used in conjunction with **Valgrind**.

The vpath in the Makefile is set depending on the `USER` variable.

## Useful functions
### Lists
#### t_list \*ft_lstfind(t_list \*lst, void \*data_ref, int (\*cmp)())
Finds a node in a linked list that matches a given reference data.<br>
Mostly used with ft_strcmp.
#### void	ft_lstpop(t_list **lst, void *ref, int (*cmp)(void *, void *), void (*del)(void *));
Removes the first node from the list that matches the reference value using the provided comparison function and deletes it using the provided deletion function.
### Environment
#### char *build_env_string(const char *name, const char *value)
Builds a string in the format `name=value` from the given name and value.
#### char *env_value(const char *env_string)
Retrieves the value part of an environment variable string.
#### char *env_name(const char *env_string)
Retrieves the name part of an environment variable string.
#### int compare_env_name(const void *content, const void *name_ref)
Compares a name against the name part of a "name=value" string.

## Builtins
### echo `[-n] [arg ...]`
Output the args, separated by spaces, followed by a newline. The return status is 0 unless a write error occurs. If -n is specified, the trailing newline is suppressed. echo does not interpret -- to mean the end of options. echo interprets the following escape sequences:
`\a`     alert (bell)
`\b`     backspace
`\c`     suppress further output
`\e`
`\E`     an escape character
`\f`     form feed
`\n`     new line
`\r`     carriage return
`\t`     horizontal tab
`\v`     vertical tab
`\\`     backslash
`\0nnn`  the eight-bit character whose value is the octal value nnn (zero to three octal digits)
`\xHH`   the eight-bit character whose value is the hexadecimal value HH (one or two hex digits)
`\uHHHH` the Unicode (ISO/IEC 10646) character whose value is the hexadecimal value HHHH (one to four hex digits)
`\UHHHHHHHH` the Unicode (ISO/IEC 10646) character whose value is the hexadecimal value HHHHHHHH (one to eight hex digits)

### cd ` [dir]`
Change the current directory to dir. If dir is not supplied, the value of the HOME shell variable is the default. Any additional arguments following dir are ignored. The variable CDPATH defines the search path for the directory containing dir: each directory name in CDPATH is searched for dir. Alternative directory names in CDPATH are separated by a colon (:). A null directory name in CDPATH is the same as the current directory. If dir begins with a slash (/), then CDPATH is not used. If .. appears in dir, it is processed by removing the immediately previous pathname component from dir, back to a slash or the beginning of dir. An argument of - is converted to $OLDPWD before the directory change is attempted. If a non-empty directory name from CDPATH is used, or if - is the first argument, and the directory change is successful, the absolute pathname of the new working directory is written to the standard output. The return value is true if the directory was successfully changed; false otherwise.

### pwd
Print the absolute pathname of the current working directory. The return status is 0 unless an error occurs while reading the name of the current directory or an invalid option is supplied.

### export `[name[=word]] ...`
The supplied names are marked for automatic export to the environment of subsequently executed commands.If no names are given, a list of names of all exported variables is printed. If a variable name is followed by =word, the value of the variable is set to word. export returns an exit status of 0 unless an invalid option is encountered or one of the names is not a valid shell variable name.

### unset `[name ...]`
For each name, remove the corresponding variable or function. Read-only variables may not be unset. Each name refers to a variable. Each unset variable is removed from the environment passed to subsequent commands. If any of BASH_ALIASES, BASH_ARGV0, BASH_CMDS, BASH_COMMAND, BASH_SUBSHELL, BASHPID, COMP_WORDBREAKS, DIRSTACK, EPOCHREALTIME, EPOCHSECONDS, FUNCNAME, GROUPS, HISTCMD, LINENO, RANDOM, SECONDS, or SRANDOM are unset, they lose their special properties, even if they are subsequently reset. The exit status is true unless a name is readonly.

### env
The env command prints all environment variables currently set in the shell. Each variable is displayed in the format: `VARIABLE=VALUE`. This implementation of env does not accept any options or arguments.

### exit `[n]`
Cause the shell to exit with a status of n. If n is omitted, the exit status is that of the last command executed. A trap on EXIT is executed before the shell terminates.
