## done

media query - use commas to apply multiple conditions (like a logical OR)
navBar should be devBar (navCtl should be navBar?) # has class="navbar" which is Bootstrap
now top image is wrong - always intro5.png!- set $('.middleImg img#introImg')
hoops scaling not working - .middleImg margins being set, but image will not scale and is pushed left...
aha - img width: 100% css: #middleImg now .middleImg

hoops - allow explanation text to be wider .container needs to be wider - currently scaled by scaleImages()
rather, new containter round images to be scaled, and apply scaleImages()
in matrix, it's .gridContainer which has the margins calculated
.container is outside that, and contains .botTxt
do the same for hoops so text can flow left and right instead of wrapping
in matrix, only 2 pages have class="gridContainer", the ones with puzzles, including the intros
several of the pages in the html are redundant - the text content comes from config.json
the pages (templates, really) in use in hoops are:

        "templateId": "home", "templateId": "intro1", "templateId": "intro6", "templateId": "game", "templateId": "thanks",

wrap each in a container with a common class that will have margins applied to it - .middleImg, perhaps

matrix: get rid of the other ones (intro1/2/3) - the only ones in use are:

    "templateId": "home", "templateId": "quiz2x2", "templateId": "quiz3x3", "templateId": "getReady", "templateId": "thanks",

description of images - size of icons and spacings between them for the 2 layouts for the Hoops system
553:31  error  event is defined but never used  no-unused-vars # `/*eslint-disable no-unused-vars*/ `
hoops - implement form submit
hoops - take off "Next" on intro test, forcing user to make a guess
hoops: scaleImages() on show, not just resize
hoops: abandon didn't work - put abandon-modal in html
shrink containing div - too big-
with `.top, .bot { width: 100%; }`, image map doesn't work-x
log IP?-x
matrix incorrect gone off to side- .my_modal_content set width, not max width
send result automatically with submit
description of images - size of icons and spacings between them for the 2 layouts for the Matrix system
* Alter systems so that data is uploaded to server automatically when last screen in test is completed (Jonathan has working code for this which can provide template). - function finished()-/
* After test is completed user should be directed to a simple "Thank You" screen.
* names of any included libraries (e.g. node.js)
* representation of the `<div>`s in the page, description of the purpose of each.
* image sizes
hoops media query breakpoint - override
goes awry >window width >=992 - like a media query breakpoint
http://localhost:9001/styles/main.css
bower_components/bootstrap-sass/assets/stylesheets/bootstrap/_grid.scss:10
```css
@(min-width: 992px)
.container {
    width: 970px;
}
```

2nd to last image (coloured squares) bottom grid not aligned with image map
hoops: image stops stretching horizontally because .container has a set width - clear this and it will stretch the whole width

    @media (min-width: 768px)
    .container {
        width: 750px;
    }

Google docs - too few options, annoying "features" e.g. spellcheck can't turn off
doing this - in text, md - have to format it all differently so would have to spend ages making it into a Word doc...
though pandoc can do this
what about images?

    2016-07-29 01:32:24 kvogel@yoga3-vlubuntu ~/Projects/bb-quizzes/doc/matrix
    $ pandoc -o ~/Dropbox/matrix.docx -f markdown -t docx matrix-doc.md
    $ \ls ~/Dropbox

https://docs.google.com/document/d/12csdd4ncqbiC-Kw6C2bjopYhiiZJoaMxMkKj0DiDBYU/edit#heading=h.fsk7l5xa17k5

scaleImagesAY()

get the unscaled dimensions of the content:
  fullHeight
    get the various heights of fixed elements - hardcoded, or with jquery
    and the full-size heights of the images added together, including padding
  fullWidth
    get the various widths of fixed elements - hardcoded, or with jquery
    and the full-size widths of the wider image (bottom 3x2 or 4x2) added together, including padding
and then work out what ratio fullHeight to viewport height is
and then work out what ratio fullWidth to viewport width is
get the greater/lesser of these # resize using the smaller of these factors as a parameter

fullWidth = widthExtra + $('.bot').width()
fullHeight = heightExtra + $('.top').height() + $('bot').height()

central images are the only thing we can usefully scale
and the only way do that is to set the left and right margins to cause the width to alter - the height will follow to keep the aspect ratio.
so, we need to find out what height the central images would need to be in order for everything to fit height-wise.
i.e. get the height of the window, subtract the heights of everything we cannot change

ay calcs: innerWidth .gridcontainer 

---

hoops - use unmin imageMapResizer?-x doesn't use 
sticky footer?-x

git log a single file:

    $ gitk ~/Projects/bb-quizzes/hoops/yo/app/index.html
    $ git log -p ~/Projects/bb-quizzes/hoops/yo/app/index.html

fossil workflow too slow/labourious, use text-
unfuddle?-x
dev prev button doesn't work now unless navbar fits on one line-x

* Modify field types in hoops database table as discussed.
* Create matrices database table analagously to hoops but without the columns to identify the puzzle (these are redundant for matrices).

### Ingres COMMENT ON

The COMMENT ON statement has the following format:

```sql
    [EXEC SQL] COMMENT ON
    TABLE [schema.]table_name | COLUMN [schema.]table_name.column_name
    IS remark_text

    -- table_name      Specifies the table for which the constraint is defined
    -- remark_text     Defines the text of the comment

    -- Limits: The maximum length for a comment is 1600 characters

    -- e.g.

    COMMENT ON COLUMN matrix.tstarted IS 'time quiz started'
```

hoops intro pics are the wrong way round, i.e. puzzle solved backwards
there are 18 different puzzles in hoops...
what is the pseudo-random algorithm?

### page transition glitch

hoops, matrix look jumpy on page change because .fadeIn()/.slideDown() is happening at the same time as .fadeOut()
if it's the same page type/template, it looks OK, but otherwise you see the next page appearing underneath before the current disappears
that's why .slideDown() looks a bit better... content is mostly offscreen while fadeout still happening
.fadeOut() is not blocking... give it a callback to call on complete
I think you have to give .fadeOut() a duration as well to give it a callback: `.fadeOut([duration] [, complete])`

http://stackoverflow.com/questions/2989549/how-do-i-make-fadeout-blocking-in-jquery

```js
$('#blah').fadeOut(2000, function(){
    $("#blah2").fadeIn(2000);
});
```

though fadeout, fadein are wrapped in funcs: hideDiv(id), showDiv(id) hidePage(currentPage())

`xev` shows keypresses in X Windows
* Fix multiple-click bug in hoops which allows users to 'stack' mouse clicks and move through without properly answering.
hoops swallows (e.g.) ctrl-shift-i for dev tools (ff and chrome) - move e.preventDefault()
hoops - cap scaling-
hoops - centre welcome screen-
make sure correct complete.php is submitted to-
hoops: on mobile, buttons are ridiculously large and spaced apart, so that image is tiny and buttons scroll off the bottom
set media queries on these:

```css
  #answers button {
      padding: 20px;
      margin: 15px;
  }
  .btn-lg, .btn-group-lg > .btn {
      padding: 10px 16px;
      font-size: 18px;
      line-height: 1.3333333;
      border-radius: 6px;
  }
```

hoops next button scrolls off bottom on getReady-
hoops abandon is too near the edge #abandon-div.row {padding-left: 28%; }
hoops prev is too near the edge- remove btn-pull-left

in chrome devtools (but not ff), you can select and copy all the stackframe variables:
some of these will always be the same, for either 2x2 or 3x3

    # static
    botHeight = 365
    botWidth = 680
    topHeight = 340
    topWidth = 420
    widthExtra = 20
    heightExtra = 36
    middleHWRatio = 1.125
    naturalFullHeight = 741
    naturalFullWidth = 700

    # changing
    targetHeight = 636
    targetMiddleHeight = 600
    targetMiddleWidth = 675
    targetWidth = 600.8097165991903
    scaleH = 2.237142857142857
    scaleV = 0.8582995951417004
    scale = 0.8582995951417004
    setMargins = 435.5

Sun Aug  7 03:04:42 2016 aycalc lives! 
rather, scaleImagesAY(). I was doing `$(window).width`, not `$(window).width()` and getting `NaN`. Fixed that and it worked, straight off. Calculations must be sound.... 

cp_web_test

    sesh_id     incremental int8 session id, allocate from counter when test first cgi starts and passed to Javascript to be returned with results
    tinstruct   client time when instructions started
    tstart      client time when test started
    tfinish     client time when test completed
    tinsert
    ntests      number of puzzles completed
    durationN   duration of puzzle
    puzzleN     identifier for which puzzle is being shown
    elapsedN    time elapsed since tstart
    answerN     answer given
    correctN    whether answer is correct

(N=1,....)


* Finish re-implementing the re-sizing algorithm as specified.

We'll finalise the spec of the tables later, but for the minute the table should contain columns

  sesh_id - incremental int8 session id, allocate from counter when test first cgi starts and passed to Javascript to be returned with results
  tinstruct - client time when instructions started
  tstart - client time when test started
  tfinish - client time when test completed
  tinsert - server time (default 'now' field) when record inserted

for each individual hoops puzzle we need to save

  duration of puzzle
  identifier for which puzzle is being shown
  time elapsed since tstart
  answer given
  whether answer is correct

in fields durationN, puzzleN, elapsedN, answerN, correctN (N=1,....)

We also need a field ntests which records the number of puzzles completed - i.e. the maximum value of N for which there is valid data (default any non-done puzzle columns to values like -1)

It would be nice if you can get the program inserting into this structure by Tuesday, but I'll settle for seeing the table created in the database register if that's not possible due to the bug fixes.

* Start saving data to ingres. Create a database cp_web_test with table "hoops" and insert a single record into each when the corresponding test is completed.  


media query breakpoint on min-height, shrink text? inc A and B on hoops
missed #answer in calcs-

hoops
abandon touches left side
.row bootstrap gives -15px margins! remove .row

no margin at top of hoops?-
matrix .container has 15 10 20 10 set in main.scss
hoops is 0 15 0 15

quick fix for scaleImagesCBsimple|new() - add more heights
abandon still scrolls!!!
debounce double-click

media query text size breakpoint v, h-
backend - no rosetta, ideas for fields to come-
total number of hoops puzzles? 18-


hide nav #buttons with 'd' key
explanatory text
cut up matrix tiles, put in table layout?-/
use media queries to flow layout for smaller widths

Thu Jun  2 09:31:05 2016
schoolboy error: was trying to add keyboard handler, but it was executing once at the start despite no keypress, then not responding to keypresses. Had done:

```js
// do
$("body").on('keydown', mykeydown);     // no brackets - reference to function object

// not
$("body").on('keydown', mykeydown());   // note brackets, calls function
```

---


sql add comment- -> db comments-
fadeFinished()? no
table and skeleton of backend for **both** quizzes

get rid of wrappers and chain show/hide/fade

```js
    $('#' + id).fadeOut(FADEOUT);
    
    function hideDiv(id) {
        //document.getElementById(id).style.display = 'none'; //console.log('hideDiv(): id: ' + id);
        $('#' + id).fadeOut(FADEOUT); // 'fast'
        //$('#' + id).slideUp();
    }
    function showDiv(id) {
        //document.getElementById(id).style.display = 'inline'; //console.log('showDiv(): id: ' + id);
        $('#' + id).fadeIn(FADEIN); // 'fast'
        //$('#' + id).slideDown();
    }
    function hidePage(page) {
        hideDiv(page.templateId); //console.log('hidePage(): templateId: ' + page.templateId); //+ obj(page) + '\'');
    }
        if (page.hasOwnProperty('suppressAbandon')) {//console.log('page.hasOwnProperty(\'suppressAbandon\')');
            hideDiv('abandon-div');
        } else {
            showDiv('abandon-div');
        }

        showDiv((page.templateId));

    function showModal(modal) {
        showDiv('modals');
        showDiv(modal); //console.log('showModal(\'' + modal + '\')');
    }
    function hideModal(modal) {
        hideDiv('modals');
        hideDiv(modal); //console.log('hideModal(\'' + modal + '\')');
    }
            if ($('#devBar').css('display') === 'none') {
                showDiv('devBar');
            } else {
                hideDiv('devBar');
            }

            hideDiv('devBar');
```

.fade() make blocking
    http://red.ctsu.ox.ac.uk/~cp/cjb/slowfade/
    you shouldn't and don't pause in js - split function and setTimeout, use callbacks
    http://stackoverflow.com/questions/2989549/how-do-i-make-fadeout-blocking-in-jquery
    http://javascriptissexy.com/understand-javascript-callback-functions-and-use-them/
double click allowed in real game but not on demo puzzle- cause .fade() non-blocking and in real game next div is same page

no comment on tables themselves, but on columns - how to put this in doc? copy from create-create.py
DAR collects these! http://inweb.ctsu.ox.ac.uk/~ingres/dar/red/assets_red_cp_web_test.htm (see below)

    [cp@red ~]$ sql cp_web_test
    $ HELP COMMENT TABLE matrix;\g
    Table matrix has no comments.
    $ HELP COMMENT COLUMN matrix sesh_id;\g
    Table:  matrix Owner:  cp Column: sesh_id Long Remark: Session ID


Fix data bug in hoops which appears to be resulting in incorrect data being output. [This is #1 priority]
    hoops logic bb-quizzes/notes/2016-08-16 hoops order.md


* Implement the re-sizing algorithm for Matrix as specified previously (cap to stop shrinking at 320px)
* description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.
  scaling of what?   height and width of whole thing without scaling? which is what? the natural size? depends on how big the viewport is...
then resize using the smaller of these factors as a parameter

not sure about startTimer
leave comments shows previous puzzle on resize
tidy up matrix, hoops
standardise text sizes-?
hourglass if wait on submit? If possible a busy/hourglass cursor could be displayed while data is uploading


### practice puzzle is different each time and should be fixed:

Jon-touchscreens.exe hoops fixed answer 
A t3yw2b1       t3yw2b1.png exists
B t3bw21y       t3bw21y.png exists

hoops
A t3bw2y1        aka top-constant.png
B (changes)

should be
A t3bw21y (same as exe B)   or 0, 1, 2, 0, 0, 3
B t3yw2b1                   or ...

top-constant is t3bw2y1

---

Collected db comments from DAR http://inweb.ctsu.ox.ac.uk/~ingres/dar/red/assets_red_cp_web_test.htm
-> hoops-doc.md, matrix-doc.md

invert hoops logic - A-B <-> B-A
make picture B look like picture A
intro2 - swap images

now lower game image changes on resize....as each resize triggers showPage().... just rescale
follow levels[] data

good news: answers are correctly matched to images
but, the order doesn't seem right - got a lot of 5s right from the start
levels: 1,8,5,2,13,6,16,7,4,9,3,15,10,12,17,11,0,14
order of correct answers: 5 1 4 5 4 4 5 1 3 2 2 5 2 4 1 2 3 1
reversed: 1 3 2 1 4 2 5 2 2 3 1 5 4 4 5 4 1 5 (same as pseudoRandLevelList)
because wanted levels being popped off in reverse order
got a really difficult one first up: t3wyb21.png ans 5, correct
levels: 2,8,5,1,11,4,16,6,7,9,0,15,13,12,14,10,3,17
answered: 5, correct: 5, isCorrect: true main.js:516:9
Correct! main.js:536:13
puzzle.b: t3w2y1b.png, correct: t3w2y1b.png

clicks ignored after resize! unbound but not rebound?
timer didn't seem to time out, answered all 18 though going slow. total time == 409996 = 6.8 minutes? startTimer when on first puzzle
don't advance beyond game div until finished-
thanks page doesn't pause-

description of images - size of icons and spacings between them for the 2 layouts
Produce a similar document for the Hoops system

Thu Jul 28 16:09:04 2016
please check yes/no too wide
because box `.my-modal-content` is fixed width:

```css
.my-modal-content {
    position: fixed;
    background-color: #FFF;
    border-radius: 5px;
    text-align: center;
    line-height: 20px;
    top: 50%;            // centre in viewport
    left: 50%;           // but need to need to offset topleft corner with margns
    margin-left: -200px; // half of _width
    margin-top: -100px;  // half of _height
    z-index: 11;
    padding: 10px;
    height: 200px;
    width: 400px;
}
```

made <300px so should fit on any screen >300.
d for developer
end of quiz:
    should send results immediately rather than relying on user to submit for
    rather than send AJAX on completion, Jon has a method of submitting a form automatically with JavaScript
    easier to do on back end with xcgi.c instead of writing AJAX endpoint
    C:\code\jonathanpr\webserver\htdocs\HMDB3\Snap\snap.php|.html|.js

biobank web bug in middle of night caused wait condition while database was locked
abandon still scrolls off bottom, particularly on 3x3 puzzles (scaling algorithm)
Implement AY re-sizing algorithm

* Implement the re-sizing algorithm for Matrix as specified previously.
* It is not necessary to support resolutions of less than 320 pixels horizontally. Algorithm can be capped to stop shrinking at this point.
* Implement re-sizing in Hoops and finish the interface for that program.
* Alter systems so that data is uploaded to server automatically when last screen in test is completed (Jonathan has working code for this which can provide template).  If possible a busy/hourglass cursor could be displayed while data is uploading [don't spend more than an hour on this - if it's not easy to do, then forget it].  After test is completed user should be directed to a simple "Thank You" screen.


### sftp to red

    red         ssh
    redftp      put bbquiz.cgi in red:~cb/cjb/bbquiz/
    redftpi     ssh to red interactively

    2016-08-15 14:44:24 cp@xrat ~/Projects/bb-quizzes/backend
    $ ./red
    Warning: the RSA host key for 'red.ctsu.ox.ac.uk' differs from the key for the IP address '163.1.206.2'
    Offending key for IP in /user/cp/.ssh/known_hosts:4
    Matching host key in /user/cp/.ssh/known_hosts:29
    Are you sure you want to continue connecting (yes/no)? yes
    [cp@red ~]$ less /etc/ssh/ssh_host_rsa_key.pub
    # added to xrat:~/.ssh/known_hosts
    # could have just deleted and logged in again, would have recreated it

http://red.ctsu.ox.ac.uk/~cp/cjb/bbquiz/?a=1&b=2&c=3 got params

/home/cbird/.config/sublime-text-2/Packages/SideBarEnhancements -> q108-vlubuntu