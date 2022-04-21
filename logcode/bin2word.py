import struct
import os

word_path = "./test/answord.txt"
bin_path = "./test/mybin.bin"

filestr = ""

op_dict={"00":"INS","01":"REP","10":"DEL","11":"RSV"}

with open(bin_path, "rb") as binfile:
    filedata = binfile.read()
    
for num in filedata:
    filestr += '{:08b}'.format(int(num)) 

wordfile = open(word_path,'w')

strlen = len(filestr)
i = 0 
while i < strlen:
    op_list = []
    data_list = []

    if i + 50 > strlen:
        break
    op = op_dict[filestr[i:i+2]]
    start = int(filestr[i+2:i+34],2)
    length = int(filestr[i+34:i+50],2)

    if op == "DEL":
        out_str = op + " " + str(start) + " " + str(length) + '\n'
        wordfile.write(out_str)
        i += 50
        continue
    
    out_str = op + " " + str(start) + " " + str(length) + " ["
    
    for j in range(0,length):
        numstr = filestr[i+50+32*j:i+82+32*j]
        if numstr[0] == "1":
            data = -int("0"+numstr[1:],2)
        else:
            data = int(numstr,2)

        if j != length-1:
            out_str += str(data) + ','
        else:
            out_str += str(data) + ']\n'

    wordfile.write(out_str)

    i += 50+32*length
    
wordfile.close()