#pragma once

#include "ofMain.h"
#include "Cloud.h"
#include "Sun.h"
#include "Snow.h"
#include "Rain.h"
#include "ofxOsc.h"
#include "ofxTrueTypeFontUC.h"


#define PORT 8000 // ポート番号
#define PREFECTURE_NUM 47 // 都道府県の数
#define WEATHER_INFO 3 // 天気情報の数
#define REGION_NUM 10 // 地域の数
#define MAP 0 // 日本地図を出力する状態
#define SUNNY 1 // 晴れの状態
#define RAIN 2 // 雨の状態
#define SNOW 3 // 雪の状態

class ofApp : public ofBaseApp{
    
    private:
        Sun sun; // 晴れオブジェクト
        Cloud cloud; // 雲りオブジェクト
        Snow snow; // 雪オブジェクト
        Rain rain; // 雨オブジェクト
        ofxOscReceiver receiver; // OSCメッセージを受信するインスタンス
        ofImage japanImage; // 日本地図
        ofImage rain_image; // 雨のときの画像
        string weathers[PREFECTURE_NUM][WEATHER_INFO]; // 地域ごとの天気
        clock_t start_time, now_time; // 経過時間
        bool connect_flag; // 通信があるかどうかのフラグ(一定間隔無かったらfalse)
        int connect_number; // 通信回数
        int region; // 地域を表す数値(0,..10) // 0は日本地図
        ofTrueTypeFont region_font; // 地域名
        ofTrueTypeFont temp_font; // 気温
        ofxTrueTypeFontUC japanese_font; // 日本地図
        ofxTrueTypeFontUC weather_font; // 最高気温
        ofTrueTypeFont comment; // バックコメント
        int prefecture_index; // 県のインデックス
        int prefecture; // 県を表す番号
        int weather_index; // 天気情報のインデックス[
        int weather; // 天気の情報(0が地図),1が晴れ, 2が雨, 3が雪
        bool getWeather; // 天気の情報を取得したかどうかのフラグ
        ofSoundPlayer weather_sound; // 天気別音楽
        // 県の名前配列
        string prefecture_name[PREFECTURE_NUM] = {"Hokkaido", "Aomori", "Iwate", "Miyagi", "Akita", "Yamagata", "Fukushima", "Ibaragi", "Tochigi", "Gunma", "Saitama", "Chiba", "Tokyo", "Kanagawa", "Nigata", "Toyama", "Ishikawa", "Fukui", "Yamanashi", "Nagano", "Gifu", "Shozuoka", "Aichi", "Mie", "Shiga", "Kyoto", "Oosaka", "Hyougo", "Nara", "Wakayama", "Tottori", "Shimane", "Okayama", "Hiroshima", "Yamaguchi", "Tokushima", "Kagawa", "Ehime", "Kouchi", "Fukuoka", "Saga", "Nagasaki", "Kumamoto", "Oita", "Miyazaki", "Kagoshima", "Okinawa"};
        // 地域ごとの晴れと雨の画像ファイル名
        string file_names[REGION_NUM][2] = {{"hokkaido_sunny.jpg", "hokkaido_rain.jpg"}, {"touhoku_sunny.jpg", "touhoku_rain.jpg"}, {"kantou_sunny.jpg", "kantou_rain.jpg"}, {"hokuriku_sunny.jpg", "hokuriku_rain.jpg"}, {"toukai_sunny.jpg", "toukai_rain.jpg"}, {"kinki_sunny.jpg", "kinki_rain.jpg"}, {"tyuugoku_sunny.jpg", "tyuugoku_rain.jpg"}, {"shikoku_sunny.jpg", "shikoku_rain.jpg"}, {"kyuusyuu_sunny.jpg", "kyuusyuu_rain.jpg"}, {"okinawa_sunny.jpg", "okinawa_rain.jpg"}};

    public:
        void setup();
        void update();
        void draw();
        
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        void dumpOSC(ofxOscMessage m); // OSCから受け取ったデータを出力する関数
        void getOscMessage(); // OSCによるメッセージを取得する関数
        int getPrefecture(int x, int y); // マウスの座標から地域を取得する
        void setupWeathers(); // 天気を初期化
        int getRegion(int prefecture); // 県から地域を取得
        void drawTemp(); // 気温表示関数

};
