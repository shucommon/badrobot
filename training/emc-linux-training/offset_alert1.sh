pid=$1
pos=$2
if [[ -d /proc/$pid/fdinfo ]]; then
    cd /proc/$pid/fdinfo
    while 1; do
        for i in *; do 
            _pos=`cat $i | grep pos | cut -f2`
            echo "$i-pos: " $_pos
            if [[ $_pos == $pos ]]; then
                echo alert;
            fi
            done
    done
else
    echo $pid not exist 
fi
