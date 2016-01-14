//
//  Rain.h
//  weather
//
//  Created by 藤野宏樹 on 2015/12/13.
//
//

#ifndef __weather__Rain__
#define __weather__Rain__

#include <stdio.h>
#include "ofMain.h"

#endif /* defined(__weather__Rain__) */

#define RAIN_NUM 100

class Rain{
    
    private:
        ofPoint rains[RAIN_NUM]; // 雨の位置ベクトル
        float vel[RAIN_NUM]; // 雨の速度ベクトル
        float rains_length[RAIN_NUM]; // 雨の長さ
        int color[RAIN_NUM]; // 雨の色
        ofImage image; // 背景画像
        
    public:
        void setup();
        void update();
        void draw();
    
};