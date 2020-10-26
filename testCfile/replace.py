import os
dir="./"  #文件夹名称
filelist=[]
for i in os.listdir(dir):  #遍历整个文件夹
    path = os.path.join(dir, i)
    if os.path.isfile(path):  #判断是否为一个文件，排除文件夹
        if os.path.splitext(path)[1]==".c":  #判断文件扩展名是否为“.jpg”
            filelist.append(i)
for i in filelist:
    print(i)

for i in filelist:
    f = open(i, "r", encoding = "utf-8")
    str1 = f.read()
    print(str1)
    str2 = str1.replace("__VERIFIER_nondet_int()", "0")
    ff = open(i, "w")
    ff.write(str2)
    ff.flush