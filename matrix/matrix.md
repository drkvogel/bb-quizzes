# matrix

Grids

ok, ftp command in yo-test, now can ftp...

## defer

general\dev\js\yeoman\borked.md
sort out prev/next-/
tea-
Preload
State machine object-/
Arrays-
jshint-
cpp JSON-x
Interstitial-/
Prev Next showPage()-/
ay re server, ie support-
biobank favicon, apple-touch-icon.png?

### scripts not being refreshed, 

even with `gulp serve` restart:

    cbird@q108-vlubuntu:~/Projects/bb-quizzes/matrix$ ll app/scripts/main.js 
    -rw-rw-r-- 1 cbird cbird 3.9K Mar  4 12:11 app/scripts/main.js
    cbird@q108-vlubuntu:~/Projects/bb-quizzes/matrix$ ll .tmp/scripts/main.js
    -rw-rw-r-- 1 cbird cbird 3.8K Mar  4 12:04 .tmp/scripts/main.js

because there are errors in yo script, g!

### how to log from gulp?

https://github.com/gulpjs/gulp-util

    npm install gulp-util --save-dev

    var gutil = require('gulp-util');
    gutil.log('Hello world!');


### clone() or show()/hide()

was thinking of using get() or load() to load the different pages in, but this involves a network wait.
best to include all sub pages in same html page, and switch them in by changing visibility - the way the Healthy Minds snap game works - or clone().

work out how to display part of css icon

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

### prototypes

re timer object - why are funcs added to prototype instead of declared in function object? e.g. why not:

    var Timer = function() {
        ...
        getTime = function() { ... };
    };

instead of:

    var Timer = function() {
        ...
    };
    Timer.prototype.getTime = function() { ... };

? Because in the first instance, each time Timer is created, everything is copied including the functions, but in the second, only the stuff in the body is copied, and references to prototyped functions are pointers to the prototype. So saves memory.

### window.performance

>The Web Performance API allows web pages access to certain functions for measuring the performance of web pages and web applications

    if (typeof window.performance !== 'undefined' && typeof window.performance.now !== 'undefined')
        this.hasPerformance = true;
    this.hasPossibleError = false;
    this.isValid = false;

    hmTimer.prototype.getTime = function() {
        if (this.hasPerformance)
            nowish = window.performance.now();  // ms.μs from performance.timing.navigationStart()
        else
            nowish = new Date().getTime();      // milliseconds elapsed since 1 January 1970 00:00:00 UTC

Date.now() returns the , performance.now() returns the number of , the start of navigation of the document, to the performance.now() call. Another important difference between Date.now() and performance.now() is that the latter is monotonically increasing, so the difference between two calls will never be negative.

[performance.now() vs Date.now()](http://stackoverflow.com/questions/30795525/performance-now-vs-date-now)

performance.now() should only be used when you want to measure the **relative** distance between two time points, not their "absolute" position in time. plus, performance.now offers more precise timing (sub-millisecond precision).

http://stackoverflow.com/questions/16808486/explanation-of-window-performance-javascript

---

are pages/screens fixed? why the data matrices?
or as many as you can do in 2 minutes - up to 18?
work out how to display part of css icon

## defer

underscore.js for templates? looks like compative with IE6+
http://stackoverflow.com/questions/10657313/jquery-underscore-js-templating-compatible-with-ie-6

https://visionmedia.github.io/page.js/
https://dev.windows.com/en-us/microsoft-edge/tools/vms/windows/
emmet, bemmet
JsFormat: install with package manager. right-click to use.
ctrl-m - match bracket

[HTML-CSS-JS Prettify](https://packagecontrol.io/packages/HTML-CSS-JS%20Prettify)

>"brace_style": "end-expand", // [collapse|expand|end-expand|none] Put braces on the same line as control statements (default), or put braces on own line (Allman / ANSI style), or just put end braces on own line, or attempt to keep them where they are

### back end

create Rosetta, e.g. ROSETTA *g = new ROSETTA(); in /jonathanpr/BioBankQuizGames/tMatrixBoard.cpp
/home/cbird/Projects/bb-quizzes/matrix/app/pages.html

## done

copy divs, hide by default
sticky footer https://getbootstrap.com/examples/sticky-footer/
http://getbootstrap.com/examples/sticky-footer-navbar/
use $.get(url, data, success) to get part of html e.g.:

    var page = $.get("./pages/pages.html", function(data) {
        $("#content-container").html($(data).filter("#intro2"));
    });

divs for grids: 2x2 + 3x2,  3x3 + 4x2- pages.html

### Not watching files: ENOSPC

>Error: watch /home/cbird/Projects/bb-quizzes/matrix/app/ ENOSPC

reboot to clear out /tmp. No dice.
http://unix.stackexchange.com/questions/11235/is-it-safe-to-rm-rf-tmp
http://superuser.com/questions/499039/how-to-cleanup-tmp-folder-safely-on-linux

    echo fs.inotify.max_user_watches=582222 | sudo tee -a /etc/sysctl.conf && sudo sysctl -p

or similar - ok, now it actually livereloads, i.e. when you change a file.
https://discourse.roots.io/t/gulp-watch-error-on-ubuntu-14-04-solved/3453/2
http://stackoverflow.com/questions/535768/what-is-a-reasonable-amount-of-inotify-watches-with-linux

---

