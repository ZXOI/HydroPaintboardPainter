from PIL import Image
import json
import sys
import math

DataPath = ".\\tasks.txt"

if len(sys.argv) < 4:
    print("ImageToData.py <ImagePath> <LeftTopX> <LeftTopY>")
    quit()

try:
    im = Image.open(sys.argv[1])
except:
    print('Open image ' + sys.argv[1] + ' failed.')
    quit()

if im.mode != "P":
    print("Index image required. Please read README.md for more information.")
    quit()

img_array = im.load()

# try:
#     with open(DataPath, 'r') as boardjson:
#         board = json.load(boardjson)
# except:

w, h = im.size
# print(w,h)

s=""
for i in range(w):
    for j in range(h):
        # e=""
        # # x=convert(img_array[i,j])
        # if img_array[i,j] != 0:
        #     for k in range(2-int(math.log10(float(img_array[i,j])))):
        #         e=e+" "
        # else:
        #     e="  "
        # print(img_array[i,j],end=e)
        s=s+str(i + int(sys.argv[2]))+" "+str(j + int(sys.argv[3]))+" "+str(img_array[i,j])+"\n"
    # print(end="\n")
# print(s)
with open(DataPath, 'w+') as f:
    f.write(s)
print("Finished converting image.")
