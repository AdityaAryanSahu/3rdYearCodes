class POW:
	def __init__(self):
		print("obj init")
		
	def getPOW(self,x:int ,n:int):
		self.res =x**n
		
	def printPOW(self):
		print(self.res)
		
obj= POW()
obj.getPOW(2,5)
obj.printPOW()
