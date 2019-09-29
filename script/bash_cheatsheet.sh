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

# 6. shell execution
echo "I'm in $(pwd)"
echo "I'm in `pwd`"     # same
echo `ls`     # same

# 7. brace expansion
# details see bash_cheatsheet_note.sh
echo {a,b}.c # a.c b.c
echo {a,b}
echo {1..5}
echo {a,b}$PATH
a=1
b=10
# the first step just do expansions
echo {$a..$b}   # wrong, it become {1..10}
#using the eval command, which basically evaluates a commandline twice:
eval echo {$a..$b} # 1 2 3 ... 10
#for i in $(eval echo {$a..$b})
#wget http://docs.example.com/documentation/slides_part{1,2,3,4,5,6}.html
#wget http://docs.example.com/documentation/slides_part{1..6}.html
#mkdir /home/bash/test/{foo,bar,baz,cat,dog}
for i in 0{1..9} 10; do printf "%s\n" "$i";done
printf "%s\n" img{00{1..2},0{10..12},{100..102}}.png
echo $(printf "img%02d.png " {1..11})
echo -v{,,,,}
# bash 4.0
# Zero padded number expansion
echo {0001..5} # 0001 0002 0003 0004 0005
echo {1..10..2}
