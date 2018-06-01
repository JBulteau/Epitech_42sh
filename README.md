# 42sh!

Grade [??](https://scontent-cdg2-1.xx.fbcdn.net/v/t1.0-0/p370x247/20258415_1390623461036699_1748591071668363730_n.jpg?_nc_cat=0&oh=5e800d5bebf143ed2d89e3a71de51598&oe=5B9261DD)/20

# What is it ?

The **42sh** is our end of first year project at **Epitech**. We have to reproduce a shell based on tcsh with redirections, pipes, separators and environment

# Bonuses

After reproducing the minimal requirements we had carte blanche to have fun and implement new features (some basics of them are strongly suggested)

Here is what we implemented:

- @ [variable[=[expression]]]
	> Assign the `expression` to `variable`
- @ variable++
	> Increment `variable` by 1.
- @ variable--
	> Decrement `variable` by 1.

	**Note** :  please notice that we temporary remove the variable replacement in command-line parsing in order to prevent some crashes. We are currently fixing it.

- alias [name [command]]
	> Assign `name` as alias for `command`
	> If `name` is omitted print all alias
- alias [rm [name]]
- unalias [name]
	> Remove the alias on `name`
- builtins
	> Display all builtins
- cd [-|dir]
	> Change working directory to `dir`
	> If `-` is the first arg returns to the previous working directory
- chdir [-|dir]
	> Same as `cd`
- echo [-n] string
	> Write string to stdout.
	> If `-n` is specified the output is not terminated by a newline.
- exit [num]
	> Exit the shell whith an exit value of `num`
	> If `num` is unspecified exit with a status of zero
- fg [jobID]
	> bring the current `jobID` to the foreground
- history [d|del|delete [num]] [clear]
	> List all commands in history
	> If a `delete` option is specified deletes the `num` command from history
	> If `clear` is specified clears the history
- jobs [-l]
	> List all running jobs
	> If `-l` specified includes process id
- printenv [variable]
	> Print all (or one specified) environment variables and their values.
- repeat [n command]
	> repeats the `command` `n` times

# To see further : JARVIS feature

We implemented a correcter (**JARVIS corrector**) in our shell. Currently, in case of wrong command, this corrector suggest the closest correct command or argument to the user input.

In the future we may improve this corrector to make it more performing.

Originally, we also wanted to implement a bigger feature : **JARVIS micro**.
Thanks to the Google API Speech, our shell should have been able to be controlled only with voice (nevertheless keeping the classical command-line).

However, time played a crucial role in the development of this project, and in order to release our 42sh before the deadline, we gave up the **JARVIS micro** feature. But not forever...
> **Important:** No CPU was abused during the development of this project.