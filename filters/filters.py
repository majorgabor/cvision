import math
import numpy as np

class Filters:
    def __init__(self):
        super().__init__()
        print("Filters ready to use!")

    # def medianFilter(self, input_img, kernel_size):

    def verticalFilter(self, original_img, kernel_size=3):
        if kernel_size != 3:
            exit()
        else:
            kernel = np.array([[-1,0,1],[-1,0,1],[-1,0,1]])

        out_img = np.zeros( (original_img.shape[0]-kernel_size+1, original_img.shape[1]-kernel_size+1), dtype=np.uint8)
        return self._apply_kernel(original_img, kernel, out_img)


    def horizontalFilter(self, original_img, kernel_size=3):
        if kernel_size != 3:
            pass
        else:
            kernel = np.array([[-1,-1,-1],[0,0,0],[1,1,1]])

        out_img = np.zeros( (original_img.shape[0]-kernel_size+1, original_img.shape[1]-kernel_size+1), dtype=np.uint8)
        return self._apply_kernel(original_img, kernel, out_img)

    def _apply_kernel(self, original_img, kernel, result_img):
        for m in range(result_img.shape[1]):
            for n in range(result_img.shape[0]):
                result_img[n][m] = int( np.abs( np.sum( kernel * original_img[n:n+kernel.shape[0], m:m+kernel.shape[1]] ) ) )
        return result_img

    def gaussianFilter(self, original_img, kernel_size=3, sigma=1):
        kernel_size = kernel_size if kernel_size % 2 else kernel_size+1
        values = np.random.normal(0, sigma, math.ceil(kernel_size/2))
        values = np.abs(values)
        values = np.sort(values)
        values = values.reshape(-1,1)
        values = np.concatenate((values, values[0:-1][::-1]), axis=0)

        kernel_avg = 1/np.sum(values)**2

        out_img = np.zeros( (original_img.shape[0]-kernel_size+1, original_img.shape[1]-kernel_size+1), dtype=np.uint8)

        for m in range(out_img.shape[1]):
            for n in range(out_img.shape[0]):
                out_img[n][m] = int( kernel_avg * np.dot( np.dot(np.transpose(values), original_img[n:n+kernel_size, m:m+kernel_size]) , values ) )
        
        return out_img