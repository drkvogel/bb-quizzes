
# Trails grok

from C:\Users\cbird\Projects\tmp\webserver\webserver\htdocs\HMDB3\Trailmaking
/home/kvogel/Projects/bb-quizzes/trails/notes/orig/trailtest.php
/home/kvogel/Projects/bb-quizzes/trails/notes/orig/trailtest.js

    > a = "A"
    'A'
    > a.charCodeAt()
    65
    > String.fromCharCode(65)
    'A'


```js
var level = 1; // 1:practicea, 2:parta, 3:practiceb, 4:partb
var redT = []; //global background timeout
var screenFactor = 0.9;
var imgDims = [[450, 274], [450, 546], [450, 274], [450, 546] ];
var imgFactor = [0.75, 0.75, 0.75, 0.75];
var divList = ["practicea", "parta", "practiceb", "partb", "wait"];
var relpos = ["relpospa", "relposa", "relpospb", "relposb"];
var trialTypes = ["0", "1", "0", "1"];
areas[0].push(["apr0", "245,167,20"]); // image map

function loaded() {
    window.onbeforeunload = null;
    window.history.forward();
    window.onbeforeunload = function(e) {
        return "The answers to the questions or tests you are doing at the moment will be lost - is this what you want to do?";
    };
    resizeTmt();
    level = 0;
    currentDiv = -1;
    totelapsed_hmTimer = new hmTimer();
    levelapsed_hmTimer = new hmTimer();
    click_hmTimer = new hmTimer();
    totelapsed_hmTimer.now();
    nextDiv();
}


```
