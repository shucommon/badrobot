pid=$1
pos=$2
if [[ -d /proc/$pid/fdinfo ]]; then
    cd /proc/$pid/fdinfo
    for i in *; do 
        _pos=`cat $i | grep pos | cut -d: -f2`
        echo "$i-pos: " $_pos
        if [[ $_pos == $pos ]]; then
            echo alert;
        fi
        done
else
    echo $pid not exist 
fi
