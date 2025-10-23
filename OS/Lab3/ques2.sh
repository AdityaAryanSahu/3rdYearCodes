n=$1
i=1
num=1
while [ $i -le $n ]; do
echo $num
i=$(($i+1))
num=$(($num+2))
done


