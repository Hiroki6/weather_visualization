//
//  Rain.cpp
//  weather
//
//  Created by 藤野宏樹 on 2015/12/13.
//
//

#include "Rain.h"

void Rain::setup(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetBackgroundAuto(false);
    // 位置ベクトルと速度ベクトル初期化
    for(int i = 0; i < RAIN_NUM; i++){
        rains[i].x = ofRandom(0, ofGetWidth());
        rains[i].y = ofRandom(0, 100);
        rains_length[i] = ofRandom(30, 50);
        vel[i] = ofRandom(1, 5);
    }
}

void Rain::update(){
    // 雨の位置更新
    for(int i = 0; i < RAIN_NUM; i++){
        rains[i].y += vel[i];
        if(rains[i].y >= ofGetHeight()){
            rains[i].y = ofRandom(0, 100);
        }
    }
}

void Rain::draw(){
    ofSetLineWidth(5);
    ofSetColor(67, 135, 233);
    for(int i = 0; i < RAIN_NUM; i++){
        ofCircle(rains[i].x, rains[i].y, 3);
    }
}
