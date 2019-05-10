pid=$1
name=$2
if [[ -d /proc/$pid/task ]]; then
    cd /proc/$pid/task
    for i in *; do echo -n "$i:"; grep $name $i/status; done;
else
    echo $pid not exist 
fi
