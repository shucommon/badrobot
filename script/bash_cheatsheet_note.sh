# conditionals

## conditions
# Note that [[ is actually a command/program that returns either 0 (true) or 1 (false).
# Any program that obeys the same logic (like all base utils, 
# such as grep(1) or ping(1)) can be used as condition, see examples.
[[ -z STRING ]]	Empty string
[[ -n STRING ]]	Not empty string
[[ STRING == STRING ]]	Equal
[[ STRING != STRING ]]	Not Equal
[[ NUM -eq NUM ]]	Equal
[[ NUM -ne NUM ]]	Not equal
[[ NUM -lt NUM ]]	Less than
[[ NUM -le NUM ]]	Less than or equal
[[ NUM -gt NUM ]]	Greater than
[[ NUM -ge NUM ]]	Greater than or equal
[[ STRING =~ STRING ]]	Regexp, contain same part
(( NUM < NUM ))	Numeric conditions
[[ -o noclobber ]]	If OPTIONNAME is enabled
[[ ! EXPR ]]	Not
[[ X ]] && [[ Y ]]	And
[[ X ]] || [[ Y ]]	Or

## file conditions
[[ -e FILE ]]	Exists
[[ -r FILE ]]	Readable
[[ -h FILE ]]	Symlink
[[ -d FILE ]]	Directory
[[ -w FILE ]]	Writable
[[ -s FILE ]]	Size is > 0 bytes
[[ -f FILE ]]	File
[[ -x FILE ]]	Executable
[[ FILE1 -nt FILE2 ]]	1 is more recent than 2
[[ FILE1 -ot FILE2 ]]	2 is more recent than 1
[[ FILE1 -ef FILE2 ]]	Same files

# arguments
*	asterisk	    The positional parameters starting from the first. When used inside doublequotes (see quoting), like "$*",
                    it expands to all positional parameters as one word, delimited by the first character if the IFS variable 
                    (a space in this example): "$1 $2 $3 $4".
                    If IFS is unset, the delimiter used will be always a space, if IFS is NULL, the delimiter will be nothing,
                    which effectively concatenates all the positional parameters without any delimiter.
                    When used unquoted, it will just expand to the strings, one by one, not preserving the word boundaries
                    (i.e. word splitting will split the text again, if it contains IFS characters.
@	at-sign	        The positional parameters starting from the first. When used inside doublequotes (see quoting), like "$@",
                    it expands all positional parameters as separate words: "$1" "$2" "$3" "$4"
                    Without doublequotes, the behaviour is like the one of * without doublequotes.
#	hash mark	    Number of positional parameters (decimal)
?	question mark	Status of the most recently executed foreground-pipeline (exit/return code)
-	dash	        Current option flags set by the shell itself, on invocation, or using the set builtin command.
                    It's just a set of characters, like himB for h, i, m and B.
$	dollar-sign	    The process ID (PID) of the shell. In an explicit subshell it expands to the PID of the current "main shell",
                    not the subshell. This is different from $BASHPID!
!	exclamation mark	The process ID (PID) of the most recently executed background pipeline (like started with command &)
0	zero	        The name of the shell or the shell script (filename). Set by the shell itself.
                    If Bash is started with a filename to execute (script), it's set to this filename.
                    If started with the -c <CMDLINE> option (commandline given as argument), then $0 will be the first argument after the given <CMDLINE>.
                    Otherwise, it is set to the string given on invocation for argv[0]. Unlike popular belief, $0 is not a positional parameter.
_	underscore	    A kind of catch-all parameter. Directly after shell invocation, it's set to the filename used to invoke Bash,
                    or the absolute or relative path to the script, just like $0 would show it.
                    Subsequently, expands to the last argument to the previous command. Placed into the environment when executing commands,
                    and set to the full pathname of these commands. When checking mail, this parameter holds the name of the mail file currently being checked.

# brace expansion
    Brace expansion is used to generate arbitrary strings. The specified strings are used to generate all possible combinations with the optional surrounding preambles and postscripts.

    {string1,string2,...,stringN}
    {<START>..<END>}
    {<START>..<END>..<INCR>} (Bash 4)
    <PREAMBLE>{........}
    {........}<POSTSCRIPT>
    <PREAMBLE>{........}<POSTSCRIPT>

# strict mode
    Let's start with the punchline. Your bash scripts will be more robust, reliable and maintainable if you start them like this:
        #!/bin/bash
        set -euo pipefail
        IFS=$'\n\t'
    I call this the unofficial bash strict mode. This causes bash to behave in a way that makes many classes of subtle bugs impossible. You'll spend much less time debugging, and also avoid having unexpected complications in production.
    There is a short-term downside: these settings make certain common bash idioms harder to work with. Most have simple workarounds, detailed below: jump to Issues & Solutions. But first, let's look at what these obscure lines actually do.
    set -e
        The set -e option instructs bash to immediately exit if any command [1] has a non-zero exit status.

    set -u
        set -u affects variables. When set, a reference to any variable you haven't previously defined - with the exceptions of $* and $@ - is an error, and causes the program to immediately exit.

    set -o pipefail
        This setting prevents errors in a pipeline from being masked. If any command in a pipeline fails, that return code will be used as the return code of the whole pipeline. By default, the pipeline's return code is that of the last command - even if it succeeds. Imagine finding a sorted list of matching lines in a file:

        % grep some-string /non/existent/file | sort
        grep: /non/existent/file: No such file or directory
        % echo $?
        0
        (% is the bash prompt.) Here, grep has an exit code of 2, writes an error message to stderr, and an empty string to stdout. This empty string is then passed through sort, which happily accepts it as valid input, and returns a status code of 0. This is fine for a command line, but bad for a shell script: you almost certainly want the script to exit right then with a nonzero exit code... like this:

        % set -o pipefail
        % grep some-string /non/existent/file | sort
        grep: /non/existent/file: No such file or directory
        % echo $?
        2

    Setting IFS
        The IFS variable - which stands for Internal Field Separator - controls what Bash calls word splitting. When set to a string, each character in the string is considered by Bash to separate words. This governs how bash will iterate through a sequence. For example, this script:

        #!/bin/bash
        IFS=$' '
        items="a b c"
        for x in $items; do
            echo "$x"
        done

        IFS=$'\n'
        for y in $items; do
            echo "$y"
        done
        ... will print out this:

        a
        b
        c
        a b c
