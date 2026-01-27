

array = []
def search( left: int, right:int, val:int): 
	if(left> right): 
		return -1
	mid = int((left+right)/2)
	if(array[mid] == val):
		 return mid
	if( array[mid] < val):
		return search(mid+1, right, val)
	return search(left, mid-1, val)
	
	

n = int(input("enter array length"))
for i in range(0, n):
	st= int(input("enter numbers"))
	array.append(st)

val = int(input("enter number to be searched"))	

res = search(0, n-1, val)

print(f"result: {res}")
	

	
