#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofBackground(25, 100, 214);
    ofSetCircleResolution(64);
    ofEnableAlphaBlending();
    receiver.setup(PORT); // 指定したポートで接続
    japanImage.loadImage("japan.png");
    start_time = clock(); // スタート時間初期化
    connect_number = 0; // 通信回数を初期化
    // 文字入力読み込み
    region_font.loadFont("AquaKana.ttc", 40);
    comment.loadFont("AquaKana.ttc", 10);
    japanese_font.loadFont("AquaKana.ttc", 40);
    weather_font.loadFont("AquaKana.ttc", 20, true, true);
    temp_font.loadFont("AquaKana.ttc", 20);
    setupWeathers(); // 天気配列を初期化
    weather = 0; // 天気初期化
    prefecture = 0; // 県を初期化
    region = 0; // 地域を初期化
    getWeather = false; // 天気情報を取得したかどうかのフラグ
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
    getOscMessage();
    if(weather == SUNNY){
        sun.update();
    }else if(weather == RAIN){
        rain.update();
    }else if(weather == SNOW){
        snow.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 0, 200);
    if(getWeather){
        ofCircle(30, ofGetHeight()-30, 20);
    }
    ofSetColor(255);
    switch (weather) {
        case MAP:
            japanese_font.drawString(L"日本の天気", 50, 50);
            japanImage.draw(20, 20, ofGetWidth()-50, ofGetHeight()-50);
            comment.drawString("Press 'r' to show snow", ofGetWidth()-300, ofGetHeight()-80);
            break;
        case SUNNY:
            drawTemp();
            ofSetColor(255);
            sun.draw();
            break;
        case RAIN:
            //ofSetBackgroundAuto(false);
            drawTemp();
            ofSetColor(255, 255, 255, 23);
            rain_image.draw(0, 0, ofGetWidth(), ofGetHeight());
            rain.draw();
            break;
        case SNOW:
            drawTemp();
            snow.draw();
            break;
    }
    ofSetColor(0, 200, 200);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // bボタンで日本地図に戻る
    if(key == 'b'){
        region = 0;
        prefecture = 0;
        ofSetBackgroundAuto(true);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofBackground(25, 100, 214);
        weather = MAP;
        weather_sound.stop();
    }
    // rボタンで雪表示
    /*if(key == 'r'){
        if(region == 0){
            weather = SNOW;
            region = 11;
            weather_sound.loadSound("snow.mp3");
            weather_sound.play();
        }
    }*/
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // マウスを押したときの座標でregionを決定する
    if(region == 0){
        prefecture = getPrefecture(ofGetMouseX(), ofGetMouseY()); // 県を取得する
        // 地域を取得(0~9)
        region = getRegion(prefecture);
        // 日本地図以外かつ情報がとれていれば
        if(prefecture != 0 && weathers[prefecture-1][0] != ""){
            if(weathers[prefecture-1][0] == "晴"){ // 晴れのとき
                weather = SUNNY;
                weather_sound.loadSound("canon.mp3");
                weather_sound.play();
                sun.setup(file_names[region-1][0]);
                ofSetBackgroundAuto(false);
            }else if(weathers[prefecture-1][0] == "雨"){ // 雨のとき
                weather = RAIN;
                weather_sound.loadSound("Xenoblade.mp3");
                weather_sound.play();
                ofSetBackgroundAuto(true);
                ofBackground(0);
                rain_image.loadImage(file_names[region-1][1]);
                rain_image.draw(0, 0, ofGetWidth(), ofGetHeight());
                rain.setup();
            }else if(weathers[prefecture-1][0] == "雪"){
                weather = SNOW;
                weather_sound.loadSound("snow.mp3");
                weather_sound.play();
                snow.setup(file_names[region-1][1]);
            }
        }else{
            prefecture = 0;
            region = 0;
            weather = 0;
        }
    }
}

// OSCメッセージの取得
void ofApp::getOscMessage(){
    now_time = clock();
    // 一定時間通信が無ければconnect_numberをリセット
    if(((double)(now_time - start_time) / CLOCKS_PER_SEC) > 0.1){
        if(connect_number >= 130){
            connect_number = 0;
        }
        start_time = clock();
    }
    // 現在順番待ちのOSCメッセージがあるか確認
    while(receiver.hasWaitingMessages()){
        if(!getWeather) getWeather = true;
        prefecture_index = connect_number/3;
        weather_index = connect_number%3;
        // 次のメッセージを取得
        ofxOscMessage message;
        receiver.getNextMessage(&message);
        string msg_string;
        msg_string = "";
        for(int i = 0; i < message.getNumArgs(); i++){
            if(message.getArgType(i) == OFXOSC_TYPE_INT32){
                msg_string += ofToString(message.getArgAsInt32(i));
            }else if(message.getArgType(i) == OFXOSC_TYPE_FLOAT){
                msg_string += ofToString(message.getArgAsFloat(i));
            }else if(message.getArgType(i) == OFXOSC_TYPE_STRING){
                msg_string += message.getArgAsString(i);
            }
        }
        // 情報がとれていれば入力
        if(msg_string != ""){
            weathers[prefecture_index][weather_index] = msg_string;
        }
        connect_number += 1;
    }
}

// OSCメッセージをコンソールに出力する関数
void ofApp::dumpOSC(ofxOscMessage m){
    string msg_string;
    for(int i = 0; i < m.getNumArgs(); i++){
        msg_string = "";
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg_string += ofToString(m.getArgAsInt32(i));
        }else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg_string += ofToString(m.getArgAsFloat(i));
        }else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg_string += m.getArgAsString(i);
        }
    }
    cout<<msg_string<<endl;
}

// 天気配列の初期化関数
void ofApp::setupWeathers(){
    for(int i = 0; i < PREFECTURE_NUM; i++){
        for(int j = 0; j < WEATHER_INFO; j++){
            weathers[i][j] = "";
        }
    }
}

// 気温を出力する関数
void ofApp::drawTemp(){
    ofSetColor(200, 50, 0);
    region_font.drawString(prefecture_name[prefecture-1], 50, 50);
    weather_font.drawString(L"最高", 50, 100);
    temp_font.drawString(weathers[prefecture-1][1], 100, 100);
    weather_font.drawString(L"度", 180, 100);
    weather_font.drawString(L"最低", 50, 150);
    temp_font.drawString(weathers[prefecture-1][2], 120, 150);
    weather_font.drawString(L"度", 180, 150);
    comment.drawString("Press 'b' to back map", ofGetWidth()-300, ofGetHeight()-50);
}

// マウスの位置から地域取得
int ofApp::getPrefecture(int x, int y){
    if(x >= 1078 && x <= 1225 && y >= 52 && y <= 190){
        return 1; // 北海道
    }else if(x >= 1078 && x <= 1225 && y >= 235 && y <= 273){
        return 2; // 青森
    }else if(x >= 1152 && x <= 1225 && y >= 277 && y <= 315){
        return 3; // 岩手
    }else if(x >= 1152 &&  x <= 1225 && y >= 317 && y <= 358){
        return 4; // 宮城
    }else if(x >= 1078 && x <= 1150 && y >= 277 && y <= 315){
        return 5; // 秋田
    }else if(x >= 1078 && x <= 1150 && y >= 317 && y <= 358){
        return 6; // 山形
    }else if(x >= 1078 && x <= 1225 && y >= 360 && y <= 400){
        return 7; // 福島
    }else if(x >= 1152 && x <= 1225 && y >= 403 && y <= 482){
        return 8; // 茨城
    }else if(x >= 1078 && x <= 1150 && y >= 403 && y <= 441){
        return 9; // 栃木
    }else if(x >= 968 && x <= 1072 && y >= 403 && y <= 441){
        return 10; // 群馬
    }else if(x >= 968 && x <= 1150 && y >= 444 && y <= 482){
        return 11; // 埼玉
    }else if(x >= 1152 && x <= 1225 && y >= 486 && y <= 568){
        return 12; //千葉
    }else if(x >= 1078 && x <= 1150 && y >= 486 && y <= 525){
        return 13; // 東京
    }else if(x >= 968 && x <= 1072 && y >= 528 && y <= 568){
        return 14; // 神奈川
    }else if(x >= 892 && x <= 1072 && y >= 360 && y <= 400){
        return 15; // 新潟
    }else if(x >= 817 && x <= 888 && y >= 360 && y <= 400){
        return 16; // 富山
    }else if(x >= 742 && x <= 815 && y >= 317 && y <= 400){
        return 17; // 石川
    }else if(x >= 666 && x <= 815 && y >= 403 && y <= 441){
        return 18; // 福井
    }else if(x >= 968 && x <= 1072 && y >= 486 && y <= 525){
        return 19; // 山梨
    }else if(x >= 892 && x <= 965 && y >= 403 && y <= 482){
        return 20; // 長野
    }else if(x >= 817 && x <= 888 && y >= 403 && y <= 482){
        return 21; // 岐阜
    }else if(x >= 892 && x <= 965 && y >= 486 && y <= 568){
        return 22; // 静岡
    }else if(x >= 817 && x <= 888 && y >= 486 && y <= 525){
        return 23; // 愛知
    }else if(x >= 742 && x <= 815 && y >= 486 && y <= 568){
        return 24; // 三重
    }else if(x >= 666 && x <= 815 && y >= 444 && y <= 482){
        return 25; // 滋賀
    }else if(x >= 589 && x <= 660 && y >= 444 && y <= 482){
        return 26; // 京都
    }else if(x >= 589 && x <= 660 && y >= 486 && y <= 525){
        return 27; // 大阪
    }else if(x >= 545 && x <= 585 && y >= 444 && y <= 525){
        return 28; // 兵庫
    }else if(x >= 666 && x <= 737 && y >= 486 && y <= 525){
        return 29; // 奈良
    }else if(x >= 589 && x <= 737 && y >= 528 && y <= 568){
        return 30; // 和歌山
    }else if(x >= 468 && x <= 541 && y >= 444 && y <= 482){
        return 31; // 鳥取
    }else if(x >= 395 && x <= 465 && y >= 444 && y <= 482){
        return 32; // 島根
    }else if(x >= 468 && x <= 541 && y >= 486 && y <= 525){
        return 33; // 岡山
    }else if(x >= 395 && x <= 465 && y >= 486 && y <= 525){
        return 34; // 広島
    }else if(x >= 317 && x <= 390 && y >= 444 && y <= 482){
        return 35; // 山口
    }else if(x >= 468 && x <= 541 && y >= 612 && y <= 651){
        return 36; // 徳島
    }else if(x >= 468 && x <= 541 && y >= 570 && y <= 608){
        return 37; // 香川
    }else if(x >= 395 && x <= 465 && y >= 570 && y <= 608){
        return 38; // 愛媛
    }else if(x >= 395 && x <= 465 && y >= 612 && y <= 651){
        return 39; // 高知
    }else if(x >= 196 && x <= 312 && y >= 486 && y <= 525){
        return 40; // 福岡
    }else if(x >= 153 && x <= 193 && y >= 486 && y <= 525){
        return 41; // 佐賀
    }else if(x >= 108 && x <= 148 && y >= 486 && y <= 568){
        return 42; // 長崎
    }else if(x >= 196 && x <= 238 && y >= 528 && y <= 651){
        return 43; // 熊本
    }else if(x >= 242 && x <= 312 && y >= 528 && y <= 568){
        return 44; // 大分
    }else if(x >= 242 && x <= 312 && y >= 570 && y <= 651){
        return 45; // 宮崎
    }else if(x >= 196 && x <= 312 && y >= 654 && y <= 691){
        return 46; // 鹿児島
    }else if(x >= 108 && x <= 193 && y >= 695 && y <= 733){
        return 47; // 沖縄
    }else{
        return 0; // 日本地図
    }
}

// 県から地域を取得する関数
int ofApp::getRegion(int prefecture){
    if(prefecture == 1){
        return 1; // 北海道
    }else if(prefecture > 1 && prefecture <= 7){
        return 2; // 東北
    }else if(prefecture > 7 && prefecture <= 14){
        return 3; // 関東
    }else if(prefecture > 14 && prefecture <= 20){
        return 4; // 北陸
    }else if(prefecture > 20 && prefecture <= 24){
        return 5; // 東海
    }else if(prefecture > 24 && prefecture <= 30){
        return 6; // 近畿
    }else if(prefecture > 30 && prefecture <= 35){
        return 7; // 中国
    }else if(prefecture > 35 && prefecture <= 39){
        return 8; // 四国
    }else if(prefecture > 39 && prefecture <= 46){
        return 9; // 九州
    }else if(prefecture == 47){
        return 10; // 沖縄
    }else{
        return 0;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    ofShowCursor();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
