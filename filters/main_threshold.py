import cv2
import numpy as np

if __name__ == "__main__":
    
    img = cv2.imread("bookpage.jpg")
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    _, threshold = cv2.threshold(img, 12, 255, cv2.THRESH_BINARY)
    _, threshold2 = cv2.threshold(img_gray, 12, 255, cv2.THRESH_BINARY)
    threshold_adaptive = cv2.adaptiveThreshold(img_gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 115, 1)

    threshold_gray = cv2.cvtColor(threshold, cv2.COLOR_BGR2GRAY)

    cv2.imshow("original", img)
    cv2.imshow("treshold", threshold)
    cv2.imshow("tresholded gray scale", threshold2)
    cv2.imshow("gray scaled treshold", threshold_gray)
    cv2.imshow("adaptive threshold", threshold_adaptive)
    cv2.waitKey(0)
    cv2.destroyAllWindows()