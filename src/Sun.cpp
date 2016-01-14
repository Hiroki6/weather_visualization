//
//  Sun.cpp
//  weather
//
//  Created by fujinohiroki on 2015/12/13.
//
//

#include "Sun.h"

void Sun::setup(string image_file){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofBackgroundHex(0x000000);
    for(int i = 0; i < SUN_NUM; i++){
        pos[i].x = 1000;
        pos[i].y = 200;
        pos[i].z = 0;
        vel[i].x = 0.5 * cos((i/(1.0*SUN_NUM))*2.0*M_PI);
        vel[i].y = 0.5 * sin((i/(1.0*SUN_NUM))*2.0*M_PI);
        vel[i].z = ofRandom(-0.5, 0.5);
    }
    image_name = image_file;
    myImage.loadImage(image_file);
    start_time = clock();
    deg = 0;
    alpha = 0;
}

void Sun::update(){
    now_time = clock();
    if(((double)(now_time - start_time) / CLOCKS_PER_SEC) > 2.0){
        this->setup(image_name);
    }
    for(int i = 0; i < SUN_NUM; i++){
        pos[i] += vel[i];
        if(deg >= 0.4) continue;
        deg += 0.00005;
    }
    alpha = 255 * sin(deg * M_PI/180.0);
}

void Sun::draw(){
    ofSetColor(255, 255, 255, int(alpha));
    myImage.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofFill();
    ofSetColor(50, 50, 30, 255);
    ofEllipse(1000, 200, 60, 60);
    glEnable(GL_DEPTH_TEST);
    ofSetColor(255, 255, 255, 150);
    for(int i = 0; i < SUN_NUM; i++){
        ofNoFill();
        ofPushMatrix();
        ofTranslate(pos[i]);
        ofCircle(0, 0, 4);
        ofPopMatrix();
    }
    glDisable(GL_DEPTH_TEST);
}
