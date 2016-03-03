# matrix


copy divs
clone()




### look at Snap-/

#### tidbits

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


are pages/screens fixed? why the data matrices?
or as many as you can do in 2 minutes - up to 18?
is this 

http://getbootstrap.com/examples/sticky-footer-navbar/

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

sticky footer https://getbootstrap.com/examples/sticky-footer/
use $.get(url, data, success) to get part of html e.g.:

    var page = $.get("./pages/pages.html", function(data) {
        $("#content-container").html($(data).filter("#intro2"));
    });

divs for grids: 2x2 + 3x2,  3x3 + 4x2- pages.html

### event delegation

jQuery event delegation: /dev/event-delegation.html
Use 

```js
    $("some-element").on("click", function() { ... });
```

rather than 

```js
    $("some-element").click(function() { ... });
```

as on() supports several parameter combinations that allow it to handle event delegation.
http://stackoverflow.com/questions/9122078/difference-between-onclick-vs-click

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

