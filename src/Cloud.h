//
//  Cloud.h
//  weather
//
//  Created by 藤野宏樹 on 2015/12/13.
//
//

#ifndef __weather__Cloud__
#define __weather__Cloud__

#include <stdio.h>
#include "ofMain.h"

#endif /* defined(__weather__Cloud__) */

#define CLOUD_NUM 10
class Cloud{
public:
    void setup(float x, float y);
    void update();
    void draw();
    
    ofPoint pos; // 場所
};