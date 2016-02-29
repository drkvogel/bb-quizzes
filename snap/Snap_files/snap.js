
var abandoning = false;    //abandon button clicked, awaiting confirmation
var abandon = 0;          //task abandon - do not allow more abandon clicks
var stopped = false;        //abandon button prevented next pair of cards from being shown

var demo_timer = null;
var total_timer = null;
var test_timer = null;
var reaction_timer = null;

var missing=-9999;
var available=true; //input control - turn off when test ends
var isready = false;    //input valid/not valid - capture both
var thissnap = false;   //true if cards match
var stimulusCount = -1;  //stimulus number 
var images = [];        //array for image sources
var randomsnap = [0,0,1,1];  //0 - different; 1 - snap.
randomsnap[4] = (Math.random() < 0.5) ? 0 : 1;  //one of each plus one random
var leftarray = [0, 1, 3, 6, 7, 2, 5];
var rightarray = [0, 4, 3, 9, 8, 2, 5];
var leftpicture = rightpicture = 25;
var oneSecond;          // one second timeout for blanks
var twoSeconds;         //two second timeout for pictures

var indexa = [];
var indexb = [];
var elapsed = [];
var snap = [];
var buttonf = [];
var buttonn = [];
for(i=0;i<=maxstimulus+1;i++)
{
    indexa[i]=missing;
    indexb[i] = missing;
    buttonf[i] = 0;
    buttonn[i] = 0;
    elapsed[i] = missing;
    snap[i] = missing;
}
for (var i = 0; i <= 24; i++) 
{ //pre-load images
    images[i] = new Image();
    images[i].src = "Snap/snap_images/F"+i+".GIF";
}
images[25] = new Image();
images[25].src = "Snap/snap_images/Rear.GIF";
var randselect = [];
for (i = 10; i < 25; i++)
{ //make list of cards not used in final seven pairs.
    randselect[i - 10] = i;
}
var j;
var k;
for (i = 0; i < 15; i++)
{  //randomise list of card indices
    j = Math.floor(Math.random() * 15);
    k = randselect[j];
    randselect[j] = randselect[i];
    randselect[i] = k;
}
for(i=0;i<randomsnap.length;i++)
{
    j = Math.floor(Math.random() * randomsnap.length);
    k = randomsnap[j];
    randomsnap[j] = randomsnap[i];
    randomsnap[i] = k;
}

var returnData = {};


function abandonit(x)
{
    if (abandon != 1) 
    {
        switch (x) 
        {
            case 0: //abandon button
                document.getElementById("abandonbutton").style.display = "none";
                document.getElementById("abandondiv").style.display = "inline";
                document.getElementById("abandonyes").style.display = "inline";
                document.getElementById("abandonno").style.display = "inline";
                abandoning = true;
                break;
            case 1: //yes - abandon
                //cancel all timings
                abandon = 1;
                clearTimeout(oneSecond);
                clearTimeout(twoSeconds);
                document.getElementById("abandondiv").style.display = "none";
                document.getElementById("abandonyes").style.display = "none";
                document.getElementById("abandonno").style.display = "none";
                document.getElementById("abandon").value = 1;
                if (available) 
                	finishIt();
                break;
            case 2: //no - cancel
                document.getElementById("abandonbutton").style.display = "inline";
                document.getElementById("abandondiv").style.display = "none";
                document.getElementById("abandonyes").style.display = "none";
                document.getElementById("abandonno").style.display = "none";
                document.getElementById("abandon").value = 2;
                abandoning = false;
                if (stopped) 
                {
                    stopped = false;
                    oneSecond = setTimeout("selectPair()", 1000);
                }
                break;
            default:
        } 
    }
}

function entryselect()
{
    document.getElementById("instructions").style.display = "inline";
    document.getElementById("bkbd").style.display = "inline";
    document.getElementById("btsd").style.display = "none";
    document.getElementById("bkb").style.display = "inline";
    document.getElementById("ekb").style.display = "inline";
    document.getElementById("ets").style.display = "none";
    switchDiv("demo0");
}

function writeValue(id, value)
{
    document.getElementById(id).value = value;
}

function switchDiv(target) 
{    
    var now0 = now();
    var divList = ["demo0", "demo1", "demo2", "demo3", "demo4", "test", "xdemo", "snapdemo", "endit", "wait"];
    for (var i in divList)    
        document.getElementById(divList[i]).style.display = "none";
    document.getElementById("abandonbutton").style.display = "none";

    document.getElementById(target).style.display = "inline";
    if (target == "demo0") 
    {
        demo_timer.now();
        total_timer.now();
        showcardsdemo(25, 25);
    }
    else if (target == "demo2") 
    {
        window.onbeforeunload = null;
        window.history.forward();   //prevent repeat after back button
        window.onbeforeunload=function(e){return "The answers to the questions or tests you are doing at the moment will be lost - is this what you want to do?";};
        showcardsdemo(2, 2); 
    } 
    else if (target == "demo3") 
    {
    	document.getElementById("snapdemo").style.display = "inline"; 
    	showcardsdemo(2, 2);
    }
    else if (target == "demo4") 
    { 
    	document.getElementById("snapdemo").style.display = "none"; 
    	document.getElementById("xdemo").style.display = "inline"; 
    	showcardsdemo(3, 4); 
    } 
    else if (target=="wait")
    	document.getElementById("demotable").style.display = "none";
    
    if (target == "test")
    {
        document.getElementById("abandonbutton").style.display = "inline";
        document.getElementById("demo").style.display = "none";
    }
    else
        document.getElementById("demo").style.display = "inline";
    
    if (target == "test") 
    {
        demo_timer.lap();
        writeValue("demoelapsed", demo_timer.getElapsed());
        test_timer.now();
        starttest();
    }
}

function showcards(left, right) 
{
    document.getElementById("leftpicture").src = images[left].src;
    document.getElementById("rightpicture").src = images[right].src;
}

function showcardsdemo(left, right) 
{
    document.getElementById("leftpicturedemo").src = images[left].src;
    document.getElementById("rightpicturedemo").src = images[right].src;
}

function starttest() 
{
    document.getElementById("begin").style.display = "inline";
    document.onkeydown = spaceBar;
    document.getElementById("test").onmousedown = touchScreen;
    document.onblur = focusHere;
}

function focusHere() 
{
    document.getElementById("test").focus();
}

function touchScreen() 
{
    responder();
}

function spaceBar(e) 
{
    var KeyID = (window.event) ? event.keyCode : e.keyCode;
    switch (KeyID) 
    {
        case 32:
            responder();
        break;
    }
}
function backs() 
{  //show backs of cards
    isready = false; //keystrokes are premature
    stimulusCount++;
    document.getElementById("snap").style.display = "none";     //clear messages
    document.getElementById("x").style.display = "none";
    showcards(images.length - 1, images.length - 1);
    clearTimeout(oneSecond);
    if (!abandoning) 
        oneSecond = setTimeout("selectPair()", 1000);
    else 
        stopped = true;
}
function selectPair() 
{ //select two cards
    if (stimulusCount > maxstimulus) 
    {
        if (available)
        	finishIt();
    } 
    else 
    {
        if (stimulusCount < randomsnap.length) 
        {
            leftpicture = randselect.pop();
            rightpicture = (randomsnap[stimulusCount] == 1) ? leftpicture : randselect.pop();
        } 
        else 
        {
            leftpicture = leftarray[stimulusCount - randomsnap.length];
            rightpicture = rightarray[stimulusCount - randomsnap.length];
        }
        indexa[stimulusCount] = leftpicture;
        indexb[stimulusCount] = rightpicture;
        thissnap = (leftpicture == rightpicture)?1:0;
        snap[stimulusCount] = thissnap;
        showcards(leftpicture, rightpicture);

        reaction_timer.now();
        isready = true;
        clearTimeout(twoSeconds);
        twoSeconds = setTimeout("backs()", 2000);
    }
}

function responder()
{
    if (available)
    {    //data submission has not started
        reaction_timer.lap();

        if (stimulusCount < 0)
        {//Response to start test run
            stimulusCount = -1;
            document.getElementById("begin").style.display = "none";
            backs();
        } 
        else 
        {
            if (isready && (reaction_timer.getElapsed()) > 100 && stimulusCount <= maxstimulus)
            {
                if (elapsed[stimulusCount] == missing) 
                {//first valid elapsed time not yet recorded
                    elapsed[stimulusCount] = reaction_timer.getElapsed();

                    if (indexa[stimulusCount] == indexb[stimulusCount]) 
                        document.getElementById("snap").style.display = "inline";
                    else 
                        document.getElementById("x").style.display = "inline";
                }
                buttonn[stimulusCount]++;   //count button entries in two seconds
            } 
            else if (stimulusCount <= maxstimulus) 
                buttonf[stimulusCount]++;   //increment count of false (premature) button entries
            else
            {
                if (available) 
                    finishIt();
            }
        }
    }
}

function finishIt() 
{
    available = false;    //prevent multiple submissions and ignore further keystrokes
    switchDiv("wait");
    document.getElementById("abandonbutton").style.display="none";

    var snapcount=0;
    var snapstotelap=0;
    var trial_comp1 = 0;
    for (var trial_comp = 0; trial_comp <= stimulusCount; trial_comp++) 
    {
        if (trial_comp <= maxstimulus) 
        {
            trial_comp1 = trial_comp + 1;

            if (indexa[trial_comp] != missing) //if the left card not set, don't save.
            {
                var newD = {};
                newD["tc"] = trial_comp1.toString();
                newD["li"]=indexa[trial_comp].toString();
                newD["ri"]=indexb[trial_comp].toString();
                newD["su"]=snap[trial_comp].toString();
                newD["es"]=elapsed[trial_comp].toString();
                newD["fn"]=buttonn[trial_comp].toString();
                newD["bf"]=buttonf[trial_comp].toString();
                returnData[trial_comp1] = newD;
            }

            if (trial_comp >= 3 && indexa[trial_comp] == indexb[trial_comp] && elapsed[trial_comp] > 0)
            {
                snapcount++;
                snapstotelap += elapsed[trial_comp];
            }
        }
    }
    writeValue("mean", (snapcount > 0&&snapstotelap>0) ? Math.round(snapstotelap / snapcount) : -1);

    test_timer.lap();
    writeValue("testelapsed",test_timer.getElapsed());

    total_timer.lap();
    writeValue("totelapsed",total_timer.getElapsed());

//check all timers for possible dodgeyness.
    var possibleE = test_timer.gethasPossibleError() + reaction_timer.gethasPossibleError() + demo_timer.gethasPossibleError() + total_timer.gethasPossibleError();
    if (possibleE > 0)
        possibleE = 1;

    writeValue("timererror",possibleE);
    writeValue("performaceTimer",total_timer.gethasPerformance());

    document.getElementById("responses").value = JSON.stringify(returnData);
    window.onbeforeunload = null;
    document.getElementById("form1").submit();
}

function highlight(id)
{
    document.getElementById(id).style.backgroundColor = "Yellow";
}

function unhighlight(id)
{
    document.getElementById(id).style.backgroundColor = "White";
}

function loaded() 
{
    window.onbeforeunload=null;
    window.history.forward();   //prevent repeat after back button - may not work.
    window.onbeforeunload=function(e){return "The answers to the questions or tests you are doing at the moment will be lost - is this what you want to do?";};

    demo_timer = new hmTimer();
    total_timer = new hmTimer();
    test_timer = new hmTimer();
    reaction_timer = new hmTimer();

    entryselect();
}
