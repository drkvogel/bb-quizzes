# matrix


copy divs
clone()

look at Snap-/
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

