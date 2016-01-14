//
//  Snow.cpp
//  weather
//
//  Created by 藤野宏樹 on 2015/12/13.
//
//

#include "Snow.h"

void Snow::setup(string image_file){
    // 位置ベクトルと速度ベクトル初期化
    for(int i = 0; i < NUM; i++){
        pos[i].x = ofGetWidth()/2;
        pos[i].y = ofGetHeight()/2;
        vel[i].x = ofRandom(-1, 1);
        vel[i].y = ofRandom(-1, 1);
        vel[i].z = ofRandom(-1, 1);
    }
    //画像データの読込み
    myImage.loadImage(image_file);
}

void Snow::update(){
    // 位置ベクトル更新
    for(int i = 0; i < NUM; i++){
        pos[i] += vel[i];
        if(pos[i].x < 0 || pos[i].x > ofGetWidth() || pos[i].y < 0 || pos[i].y > ofGetHeight() || pos[i].z < -500 || pos[i].z > 700){
            pos[i].x = ofGetWidth()/2;
            pos[i].y = ofGetHeight()/2;
            pos[i].z = ofRandom(-100, 500);
        }
    }
}

void Snow::draw(){
    ofSetColor(255, 192, 203);
    ofFill();
    glEnable(GL_DEPTH_TEST);
    myImage.draw(0,0, ofGetWidth(), ofGetHeight());
    //ofSetColor(255, 192, 203);
    for(int i = 0; i < NUM; i++){
        ofPushMatrix();
        ofTranslate(pos[i]);
        ofCircle(0, 0, 4);
        ofPopMatrix();
    }
    glDisable(GL_DEPTH_TEST);
}
