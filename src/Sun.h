//
//  Sun.h
//  weather
//
//  Created by 藤野宏樹 on 2015/12/13.
//
//

#ifndef __weather__Sun__
#define __weather__Sun__

#include <stdio.h>
#include "ofMain.h"

#define SUN_NUM 50

#endif /* defined(__weather__Sun__) */

class Sun{
    
    private:
        ofImage sunImage; // 背景画像
        ofVec3f pos[SUN_NUM]; // 光の位置ベクトル
        ofVec3f vel[SUN_NUM]; // 光の速度ベクトル
        ofImage myImage; // 背景画像
        clock_t start_time, now_time; // 経過時間
        float rad; // ラジアン
        float deg; // 角度
        float alpha; // ラジアン
        string image_name; // 画像のファイル名
    
    public:
        void setup(string image_file);
        void update();
        void draw();
};