INS_OP = "00"
REP_OP = "01"
DEL_OP = "10"
RSV_OP = "11"

word_path = "./test/myword.txt"
bin_path = "./test/ansbin.bin"

with open(word_path, "r") as wordfile:
    oplist = wordfile.readlines()

str = ""

for op in oplist:
    word = op.split(' ')
    if word[0] == "INS":
        str += INS_OP
    elif word[0] == "REP":
        str += REP_OP
    elif word[0] == "DEL":
        str += DEL_OP
    else:
        str += RSV_OP

    str += '{:032b}'.format(int(word[1]))
    str += '{:016b}'.format(int(word[2]))
    
    if word[0] != "DEL":

        data_list = word[3][1:-2].split(',')
        for data in data_list:
            if data[0] == '-':
                tmpstr = '{:032b}'.format(int(data[1:]))
                tmpstr = "1" + tmpstr[1:]
            else:
                tmpstr = '{:032b}'.format(int(data))
            str += tmpstr    

strlen = len(str)
if r := strlen % 8:
    str += "0"*(8-r)
    strlen += (8-r)
b = bytes([int(str[i:i+8], 2) for i in range(0, strlen, 8)])

with open(bin_path, "wb") as binfile:
    binfile.write(b)
