#include "image.hpp"

typedef unsigned char uchar;

int main(void){
    Image sample("stap.png");
    Image gray_image(sample.w, sample.h, 3);
    Image equal_image(sample.w, sample.h, 3);

    int hist[256] = {0};
    int total = sample.w * sample.h;

    for(int y=0; y<sample.h; y++){
        for(int x=0; x<sample.w; x++){
            uchar r = sample.GetPixel(y, x, 0);
            uchar g = sample.GetPixel(y, x, 1);
            uchar b = sample.GetPixel(y, x, 2);

            uchar v = (r+g+b)/3;

            gray_image.SetPixel(y, x, 0, v);
            gray_image.SetPixel(y, x, 1, v);
            gray_image.SetPixel(y, x, 2, v);

            hist[v]++;
        }
    }
    int table[256] = {0};
    int cdf = 0;

    for(int k=0; k<256; k++){
        cdf += hist[k];
        table[k] = cdf * 255 / total;
    }
    for(int y=0; y<sample.h; y++){
        for(int x=0; x<sample.w; x++){
        int v = gray_image.GetPixel(y, x, 0);
        int s = table[v];

        equal_image.SetPixel(y, x, 0, s);
        equal_image.SetPixel(y, x, 1, s);
        equal_image.SetPixel(y, x, 2, s);
        }
    }
    gray_image.save("stap_gray.png");
    equal_image.save("stap_equalized.png");

    return 0;
}

//考察
//STAP細胞の電気泳動画像をヒストグラム平坦化したことで、画像の左から三番目のレーンが
//他の部分と自然に繋がっておらず、切り貼りされたように見えることが分かった。これは、
//ヒストグラム平坦化によって画像のコントラストが強調され、元の画像では目立たなかった
//明るさの違いや境界が明確になった体と考えられる。