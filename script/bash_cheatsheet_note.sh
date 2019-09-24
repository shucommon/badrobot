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
