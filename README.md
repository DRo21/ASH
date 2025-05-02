# Ash

ASH just Another SHell

At the moment the focus lies in implementing the core functionalities.
In the future more features like flags will be added.

# Core functionalities

## File System Navigation & Management
- [x] `cd`: Change the current directory.
- [x] `pwd`: Print the current working directory.
- [x] `ls`: List directory contents.
- [x] `mkdir`: Create a new directory.
- [x] `rmdir`: Remove an empty directory.
- [x] `rm`: Remove files or directories.
- [x] `touch`: Create an empty file or update the timestamp of an existing file.
- [x] `cp`: Copy files or directories.
- [x] `mv`: Move or rename files or directories.
- [x] `find`: Search for files and directories in a directory hierarchy.
- [x] `ln`: Create hard or symbolic links to files.

## File Viewing & Editing
- [x] `cat`: Concatenate and display file content.
- [x] `more`: View the contents of a file, page by page.
- [x] `less`: View file content, allows scrolling and searching.
- [x] `head`: Display the first few lines of a file.
- [x] `tail`: Display the last few lines of a file.

## Process Management
- [x] `ps`: Display currently running processes.
- [x] `top`: Display dynamic real-time information about processes.
- [x] `kill`: Terminate processes.
- [x] `killall`: Terminate processes by name.
- [x] `bg`: Resume a suspended job in the background.
- [x] `fg`: Bring a job to the foreground.
- [x] `jobs`: List all current jobs running in the background.
- [x] `nohup`: Run a command immune to hangups (often used to run long-running tasks).

## System Information & Management
- [ ] `df`: Display disk space usage.
- [ ] `du`: Display disk usage of files and directories.
- [ ] `free`: Display memory usage.
- [ ] `uname`: Display system information.
- [ ] `uptime`: Show how long the system has been running.
- [ ] `who`: Show who is logged in to the system.
- [ ] `w`: Display who is logged in and their activity.
- [x] `top`: Display real-time information about system processes and resource usage.

## File Permissions & Ownership
- [ ] `chmod`: Change file permissions.
- [ ] `chown`: Change file owner and group.
- [ ] `chgrp`: Change group ownership of a file or directory.
- [ ] `umask`: Set default file creation permissions.

## Redirection & Piping
- [ ] `>`: Output redirection (e.g., redirecting the output of a command to a file).
- [ ] `>>`: Append output redirection.
- [ ] `<`: Input redirection (e.g., using a file as input to a command).
- [ ] `|`: Pipe the output of one command into another command.

## Networking
- [ ] `ping`: Send ICMP ECHO_REQUEST to network hosts.
- [ ] `ifconfig`: Display or configure network interfaces (deprecated in some systems in favor of `ip`).
- [ ] `ip`: A more modern tool for network configuration.
- [ ] `netstat`: Display network connections, routing tables, and interface statistics.

## Archiving & Compression
- [ ] `zip`: Create zip archives.
- [ ] `unzip`: Extract files from zip archives.

## Environment & Shell Management
- [ ] `export`: Set environment variables for the current shell session.
- [ ] `env`: Show the environment or run a command with a modified environment.
- [ ] `source`: Read and execute commands from a file in the current shell session.
- [ ] `alias`: Create or display aliases for commands.
- [ ] `unalias`: Remove aliases.
- [ ] `unset`: Remove environment variables or shell functions.

## Job Control
- [x] `bg`: Resume a job in the background.
- [x] `fg`: Bring a job to the foreground.
- [x] `jobs`: List background jobs.
- [ ] `ctrl+z`: Suspend the current foreground job.
- [ ] `ctrl+c`: Terminate the current foreground job.

## Search & Text Processing
- [ ] `grep`: Search for patterns in files.
- [ ] `sed`: Stream editor for text processing and transformation.
- [ ] `awk`: Pattern scanning and processing language for data extraction and reporting.
- [ ] `cut`: Remove sections from lines of files.
- [ ] `sort`: Sort lines of text files.
- [ ] `uniq`: Report or omit repeated lines.
- [ ] `tr`: Translate or delete characters.
- [ ] `wc`: Word count (lines, words, characters).
- [ ] `diff`: Compare files line by line.
- [ ] `cmp`: Compare two files byte by byte.

## Shell Built-ins & Control Structures
- [x] `exit`: Exit the shell.
- [x] `echo`: Output text or variables to the terminal.
- [ ] `read`: Read input from the user.
- [ ] `set`: Set or unset shell options.
- [ ] `unset`: Remove shell variables or functions.
- [ ] `test` / `[ ]`: Evaluate conditional expressions (used in scripting).

## Utilities
- [x] `history`: Show command history.
- [x] `clear`: Clear the terminal screen.
- [ ] `date`: Display or set the system date and time.
- [ ] `cal`: Display a calendar.
- [ ] `bc`: Basic calculator.
- [ ] `file`: Determine the file type.
- [ ] `stat`: Display detailed file or file system status.
- [ ] `tee`: Read from standard input and write to standard output and files.

## Disk and File System Utilities
- [ ] `mount`: Mount a file system.
- [ ] `umount`: Unmount a file system.
- [ ] `fsck`: Check and repair file systems.
- [ ] `fdisk`: Partition a disk.
- [ ] `mkfs`: Create a file system on a device.

## System Shutdown & Reboot
- [ ] `reboot`: Reboot the system.
- [ ] `shutdown`: Shut down the system.
- [ ] `halt`: Halt the system.