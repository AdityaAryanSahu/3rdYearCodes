class StringClass:
	def __init__(self):
		print("obj initialized")
		
	def get_string(self):
		self.tr = input("enter a string")
		
	def print_string(self):
		print(f"initilised string:{self.tr.upper()}")
		
		
new_obj = StringClass()
new_obj.get_string()
new_obj.print_string()
		
