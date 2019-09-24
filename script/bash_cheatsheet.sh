#!/bin/bash

# 1. variable
NAME="Qiang"
echo $NAME
echo "$NAME"
echo "${NAME}!"

# example
echo "Hello $NAME!"

# 2. string quotes
echo "Hi $NAME"  #=> Hi Qiang 
echo 'Hi $NAME'  #=> Hi $NAME

# 3. conditional execution
# git commit && git push
# git commit || echo "Commit failed"

# 4. conditionals
# details see bash_cheatsheet_note.sh in the same folder
## 4.1 conditions example
if ping -c 1 google.com; then
  echo "It appears you have a working internet connection"
fi

if grep -q 'ls' ~/.bash_history; then
  echo "You appear to have typed 'ls' in the past"
fi

## 4.2 String
if [[ -z "$string" ]]; then
  echo "String is empty"
elif [[ -n "$string" ]]; then
  echo "String is not empty"
fi

## 4.3 Combinations
if [[ X ]] && [[ Y ]]; then
    echo "x and y both true"  
fi

## 4.4 Equal
if [[ "$A" == "$B" ]]; then
    echo "a == b"
fi

## 4.5 Regex
s1='hello'
s2='w'
s3='h'
if [[ $s1 =~ $s2 ]]; then
    echo "hello not =~ w"
elif [[ $s1 =~ $s3 ]]; then
    echo "hello =~ h"
fi

a=1
b=2
if (( $a < $b )); then
   echo "$a is smaller than $b"
fi

if [[ -e "file.txt" ]]; then
  echo "file exists"
fi

# 5. functions
## 5.1 Defining functions
myfunc() {
    echo "hello $1"
}

# Same as above (alternate syntax)
function myfunc() {
    echo "hello $1 $2"
    echo "number of argc $#"
}

myfunc "Qiang" "Guo"

get_name() {
    echo "Qiang"
}
echo "You are $(get_name)"

# returning values
myfunc() {
    local myresult='some value'
    echo $myresult
}
result="$(myfunc)"
echo $result

# arguments
# see bash_cheatsheet_note.sh for details
# $#	Number of arguments
# $*	All arguments
# $@	All arguments, starting from first
# $1	First argument

# Raising errors
myfunc() {
    return 1
    #echo 1
}
echo $(myfunc)
if myfunc; then
    echo "success"
else
    echo "failure"
fi
