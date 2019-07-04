#/bin/bash

interval=1
filename="capture/logcap.pcap"

while getopts "if:" opt; do
    case "$opt" in
        i)  
            interval=$OPTARG
            ;;

        f)  
            filename=$OPTARG
            ;;

        p)
            
    esac
done

#rm $filename
touch $filename
chmod 777 $filename
COMMAND="dumpcap -w $filename -B 200 -i wlp1s0 -s 50"

eval $COMMAND
echo "end"
