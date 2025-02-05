# 📝 td

_td_ is a blazing-fast CLI tool to efficiently manage your TODO.md directly from the terminal. It's fast!

## 🚀 Usage

```bash
$ td --help
A blazing-fast CLI tool to efficiently manage your TODO.md directly from the terminal

Usage: td [COMMAND] [ARGUMENTS] [OPTIONS]

Commands:
  init <title>              Create TODO.md in the current directory
  add <task>                Add a new task to TODO.md
  list                      Display all tasks
  done <id>                 Mark the task with ID <id> as completed
  remove <id>               Remove the task with ID <id>
  clear                     Remove all tasks from TODO.md

Arguments:
  <task>                    The task description (e.g., "Learn C")
  <title>                   The heading for TODO.md (e.g., "Planned features")
  <id>                      The task ID (e.g., the number from the task list)

Options:
  -f, --file <path>         Specify a custom TODO.md file path (defaults to TODO.md in the current directory)
  -h, --help                Show this help message
  -v, --version             Display the program version
```
