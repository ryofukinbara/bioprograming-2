#include "image.hpp"

typedef unsigned char uchar;

int main(void){
    Image gray_image("gray.png");
    Image binarize_image(gray_image.w, gray_image.h, 3);

    int hist[256] = {0};
    int total = gray_image.w * gray_image.h;
    int sum = 0;

    for(int y=0; y<gray_image.h; y++){
        for(int x=0; x<gray_image.w; x++){
            int v=gray_image.GetPixel(y, x, 0);
            hist[v]++;
            sum += v; 
        }
    }
    double mt = sum / total;

    double max_variance = 0;
    int threshold;
    for(int i=0; i<=254; i++){
        int count_b = 0;
        int sum_b = 0;
        for(int k=0; k<=i; k++){
            count_b += hist[k];
            count_b += k * hist[k];
        }
        int count_w  = total - count_b;
        int sum_w = sum - sum_b;

        if(count_b == 0 || count_w == 0){
            continue;
        }
        double m_b = sum_b / count_b;
        double m_w = sum_w / count_w;

        double variance = (count_b * (m_b - mt) * (m_b - mt) 
                           + count_w * (m_w - mt) * (m_w - mt))
                           / (count_b + count_w);
        
        if(variance > max_variance){
            max_variance = variance;
            threshold = i;
        }
    }
    for(int y=0; y<gray_image.h; y++){
        for(int x=0; x<gray_image.w; x++){
            int v=gray_image.GetPixel(y, x, 0);
            int color;

            if(v > threshold){
                color = 255;
            }else{
                color = 0;
            }
            binarize_image.SetPixel(y, x, 0, color);
            binarize_image.SetPixel(y, x, 1, color);
            binarize_image.SetPixel(y, x, 2, color);
        }
    }
    binarize_image.save("binarize.png");

    return 0;
}