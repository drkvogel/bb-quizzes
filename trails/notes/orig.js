// jshint ignore: start
/*
Graphics in jonathanpr\webserver\htdocs\HMDB3\TrailMaking\*
*/

var totelapsed_hmTimer = null;
var levelapsed_hmTimer = null;
var click_hmTimer = null;

var timerErrors = 0;

var level = 1;  //1:practicea, 2:parta, 3:practiceb, 4:partb
var abandon = 0;
var timeOut;  //v0.16 User inactivity timeout variable
var currentDiv = 0;
var divList = ["practicea", "parta", "practiceb", "partb", "wait"];
var divRoot = divList[0];
var nextCircle = 0;
var trialTypes = ["0", "1", "0", "1"];
var returnData = {};
var levelErrors = 0;
var attempt = 0;

var imageList = [  'TrailMaking/practice_a_gifs/s01.gif'
                 , 'TrailMaking/practice_a_gifs/s12.gif'
                 , 'TrailMaking/practice_a_gifs/s23.gif'
                 , 'TrailMaking/practice_a_gifs/s34.gif'
                 , 'TrailMaking/practice_a_gifs/s45.gif'
                 , 'TrailMaking/practice_a_gifs/s56.gif'
                 , 'TrailMaking/practice_a_gifs/s67.gif'
                 , 'TrailMaking/practice_a_gifs/s78.gif'
                 , 'TrailMaking/practice_a_gifs/tmt_practice_a.gif'
                 , 'TrailMaking/part_a_gifs/part_a_back.gif'
                 , 'TrailMaking/part_a_gifs/part_a_red.gif'
                 , 'TrailMaking/part_a_gifs/t01.gif'
                 , 'TrailMaking/part_a_gifs/t12.gif'
                 , 'TrailMaking/part_a_gifs/t23.gif'
                 , 'TrailMaking/part_a_gifs/t34.gif'
                 , 'TrailMaking/part_a_gifs/t45.gif'
                 , 'TrailMaking/part_a_gifs/t56.gif'
                 , 'TrailMaking/part_a_gifs/t67.gif'
                 , 'TrailMaking/part_a_gifs/t78.gif'
                 , 'TrailMaking/part_a_gifs/t89.gif'
                 , 'TrailMaking/part_a_gifs/t910.gif'
                 , 'TrailMaking/part_a_gifs/t1011.gif'
                 , 'TrailMaking/part_a_gifs/t1112.gif'
                 , 'TrailMaking/part_a_gifs/t1213.gif'
                 , 'TrailMaking/part_a_gifs/t1314.gif'
                 , 'TrailMaking/part_a_gifs/t1415.gif'
                 , 'TrailMaking/part_a_gifs/t1516.gif'
                 , 'TrailMaking/part_a_gifs/t1617.gif'
                 , 'TrailMaking/part_a_gifs/t1718.gif'
                 , 'TrailMaking/part_a_gifs/t1819.gif'
                 , 'TrailMaking/part_a_gifs/t1920.gif'
                 , 'TrailMaking/part_a_gifs/t2021.gif'
                 , 'TrailMaking/part_a_gifs/t2122.gif'
                 , 'TrailMaking/part_a_gifs/t2223.gif'
                 , 'TrailMaking/part_a_gifs/t2324.gif'
                 , 'TrailMaking/part_a_gifs/t2425.gif'
                 , 'TrailMaking/part_a_gifs/tmt_part_a.gif'
                 , 'TrailMaking/practice_b_gifs/practice_b_red.gif'
                 , 'TrailMaking/practice_b_gifs/s_1.gif'
                 , 'TrailMaking/practice_b_gifs/s1A.gif'
                 , 'TrailMaking/practice_b_gifs/sA2.gif'
                 , 'TrailMaking/practice_b_gifs/s2B.gif'
                 , 'TrailMaking/practice_b_gifs/sB3.gif'
                 , 'TrailMaking/practice_b_gifs/s3C.gif'
                 , 'TrailMaking/practice_b_gifs/sC4.gif'
                 , 'TrailMaking/practice_b_gifs/s4D.gif'
                 , 'TrailMaking/practice_b_gifs/tmt_practice_b.gif'
                 , 'TrailMaking/part_b_gifs/t_1.gif'
                 , 'TrailMaking/part_b_gifs/t1A.gif'
                 , 'TrailMaking/part_b_gifs/tA2.gif'
                 , 'TrailMaking/part_b_gifs/t2B.gif'
                 , 'TrailMaking/part_b_gifs/tB3.gif'
                 , 'TrailMaking/part_b_gifs/t3C.gif'
                 , 'TrailMaking/part_b_gifs/tC4.gif'
                 , 'TrailMaking/part_b_gifs/t4D.gif'
                 , 'TrailMaking/part_b_gifs/tD5.gif'
                 , 'TrailMaking/part_b_gifs/t5E.gif'
                 , 'TrailMaking/part_b_gifs/tE6.gif'
                 , 'TrailMaking/part_b_gifs/t6F.gif'
                 , 'TrailMaking/part_b_gifs/tF7.gif'
                 , 'TrailMaking/part_b_gifs/t7G.gif'
                 , 'TrailMaking/part_b_gifs/tG8.gif'
                 , 'TrailMaking/part_b_gifs/t8H.gif'
                 , 'TrailMaking/part_b_gifs/tH9.gif'
                 , 'TrailMaking/part_b_gifs/t9I.gif'
                 , 'TrailMaking/part_b_gifs/tI10.gif'
                 , 'TrailMaking/part_b_gifs/t10J.gif'
                 , 'TrailMaking/part_b_gifs/tJ11.gif'
                 , 'TrailMaking/part_b_gifs/t11K.gif'
                 , 'TrailMaking/part_b_gifs/tK12.gif'
                 , 'TrailMaking/part_b_gifs/t12L.gif'
                 , 'TrailMaking/part_b_gifs/tL13.gif'
                 , 'TrailMaking/part_b_gifs/tmt_part_bb.gif'  ];
//
var images = [];
for(var i in imageList)
{    //pre-load images
    images[i] = new Image();
    images[i].src = imageList[i];
}
var now0 = now();
var isReady = true; //prevent double-clicking
var isTest = false; //div contains a test
//var allSelects = "";   //list of all selects and times
var redT = [];   //global background timeout
var circlesList = [];
for (i = 0; i < 4; i++)
{
    circlesList[i] = [];
}
var a = "A";

circlesList[0]=["1","2","3","4","5","6","7","8"];

for(i=0;i<25;i++)
    circlesList[1][i]=""+(i+1);
for(i=0;i<4;i++)
    circlesList[2][2*i]=""+(i+1);
for(i=0;i<4;i++)
   circlesList[2][2*i+1]=String.fromCharCode(a.charCodeAt()+i);
for(i=0;i<13;i++)
    circlesList[3][2*i]=""+(i+1);
for(i=0;i<12;i++)
    circlesList[3][2*i+1]=String.fromCharCode(a.charCodeAt()+i);

var imgDims=[[450,274],[450,546],[450,274],[450,546]];
var imgFactor=[0.75,0.75,0.75,0.75];
var screenFactor = 0.9;

var relpos = ["relpospa", "relposa", "relpospb", "relposb"];

var hasTimedOut = false;

var areas = [[],[],[],[]];
areas[0].push(["apr0","245,167,20"]);
areas[0].push(["apr1","285,66,20"]);
areas[0].push(["apr2","384,127,20"]);
areas[0].push(["apr3","325,156,20"]);
areas[0].push(["apr4","353,236,20"]);
areas[0].push(["apr5","97,217,20"]);
areas[0].push(["apr6","48,117,20"]);
areas[0].push(["apr7","176,111,20"]);

areas[1].push(["aa0","277,390,20"]);
areas[1].push(["aa1","213,452,20"]);
areas[1].push(["aa2","319,452,20"]);
areas[1].push(["aa3","327,208,20"]);
areas[1].push(["aa4","206,267,20"]);
areas[1].push(["aa5","263,321,20"]);
areas[1].push(["aa6","185,356,20"]);
areas[1].push(["aa7","86,440,20"]);
areas[1].push(["aa8","107,490,20"]);
areas[1].push(["aa9","156,445,20"]);
areas[1].push(["aa10","206,511,20"]);
areas[1].push(["aa11","35,516,20"]);
areas[1].push(["aa12","65,287,20"]);
areas[1].push(["aa13","29,336,20"]);
areas[1].push(["aa14","29,69,20"]);
areas[1].push(["aa15","72,159,20"]);
areas[1].push(["aa16","149,36,20"]);
areas[1].push(["aa17","178,158,20"]);
areas[1].push(["aa18","284,117,20"]);
areas[1].push(["aa19","206,110,20"]);
areas[1].push(["aa20","236,29,20"]);
areas[1].push(["aa21","406,84,20"]);
areas[1].push(["aa22","419,493,20"]);
areas[1].push(["aa23","370,282,20"]);
areas[1].push(["aa24","355,508,20"]);

areas[2].push(["bpr0","245,167,20"]);
areas[2].push(["bpr1","285,66,20"]);
areas[2].push(["bp2r","384,127,20"]);
areas[2].push(["bpr3","325,156,20"]);
areas[2].push(["bpr4","353,236,20"]);
areas[2].push(["bpr5","97,217,20"]);
areas[2].push(["bpr6","48,117,20"]);
areas[2].push(["bpr7","177,101,20"]);

areas[3].push(["bb0","228,232,20"]);
areas[3].push(["bb1","323,387,20"]);
areas[3].push(["bb2","175,420,20"]);
areas[3].push(["bb3","203,111,20"]);
areas[3].push(["bb4","234,169,20"]);
areas[3].push(["bb5","327,286,20"]);
areas[3].push(["bb6","277,80,20"]);
areas[3].push(["bb7","386,78,20"]);
areas[3].push(["bb8","380,246,20"]);
areas[3].push(["bb9","381,472,20"]);
areas[3].push(["bb10","233,457,20"]);
areas[3].push(["bb11","130,498,20"]);
areas[3].push(["bb12","155,225,20"]);
areas[3].push(["bb13","90,381,20"]);
areas[3].push(["bb14","65,90,20"]);
areas[3].push(["bb15","108,268,20"]);
areas[3].push(["bb16","149,79,20"]);
areas[3].push(["bb17","342,29,20"]);
areas[3].push(["bb18","416,29,20"]);
areas[3].push(["bb19","408,409,20"]);
areas[3].push(["bb20","422,520,20"]);
areas[3].push(["bb21","38,521,20"]);
areas[3].push(["bb22","23,337,20"]);
areas[3].push(["bb23","56,452,20"]);
areas[3].push(["bb24","32,40,20"]);

var practiceaList = ["s01", "s12", "s23", "s34", "s45", "s56", "s67", "s78"];
var partaList = ["t01", "t12", "t23", "t34", "t45", "t56", "t67", "t78", "t89", "t910", "t1011", "t1112", "t1213", "t1314", "t1415", "t1516", "t1617", "t1718", "t1819", "t1920", "t2021", "t2122", "t2223", "t2324", "t2425"];
var practicebList = ["s_1", "s1a", "sa2", "s2b", "sb3", "s3c", "sc4", "s4d"];
var partbList = ["t_1", "t1a", "ta2", "t2b", "tb3", "t3c", "tc4", "t4d", "td5", "t5e", "te6", "t6f", "tf7", "t7g", "tg8", "t8h", "th9", "t9i", "ti10", "t10j", "tj11", "t11k", "tk12", "t12l", "tl13"];
var lines = [practiceaList, partaList, practicebList, partbList];
var redBack = ["practice_a_red", "part_a_red", "practice_b_red", "part_b_red"];
var whiteBack = ["practice_a_back","part_a_back","practice_b_back","part_b_back"];
var testGif = ["tmt_practice_a","tmt_part_a","tmt_practice_b","tmt_part_b"];

function resize1Tmt(id,w,h)
{
    document.getElementById(id).style.width = w;
    document.getElementById(id).style.height = h;
}

function resizeTmt()
{   //resize images in a function to keep variables local
   var bodywidth = $("body").outerWidth();
   var bodyheight = $("body").outerHeight()-$('#abandonbar').outerHeight();

   for (var i = 1; i <= 3; i = i + 2)
   {
       var sizeFactor = ((bodywidth / imgDims[i][0] > bodyheight / imgDims[i][1]) ? bodyheight / imgDims[i][1] : bodywidth / imgDims[i][1]) * screenFactor;
       imgFactor[i - 1] = sizeFactor;
       imgFactor[i] = sizeFactor;
   }

    for (i = 0; i <= 3;i++ )
    {
        var w = Math.floor(imgDims[i][0] * imgFactor[i]) + "px";
        var h = Math.floor(imgDims[i][1] * imgFactor[i]) + "px";
        resize1Tmt(relpos[i], w, h);
        resize1Tmt(testGif[i], w, h);
        for(var k in areas[i])
            area_resize(areas[i][k][0], areas[i][k][1], imgFactor[i]);

        resize1Tmt(redBack[i], w, h);
        resize1Tmt(whiteBack[i], w, h);
        for(var j in lines[i])
             resize1Tmt(lines[i][j],w,h);

        if(i==0)
            document.getElementById("tmttd").style.width = w;
    }
}

function area_resize(areaId, baseCoords, factor)
{
  var newCoords = "";
  var baseCoordsArray = String(baseCoords).split(",");

  for (var i = 0; i < baseCoordsArray.length; i++)
  {
      if (String(baseCoordsArray[i]).length > 0)
      {
          if (i < 2)
              newCoords += String(parseInt(Math.floor(factor * parseInt(String(baseCoordsArray[i])))));//coords
          else
              newCoords += String(parseInt(Math.ceil(factor * parseInt(String(baseCoordsArray[i])))));//radius
      }
      if (i < baseCoordsArray.length - 1)
          newCoords += ",";
  }
  document.getElementById(areaId).coords = newCoords;
}

function clicked(x)
{
    var now1 = now();
    clearTimeout(timeOut);

    if (hasTimedOut)
    {
        hasTimedOut = false;
        timedOutNext();
        return;
    }

    if(isReady)
    {
        timeOut=setTimeout("abandonit(3)",30000);
        isReady = false;
        now0 = now1;
        if (goodAttempt(x))
        {
            if(endCircles())
            {
                levelapsed_hmTimer.lap();
                timerErrors += levelapsed_hmTimer.gethasPossibleError();
                document.getElementById("levelelapsed"+level).value = levelapsed_hmTimer.getElapsed();

                if (divRoot == "practicea")
                {
                    isReady = false;
                    document.getElementById("praca_inst").style.display = "none";
                    document.getElementById("parta_inst").style.display = "inline";
                    clearTimeout(timeOut);
                }
                else if (divRoot == "practiceb")
                {
                    isReady = false;
                    document.getElementById("pracb_inst").style.display = "none";
                    document.getElementById("partb_inst").style.display = "inline";
                    clearTimeout(timeOut);
                }
                else
                    gotoNextLevel();
            }
            else
                isReady = true;
        }
        else
            isReady = true;
    }
}

function clearRed()
{
    document.getElementById(redBack[level]).style.display = "none";
}

function nextDiv1()
{
    now0 = now();
    nextDiv();
}

function abandonit(x)
{
    if (abandon != 1)
    {
        switch (x)
        {
            case 0: //abandon button
                clearTimeout(timeOut);
                document.getElementById("abandonbutton").style.display = "none";
                document.getElementById("abandondiv").style.display = "inline";
                document.getElementById("abandonyes").style.display = "inline";
                document.getElementById("abandonno").style.display = "inline";
                break;
            case 1: //yes - abandon
                document.getElementById("abandondiv").style.display = "none";
                document.getElementById("abandonyes").style.display = "none";
                document.getElementById("abandonno").style.display = "none";
                document.getElementById("abandon").value = 1;
                nextDiv1();
                break;
            case 2: //no - cancel
                document.getElementById("abandonbutton").style.display = "inline";
                document.getElementById("abandondiv").style.display = "none";
                document.getElementById("abandonyes").style.display = "none";
                document.getElementById("abandonno").style.display = "none";
                document.getElementById("abandon").value = 2;
                timeOut=setTimeout("abandonit(3)",30000);
                break;
            case 3: //30 second user inactivity - timeout
                hasTimedOut = true;
 //            timedOutNext();
              break;
            default:

        }
    }
}


function gotoNextLevel()
{
    endLevel();
    nextDiv();
}

function nextDiv()
{
    if(currentDiv==0)
    {
        window.onbeforeunload=null;
        window.history.forward();
        window.onbeforeunload = function(e) {return "The answers to the questions or tests you are doing at the moment will be lost - is this what you want to do?";};
    }

    if(currentDiv>=0&&level>0)
    {
        document.getElementById(divList[currentDiv]).style.display = "none";
    }

    levelapsed_hmTimer.now();
    currentDiv++;
    if(document.getElementById("abandon").value == 1||document.getElementById("abandon").value == 3)
        currentDiv = divList.length - 1;

    divRoot = divList[currentDiv];
    isTest=(divRoot == "practicea" || divRoot == "parta" || divRoot == "practiceb" || divRoot == "partb");
    if (isTest)
    {
        document.getElementById("abandonbutton").style.display = "inline";

        document.getElementById("headerdiv").style.display = "none";
        document.getElementById("nextbutton").style.display = "none";
        document.getElementById("introtable").style.display = "none";
        document.getElementById("testtable").style.display = "block";
        var dr = (divRoot == "practicea") ? 0 : (divRoot == "parta") ? 1 : (divRoot == "practiceb") ? 2 : 3;
        document.getElementById("tmttd").style.width = Math.floor(imgDims[dr][0] * imgFactor[dr]) + "px";
        document.getElementById("abandonbar").style.display = "block";
        startLevel();
    }
    else
    {
        document.getElementById("headerdiv").style.display = "inline";
        document.getElementById("introtable").style.display = "block";
        document.getElementById("testtable").style.display = "none";

        if ((divRoot!="wait")) {
            document.getElementById("nextbutton").style.display = "inline";
        } else {
            document.getElementById("abandonbutton").style.display="none";

            totelapsed_hmTimer.lap();
            document.getElementById("intro").style.display="none";

            var hasTimerError = timerErrors + totelapsed_hmTimer.gethasPossibleError() + levelapsed_hmTimer.gethasPossibleError();
            document.getElementById("timererror").value = hasTimerError;
            document.getElementById("performaceTimer").value = totelapsed_hmTimer.gethasPerformance();

            document.getElementById("responses").value = JSON.stringify(returnData);
            document.getElementById("totelapsed").value = totelapsed_hmTimer.getElapsed();
            window.onbeforeunload = null;
            document.getElementById("fm1").submit();
        }
    }
    document.getElementById(divList[currentDiv]).style.display = "block";// "inline"; This fails on IE7
    if(divList[currentDiv]=="practicea"||divList[currentDiv]=="practiceb"||currentDiv>=divList.length-1) {
       clearTimeout(timeOut);
    } else {
        clearTimeout(timeOut);
        timeOut=setTimeout("abandonit(3)",30000);
    }
}

function startLevel() {
    nextCircle = 0;
    levelErrors = 0;
    isReady = true;
    startCircle();
}

function startCircle() {
    click_hmTimer.now();
    attempt = 0;
}

function goodAttempt(x) {
    click_hmTimer.lap();
    timerErrors += click_hmTimer.gethasPossibleError();

    mark=(x == nextCircle)?1:0;
    clearTimeout(redT[level]);
    if(mark==1) {
        document.getElementById(redBack[level]).style.display = "none";
        document.getElementById(lines[level][x]).style.display = "block";
    }
    else
    {
       levelErrors++;
        document.getElementById(redBack[level]).style.display = "block";
        redT[level] = setTimeout("clearRed()", 200);
    }
    attempt++;

    var circleNo = "";
    if (circlesList[level].length > x)
        circleNo= circlesList[level][x];

    var newD = {};
    newD["tn"] = (level+1);
    newD["tc"]=(nextCircle+1);
    newD["at"]=attempt;
    newD["pa"]=(((level+1)<=2)?"A":"B")
    newD["tt"]=trialTypes[level];
    newD["ex"]=circlesList[level][nextCircle];
    newD["sl"]=circleNo;
    newD["es"]=click_hmTimer.getElapsed();   //ONLY RESET ON CORRECT CLICK
    newD["mt"]=mark;
    returnData[getObjectLength(returnData)] = newD;

    if (mark)
        click_hmTimer.now();
    return (mark==1);
}

function endCircles()
{
    nextCircle++;

    var response=(nextCircle >= lines[level].length);
   if(!response)
        startCircle();
    return response;
}

function endLevel()
{
    document.getElementById("levelerrors"+level).value = levelErrors;
    level++;
}

function timedOutNext()
{
  document.getElementById("abandon").value = 3;
  document.getElementById("timeoutdiv").style.display = "none";
  document.getElementById("timeoutnext").style.display = "none";
    nextDiv1();
}

function loaded()
{
    window.onbeforeunload=null;
    window.history.forward();
    window.onbeforeunload=function(e){return "The answers to the questions or tests you are doing at the moment will be lost - is this what you want to do?";};

    resizeTmt();
    level = 0;
    currentDiv = -1;

    totelapsed_hmTimer = new hmTimer();
    levelapsed_hmTimer = new hmTimer();
    click_hmTimer = new hmTimer();

    totelapsed_hmTimer.now();
    nextDiv();
}

