pid=$1
limit=$2
if [[ -d /proc/$pid ]]; then
    cd /proc/$pid
    size=`cat status | grep VmRSS | cut -f2`
    echo "size: " $size
    if [[ $size > $limit ]]; then 
        echo alert
    fi
else
    echo $pid not exist 
fi
