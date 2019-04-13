#!/bin/bash
find . -name '*.c' | xargs wc -l

# works on names with spaces, only outputs one number.
find ./ -name '*.c' -print0 | xargs -0 cat | wc -l
