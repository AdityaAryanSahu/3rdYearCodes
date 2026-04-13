with open("file.txt", "r") as infile:
    data = infile.read()

with open("output1.txt", "w") as outfile:
    outfile.write(data[::-1])
