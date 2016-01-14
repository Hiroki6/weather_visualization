//
//  Snow.h
//  weather
//
//  Created by 藤野宏樹 on 2015/12/13.
//
//

#ifndef __weather__Snow__
#define __weather__Snow__

#include <stdio.h>
#include <vector>
#include "ofMain.h"

#define NUM 250

#endif /* defined(__weather__Snow__) */

class Snow{

    private:
        ofImage myImage; // 画像ファイル
        string region_name; //
        ofVec3f pos[NUM]; // 雪の位置ベクトル
        ofVec3f vel[NUM]; // 雪の速度ベクトル

    public:
        void setup(string image_file);
        void update();
        void draw();
    
};
