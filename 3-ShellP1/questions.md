1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  `fgets()` is a good choice for this application as it prevents buffer overflow and it reads complete lines.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  We used `malloc()` instead as it provides greater flexibility then allocating a fixed-size array.


3. In `dshlib.c`, the function `build_cmd_list()` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  It is necessary to trim leading and trailing spaces in order to ensure the data is being parsed correctly. Without trimming, issues like misinterpreting data or handling empty commands could arise.

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  Redirecting STDOUT to a file: uses `>` to redirect output from the screen to a specific file. Can create a file if it doesn't exist already or remove it if it does.

    > Appending to a file: `>>` Adds on to the contents of a file, but it must be the last command executed on the command line.
    
    > Redirect STDERR to a file: just like with STDOUT, you can redirect error messages to a file using `2>`.
    
    > We could have issues with error handling and data parsing if we implemented these redirection examples.

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:  The key difference between redirection and piping is that redirect is file-based and changes where input/output goes, while piping connects multiple commands and is more process-based.

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**: It is important to keep these separate in a shell in order to have better control over the flow of data and it makes it easier to handle error detection.

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**: I think our custom shell should keep STDOUT and STDERR separate. Errors from commands that fail should be displayed to the user then stored in an error file for debugging purposes. 