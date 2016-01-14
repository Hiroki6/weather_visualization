array=new Array(46);
list=[
"http://rss.weather.yahoo.co.jp/rss/days/1400.xml",
"http://rss.weather.yahoo.co.jp/rss/days/3110.xml",
"http://rss.weather.yahoo.co.jp/rss/days/3310.xml",
"http://rss.weather.yahoo.co.jp/rss/days/3410.xml",
"http://rss.weather.yahoo.co.jp/rss/days/3210.xml",
"http://rss.weather.yahoo.co.jp/rss/days/3510.xml",
"http://rss.weather.yahoo.co.jp/rss/days/3610.xml",
"http://rss.weather.yahoo.co.jp/rss/days/4010.xml",
"http://rss.weather.yahoo.co.jp/rss/days/4110.xml",
"http://rss.weather.yahoo.co.jp/rss/days/4210.xml",
"http://rss.weather.yahoo.co.jp/rss/days/4310.xml",
"http://rss.weather.yahoo.co.jp/rss/days/4510.xml",
"http://rss.weather.yahoo.co.jp/rss/days/4410.xml",
"http://rss.weather.yahoo.co.jp/rss/days/4610.xml",
"http://rss.weather.yahoo.co.jp/rss/days/5410.xml",
"http://rss.weather.yahoo.co.jp/rss/days/5510.xml",
"http://rss.weather.yahoo.co.jp/rss/days/5610.xml",
"http://rss.weather.yahoo.co.jp/rss/days/5710.xml",
"http://rss.weather.yahoo.co.jp/rss/days/4910.xml",
"http://rss.weather.yahoo.co.jp/rss/days/4810.xml",
"http://rss.weather.yahoo.co.jp/rss/days/5210.xml",
"http://rss.weather.yahoo.co.jp/rss/days/5010.xml",
"http://rss.weather.yahoo.co.jp/rss/days/5110.xml",
"http://rss.weather.yahoo.co.jp/rss/days/5310.xml",
"http://rss.weather.yahoo.co.jp/rss/days/6010.xml",
"http://rss.weather.yahoo.co.jp/rss/days/6110.xml",
"http://rss.weather.yahoo.co.jp/rss/days/6200.xml",
"http://rss.weather.yahoo.co.jp/rss/days/6310.xml",
"http://rss.weather.yahoo.co.jp/rss/days/6410.xml",
"http://rss.weather.yahoo.co.jp/rss/days/6510.xml",
"http://rss.weather.yahoo.co.jp/rss/days/6910.xml",
"http://rss.weather.yahoo.co.jp/rss/days/6810.xml",
"http://rss.weather.yahoo.co.jp/rss/days/6610.xml",
"http://rss.weather.yahoo.co.jp/rss/days/6710.xml",
"http://rss.weather.yahoo.co.jp/rss/days/8120.xml",
"http://rss.weather.yahoo.co.jp/rss/days/7110.xml",
"http://rss.weather.yahoo.co.jp/rss/days/7200.xml",
"http://rss.weather.yahoo.co.jp/rss/days/7310.xml",
"http://rss.weather.yahoo.co.jp/rss/days/7410.xml",
"http://rss.weather.yahoo.co.jp/rss/days/8210.xml",
"http://rss.weather.yahoo.co.jp/rss/days/8510.xml",
"http://rss.weather.yahoo.co.jp/rss/days/8410.xml",
"http://rss.weather.yahoo.co.jp/rss/days/8610.xml",
"http://rss.weather.yahoo.co.jp/rss/days/8310.xml",
"http://rss.weather.yahoo.co.jp/rss/days/8710.xml",
"http://rss.weather.yahoo.co.jp/rss/days/8810.xml",
"http://rss.weather.yahoo.co.jp/rss/days/9110.xml"
]
// 繝｢繧ｸ繝･繝ｼ繝ｫ縺ｮ蜿悶ｊ霎ｼ縺ｿ
var osc = require('node-osc');
var OF_PORT = 8000;
var client = new osc.Client('127.0.0.1', OF_PORT);
var parseString = require('xml2js').parseString;
var request = require('request');
setInterval(function(){
  for(var i = 0; i < 47; i++) {
    request(list[i],function (err, response, body) {
      parseString(body, function(err, obj) {
        var items=obj.rss.channel[0].item;
        var item =items[0];
        var item2=item.description[0];
        var re=new RegExp("-");
        var item3=re.exec(item2)
        var item4=item2.toString();    
        var item5=item4.substring(0,item3.index);    
        var re1=new RegExp("/");
        var item6=re1.exec(item2);
        var item7=item4.substring(item3.index+1,item6.index);
        var item8=item4.substring(item6.index+1);
        item7 = item7.replace("℃","");
        item8 = item8.replace("℃","");
        array[i]=new Array(3);
        array[i][0]=item5;
        array[i][1]=item7;
        array[i][2]=item8;
      var weather=array[i][0];
        weather=weather.toString();
        weather=weather.substr(0,1);
      if(weather=="曇"){weather="晴"};
      array[i][0]=weather;
      client.send('/test', weather);
      client.send('/test', item7);
      client.send('/test', item8);
      console.log(weather);
      console.log(item7);
      console.log(item8);
    });
    });
  }
},10000);
