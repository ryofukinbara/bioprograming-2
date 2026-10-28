#include "image.hpp"

typedef unsigned char uchar;

int main(void){
    Image sample("sample.png");
    Image gray_image(sample.w, sample.h, 3);

    for(int y=0; y<sample.h; y++){
        for(int x=0; x<sample.w; x++){
            uchar r = sample.GetPixel(y, x, 0);
            uchar g = sample.GetPixel(y, x, 1);
            uchar b = sample.GetPixel(y, x, 2);

            uchar v = (r+g+b)/3;

            gray_image.SetPixel(y, x, 0, v);
            gray_image.SetPixel(y, x, 1, v);
            gray_image.SetPixel(y, x, 2, v);
        }
    }

    gray_image.save("gray.png");

    return 0;
}