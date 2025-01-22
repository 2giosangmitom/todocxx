# 📝 todocxx

**todocxx** is a blazing-fast, terminal-based TODO application written in C++. It empowers developers and terminal enthusiasts to manage their tasks efficiently with a simple yet powerful command-line interface.

## ✨ Features

- ➕ **Add**, 📜 **list**, ✏️ **update**, and ❌ **delete** TODOs effortlessly.
- 🌟 Assign priorities to tasks (🟢 Low, 🟡 Medium, 🔴 High).
- 🔍 Filter and search tasks by priority or keywords.
- 📊 View tasks in a dynamically formatted table for better readability.
- ⚡ Lightweight and fast, suitable for developers working directly in the terminal.

## 🛠️ Installation

### Prerequisites

- C++17 or newer
- A compatible compiler (e.g., g++, clang++)
- [fmt](https://fmt.dev/latest/index.html) library
- [cxxopts](https://github.com/jarro2783/cxxopts)

### Build steps

These build steps are for Linux:

1. Clone the repository:

   ```bash
   git clone https://github.com/2giosangmitom/todocxx.git
   cd todocxx
   ```

2. Build the project:

   ```bash
   make
   ```

3. Run the executable:

   ```bash
   ./build/todocxx
   ```

## 🚀 Usage

**todocxx** provides a simple and intuitive interface for managing TODOs. Below are the supported commands:

### 🛠️ General options

| Command         | Description                     |
| --------------- | ------------------------------- |
| `--help, -h`    | Display the help message        |
| `--version, -v` | Display the application version |

### 📋 Task management

| Command              | Description                                                    |
| -------------------- | -------------------------------------------------------------- |
| `--add, -a <TITLE>`  | Add a new TODO with the specified title                        |
| `--list, -l`         | List all TODOs                                                 |
| `--update, -u <ID>`  | Update a TODO by ID (keeps existing priority if not specified) |
| `--delete, -d <IDs>` | Delete one or more TODOs by ID (e.g., `1,2,3`)                 |

### 🔍 Query options

| Command                     | Description                                                     |
| --------------------------- | --------------------------------------------------------------- |
| `--priority, -p <1-3>`      | Set or filter by priority (1: 🟢 Low, 2: 🟡 Medium, 3: 🔴 High) |
| `--filter, -f <PRIORITIES>` | Filter TODOs by priorities (e.g., `1,2`)                        |
| `--search, -s <KEYWORDS>`   | Search TODOs by keywords                                        |

## 💻 Examples

### ➕ Add a task

```bash
./todocxx --add "Write documentation" --priority 2
```

### 📜 List all tasks

```bash
./todocxx --list
```

### ✏️ Update a task

```bash
./todocxx --update 1 --title "Update README"
```

If `--priority` is omitted, the priority remains unchanged.

### ❌ Delete tasks

```bash
./todocxx --delete 1,2
```

## 🤝 Contributing

Contributions are welcome! Feel free to fork this repository, make changes, and submit a pull request.

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

Special thanks to the creators of:

- [fmt](https://fmt.dev/latest/index.html)
- [cxxopts](https://github.com/jarro2783/cxxopts)
