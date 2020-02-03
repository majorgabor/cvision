import cv2
import sys
import math
import numpy as np
from filters import Filters

DEFAULT_KERNEL = 0
VERTICAL_KERNEL = 1
HORIZONTAL_KERNEL = 2

def rgb2gray(in_img):
    return np.array(np.mean(in_img, axis=2), dtype=np.uint8)

def subImg(img1, img2):
    img1_16 = img1.astype(np.int16)
    img2_16 = img2.astype(np.int16)
    res = abs(img1_16 - img2_16)
    return res.astype(np.uint8)

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("main_filter.py <relative/path/to/file>")
        exit(0)
    
    filts = Filters()

    img = cv2.imread(sys.argv[1])
    img = cv2.resize(img, (int(img.shape[1]/2), int(img.shape[0]/2)))
    cv2.imshow("original image", img)

    gray_img = rgb2gray(img)
    cv2.imshow("gray scaled", gray_img)

    vert_fil_img = filts.verticalFilter(gray_img)
    cv2.imshow("vertical filtered", vert_fil_img)
    cv2.imshow("vertical filtered diff", subImg(gray_img[1:-1,1:-1], vert_fil_img))

    horz_fil_img = filts.horizontalFilter(gray_img)
    cv2.imshow("horizontal filtered", horz_fil_img)
    cv2.imshow("horizontal filtered diff", subImg(gray_img[1:-1,1:-1], horz_fil_img))

    gauss_img = filts.gaussianFilter(gray_img,13)
    cv2.imshow("gaussian filtered", gauss_img)
    cv2.imshow("gaussian filtered diff", subImg(gray_img[6:-6,6:-6], gauss_img))

    print("to terminate pres ESC")
    cv2.waitKey(0)
    cv2.destroyAllWindows()
