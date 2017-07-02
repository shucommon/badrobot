rm cscope.files
find -L . -name "*.cpp" >> ./cscope.files
find -L . -name "*.cxx" >> ./cscope.files
find -L . -name "*.c" >> ./cscope.files
find -L . -name "*.h" >> ./cscope.files
find -L . -name "*.xml" >> ./cscope.files
find -L . -name "*.asm" >> ./cscope.files
find -L . -name "*akefil*" >> ./cscope.files
find -L . -name "*.py" >> ./cscope.files
find -L . -name "*.in" >> ./cscope.files
find -L . -name "*.xml" >> ./cscope.files
cscope -b

