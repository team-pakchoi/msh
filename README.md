
## Team Pakchoi 🥬
- [cpak](https://github.com/PCHANUL)
- [sarchoi](https://github.com/srngch)

[![42](https://img.shields.io/badge/BornToCode-3_Circle-00babc?style=flat-square&logo=42)](https://42seoul.kr/)
[![result](https://img.shields.io/badge/WIP-0/100-5cb85c?style=flat-square&logoWidth=12&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAAAXNSR0IArs4c6QAAAylJREFUaEPtmDmLVEEUhb+LK+IG7qIibuCKYCYYOSoGomjimoggOgiKmYGhgYEMGqgYiJmIG4ig4IKGitsv8Ae4m7ocuWO108u8flWvu+030JXN9Kmqc+49devWM0b4sBHOn56Abmewl4FeBnIiIGk6cBtYCxwzs2vVU0ptIUkzgEfAmkBawFEzu1QRUVoBgfxjYHVdklzEETO77P8vpYAm5CtafgMH3U6lEyBpJuCRX5VzPH4BB0olIJB/AqyMrG4fSiNA0izAya+IJO+wp6UQkGCbam3vgL6uCyhgGxfxl7zZx64KCLbxAxvr+RryXS2jBT3/L/JdvcjaRX7YDEhaBJwB3gOnzexHQlXIhUqa69UDWJYLHgK8DZ7/VD+n5gxIWgfcB7yk+bgF7DaznwmbZUIlzQ6XVEqpbLDNsM2cpI2h65tcx+AmsKdVEYG81/nlCcHwyG/yapM1ZzADkvYBV4ExGcAbwF4z8+s7eUiaF2yzJGFypm1qMiCpH7gQ0di5wENm5o1U9ChI/k3w/Oe8jUzSd2BSHjD8fgU4bGbe0uYOSfND5BfngocA0eR9igu4C2xP2OAi0J8nQtKC0NukkH8dPJ8b+QpfFzABeABsSBBxHjieJaJg5KM8X8+xcoinhPLmZTR2DJjZiXpwwcgXIj9ooQqB8Hh+ltjOnjOzk1VruG38kvLLMHYUJl8jwP8It+RzIMW3Z4FTYc5DYGEsc+BV8PyXhDk10IZuVJITcBFeQWLH11DJRsVOaAf5hgxUWWEp4Haak0AoBeql0m/Yht4mZZFMAcFO/jnD/TwtddEcfFKdz9u76YNGkn8NcxFT8xaK/L2t5JtmoMpO6wE/nBMjSWbB2k4+SkCwUx9wDxhfUETyDRu7T/SbWNI2wFvrsbGLB9xLYLOZeaVq+4gWEDKxFbgDjItk0rHIV/ZPEhBE7AD8fZD1dqis/QLY0qnIFxYQROwErjcR0fHItyQgR8R/Ix9dhbL8LmlXyMTogPHexg9sdD8feZYyYclnoH4lSW6ngfC5b7+ZfWuVVMr8lgWkbNYJbE9AJ6KasmYvAynR6gR2xGfgD5kpEElZbxKNAAAAAElFTkSuQmCC)](https://projects.intra.42.fr/42cursus-minishell/sarchoi)


[![code-size](https://img.shields.io/github/languages/code-size/42pakchoi/minishell?style=flat-square)](https://github.com/42pakchoi/minishell)
[![last-commit](https://img.shields.io/github/last-commit/42pakchoi/minishell?style=flat-square)](https://github.com/42pakchoi/minishell)

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#requirements">Requirements</a></li>
    <li><a href="#implementation">Implementation</a></li>
    <li><a href="#project-structure">Project Structure</a></li>
    <li><a href="#environment">Environment</a></li>
    <li><a href="#compile">Compile</a></li>
		<li><a href="#execute">Execute</a></li>
		<li><a href="#example">Example</a></li>
		<li><a href="#links">Links</a></li>
  </ol>
</details>

---

# Minishell

The objective of this project is for you to create a simple shell. Yes, your own little bash or zsh. You will learn a lot about processes and file descriptors.

## Requirements

|                      |                                           |
| -------------------- | ----------------------------------------- |
| **Program name**     | `minishell`                               |
| **Makefile**         | `all`, `clean`, `fclean`, `re`            |
| **Arguments**        | None                 |
| **External functs.** | `readline`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `errno`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs` |
| **Libft authorized** | Yes                                       |

## Implementation

- prompt
- history
- builtins
	- `echo` with option `-n`
	- `cd` with only a relative or absolute path
	- `pwd` without options
	- `export` without options
	- `unset` without options
	- `env` without options or arguments
	- `exit` without options
- interpretation `"` only for `$`
- redirections
	- `<` redirect input
	- `>` redirect output
	- `<<` heredoc
	- `>>` redirect output with append mode
- pipes: `|`
- environment variables: `$`
- exit status: `$?`
- signal interactive like bash
	- `ctrl-c` print a new prompt on a newline.
	- `ctrl-d` exit the shell.
	- `ctrl-\` do nothing.

## Project Structure

```
./
├── includes/		# header files
├── libft/			# library files
├── src/			# source files
│   ├── builtin/	# builtin commands
│   └── util/		# utility functions
├── test/			# test command files
└── Makefile
```

## Environment

- MacOS 12.3.1(Monterey, Intel)

Developed and tested in this environment.

## Compile

### Mandatory

```bash
$ git clone https://github.com/42pakchoi/minishell
$ make
```

## Execute

Run compiled executable file in the root folder.

```bash
$ ./minishell
~/path_to_pwd/minishell $ 
```

## Example

```bash
# minishell builtin commands
~/path_to_pwd/minishell $ echo "Hello world!"
Hello world!
# commands in PATH
~/path_to_pwd/minishell $ ls
Makefile	includes	minishell	test
README.md	libft		src
# command `exit` or press `ctrl-d` to exit the minishell
~/path_to_pwd/minishell $ exit
```


## Links

- [Subject - 42 Intra](https://projects.intra.42.fr/projects/42cursus-minishell)
- [Subject - 42Seoul Translation](https://github.com/42seoul-translation/subject_ko/blob/master/minishell/minishell.md)
- [GNU Bash manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/)
