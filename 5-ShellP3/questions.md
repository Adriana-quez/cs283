1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

> My implementation ensures that all child processes complete by utilizing waitpid to signal when a child has ended. If I forgot to call waitpid on all child processes then the terminated children would remain in a zombie state and consume system resources.

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

> If unused pipes are left open after calling dup2(), issues like a resource/file descriptor leak could occur.

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

> CD is implemented as a built-in command as it changes the shell's current directory, which affects the shell itself. If it were implemented as an external process, then the change would only happen in the child process and would be lost once that process ends.

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

> To allow an arbitrary number of piped commands, I would modify my implementation to dynamically allocate memory for the pipe file descriptors and processes using malloc(). Some trade-offs I would need to consider include ensuring that the resources are properly cleaned up to avoid leaks.