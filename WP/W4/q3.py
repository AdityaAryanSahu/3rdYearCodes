
array = []
n = int(input("enter number of strings"))
for i in range(0, n):
	st= input("enter string")
	array.append(st)
	
	
array.sort()
	
for i in range(0, n-1):
	for j in range( 0, n-1-i):
		if(array[j]> array[j+1]):
			array[j], array[j+1] = array[j+1], array[j]
			
for i in range(0, n):
	print(array[i])
