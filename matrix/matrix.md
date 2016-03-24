# matrix

record which one
make images %width (top auto?)
try ftp onto webfaction?
sort out blog
salts tomorrow


### style

bootstrap: dev/bootstrap.md
fix css/scss
bootstrap css should go in styles as sass... but how?
put them in styles folder as .scss, deployed as css but not linked to from HTML, not concatenated into main.css

https://learn.jquery.com/using-jquery-core/css-styling-dimensions/
http://stackoverflow.com/questions/3730035/how-to-change-css-using-jquery
http://code.dougneiner.com/coding/using-css-classes-for-states.html

### timings

Jon re
ajax timing messages - or record in-memory and send with results dump (serialize JSON)
delay on vbox ff btwn div show and background (tiles) change - show div should be last thing- it is!
use bb-quizzes/matrix/app/scripts/timer.js

## defer

record User agent js: `document.getElementById('UserAgent').value = navigator.userAgent;`
detect device: bb-quizzes/matrix/app/scripts/detect.js
jslint: general/dev/js/jslint/jslint.md
bb-quizzes/notes/2016-03-21.md
ay has dvd of original flash games
disable back button? user should not be able to have second try
compass, Bourbon, Neat
css sprites-

underscore.js for templates? looks like compative with IE6+
http://stackoverflow.com/questions/10657313/jquery-underscore-js-templating-compatible-with-ie-6
https://visionmedia.github.io/page.js/
https://dev.windows.com/en-us/microsoft-edge/tools/vms/windows/
emmet, bemmet
ctrl-m - match bracket
JsFormat: install with package manager. right-click to use.
[HTML-CSS-JS Prettify](https://packagecontrol.io/packages/HTML-CSS-JS%20Prettify)

>"brace_style": "end-expand", // [collapse|expand|end-expand|none] Put braces on the same line as control statements (default), or put braces on own line (Allman / ANSI style), or just put end braces on own line, or attempt to keep them where they are

### general

Why so little progress? Borked yo/npm stuff, Occ health, (Optimor), ?, working out how to ftp with gulp, working out how to alt-tab (ctrl-tab) in vbox....
Need to: find decent time to catch up over coming days. e.g. tomorrow night. forward!

### browser compatibility

Testing re remote browser testing-
http://kangax.github.io/compat-table/es6/ awesome!

OldIE jQuery switching

        <!-- jQuery 1.9 for IE lt 9 -->
        <!--[if lt IE 9]>
            <script src="http://code.jquery.com/jquery-1.9.0.js"></script>
            <script src="http://code.jquery.com/jquery-migrate-1.0.0.js"></script>
        <![endif]-->
        <!--[if gte IE 9]><!-->
            <script src="/bower_components/jquery/dist/jquery.js"></script>
        <!--<![endif]-->    
        <!-- <script src="jquery-1.9.0.js"></script> -->

and this:

    <script src="scripts/data.js"></script>

ok, ftp command in yo-test, now can ftp...

## defer

general\dev\js\yeoman\borked.md
sort out prev/next-/
Preload
State machine object-/
Arrays-
jshint-
cpp JSON-x
Interstitial-/
Prev Next showPage()-/
ay re server, ie support-
biobank favicon, apple-touch-icon.png?
work out how to display part of css icon- background-position

### look at Snap-/

#### tidbits

    # submitting the data
    <form id="form1" class="viz" action="https://trials.ctsu.ox.ac.uk/~webfu/HMDB3/StoreData.php" method="post">
        <input type="hidden" name="sid" value="1">

    window.history.forward();                                           # prevent repeat after back button
    window.onbeforeunload = function(e){return "are you sure?";};       # if window close received
    window.onbeforeunload = null;                                               # disable quit check
    document.getElementById("responses").value = JSON.stringify(returnData);    # prepare response data
    document.getElementById("form1").submit();                                  # send it
    document.getElementById("leftpicture").src = images[left].src;      # set an image
    document.getElementById("rightpicture").src = images[right].src;
    document.getElementById(id).style.backgroundColor = "Yellow";       # e.g. to highlight
    document.getElementById("abandonbutton").style.display = "none";            # hide
    document.getElementById("abandondiv").style.display = "inline";             # show
    clearTimeout(twoSeconds);
    twoSeconds = setTimeout("backs()", 2000);                                   # set timer
    document.onkeydown = spaceBar;                                              # register callback for keydown on whole page
    document.getElementById("test").onmousedown = touchScreen;                  # register callback for mousedown on element
    document.onblur = focusHere;                                                # if focus lost, reset to specific element
    document.getElementById("test").focus();                                    # focus
    var KeyID = (window.event) ? event.keyCode : e.keyCode;                     # get keypress
    switch (KeyID) { case 32:                                                   # spacebar
    var divList = ["demo0", "demo1", "demo2", "demo3", "demo4", "test", "xdemo", "snapdemo", "endit", "wait"]; # I need one of these...
    images[i] = new Image();
    images[i].src = "Snap/snap_images/F"+i+".GIF";      # pre-load images
    if (typeof window.performance !== 'undefined' && typeof window.performance.now !== 'undefined') # ??
    if (this.hasPerformance)
        nowish = window.performance.now();
    else
        nowish = new Date().getTime();
    if(obj.hasOwnProperty(key))

#### funcs

    # snap.js
    function abandonit(x)
    function entryselect()              document.getElementById("instructions").style.display = "inline";
    function writeValue(id, value)      document.getElementById(id).value = value;
    function switchDiv(target) 
            demo_timer.lap();
            writeValue("demoelapsed", demo_timer.getElapsed());
            test_timer.now();
            starttest();
    function showcards(left, right) 
    function showcardsdemo(left, right) 
    function starttest() 
    function focusHere() 
    function touchScreen() 
    function spaceBar(e) 
    function backs() 
    function selectPair() 
    function responder()
    function finishIt() 
    function highlight(id)
    function unhighlight(id)
    function loaded() 


    # script.js
    function SelectRadio(buttonId) 
    function Script_noBackButton()

    # json2.js
    # json stuff

    # hmTimer.js
    function getObjectLength(obj)
    var hmTimer = function()
    hmTimer.prototype.getTime = function()
    hmTimer.prototype.findnow = function()
    hmTimer.prototype.now = function()
    hmTimer.prototype.lap = function()
    hmTimer.prototype.getElapsed = function()
    hmTimer.prototype.gethasPerformance = function()
    hmTimer.prototype.gethasPossibleError = function()
    hmTimer.prototype.copy = function()
    hmTimer.prototype.getStart = function()
    hmTimer.prototype.getLap = function()
    hmTimer.prototype.isValid = function()

    # biobank_cb_common.js
    function highlight(id)
    function unhighlight(id)
    function unhighlight(id,colour)
    function now()

/general/dev/js/prototypes.md

### window.performance

/general/dev/js/performance.md

general/dev/js/jslint/jslint.md

general/dev/js/gulp/gulp.md


### back end

create Rosetta, e.g. ROSETTA *g = new ROSETTA(); in /jonathanpr/BioBankQuizGames/tMatrixBoard.cpp
/home/cbird/Projects/bb-quizzes/matrix/app/pages.html

## done

get one screen working, with clickable solution, delay and move to nexts-
copy divs, hide by default
sticky footer https://getbootstrap.com/examples/sticky-footer/
http://getbootstrap.com/examples/sticky-footer-navbar/
use $.get(url, data, success) to get part of html e.g.:

    var page = $.get("./pages/pages.html", function(data) {
        $("#content-container").html($(data).filter("#intro2"));
    });

divs for grids: 2x2 + 3x2,  3x3 + 4x2- pages.html

are pages/screens fixed? why the data matrices?
or as many as you can do in 2 minutes - up to 18?
work out how to display part of css icon

>manipulating CSS in javascript can be considered poor practice. Consider add/remove/toggling classes. – Austin Aug 5 '15 at 18:06

>Please add a non-JQuery alternative to the answer. So many new developers think that jQuery *is* Javascript