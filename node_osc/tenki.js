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
var osc = require('node-osc');
var OF_PORT = 8000;
var client = new osc.Client('127.0.0.1', OF_PORT);
var parseString = require('xml2js').parseString;
var request = require('request');
setInterval(function(){
  for(var i = 0; i < 47; i++) {
    request(list[i],function (err, response, body) {
      parseString(body, function(err, obj) {
        var contents = obj.rss.channel[0].item[0].description[0]; // 天気と温度
        var re_hyphen = new RegExp("-");
        var hyphen_contents = re_hyphen.exec(contents);
        var temp_contents = contents.toString();
        var weather = contents.toString().substring(0,hyphen_contents.index);    
        var re_slash = new RegExp("/");
        var slash_contents = re_slash.exec(contents);
        var max_temp = temp_contents.substring(hyphen_contents.index+1, slash_contents.index).replace("℃","");
        var min_temp = temp_contents.substring(slash_contents.index+1).replace("℃","");
        weather = weather.toString();
        weather = weather.substr(0,1);
        if(weather == "曇") weather = "晴";
        client.send('/test', weather);
        client.send('/test', max_temp);
        client.send('/test', min_temp);
        console.log(weather);
        console.log(max_temp);
        console.log(min_temp);
      });
    });
  }
},10000);
