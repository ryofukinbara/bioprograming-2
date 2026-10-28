#include "image.hpp"

typedef unsigned char uchar;

int main(void){
    Image gray_image("gray.png");
    Image binarize_image(gray_image.w, gray_image.h, 3);

    int hist[256] = {0};
    int total = gray_image.w * gray_image.h;
    int total_sum = 0;

    for(int y=0; y<gray_image.h; y++){
        for(int x=0; x<gray_image.w; x++){
            int v=gray_image.GetPixel(y, x, 0);
            hist[v]++;
            total_sum += v; 
        }
    }
}