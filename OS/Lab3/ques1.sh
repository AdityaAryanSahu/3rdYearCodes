num=$1
rem=$((num%2))
if [ $rem -eq 0 ]; then
echo "even"
else
echo "odd"
fi



