a=$1
b=$2
c=$3
D=$((b*b - 4*a*c))
echo $D


s=$(echo "scale=4; sqrt($s)" | bc -l)

if [ $D -gt 0 ]; then
bool=1
elif [ $D -eq 0 ]; then
bool=0
else
bool=-1
fi

echo "hello"
echo $bool 

case $bool in
	-1)
	echo No real roots
	;;
	0)
	echo "Roots are real and equal"
	exp=$((b/(2*a)))
	echo $exp
	;;
	1)
	echo "Roots are distinct"
	sqrt_res=$((sqrt($D)))
	exp1=$((($b+$sqrt_res)/(2*a)))
	exp2=$((($b-$sqrt_res)/(2*a)))
	;;
esac

