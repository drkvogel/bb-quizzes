# Hoops Quiz : structure, technology and algorithms

## Contents

* Representation of the elements in the page, description of the purpose of each.
* Image dimensions
* Description of scaling algorithm
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208
* Names of any included libraries

\newpage

## Description of page elements

![hoops layout](hoops-layout.png "hoops layout")

>representation of the HTML elements in the hoops puzzle, with a description of the purpose of each.

    body                    HTML <body> tag
    #devBar                 hidden    
    div.container           Used to add page margins
    div#pages               Container to switch the pages
	div.page#game           Container for the main puzzle
    div.middleImg           Contains for images, e.g. intro or game
	div.toptable-container  A container for the game images
	table.toptable          Table containing the two images for each puzzle
	td#imgdiv-a             Containing cell for the upper image
    img#img-a               The upper image, which is the same on each page
	td#imgdiv-b             Containing cell for the lower image
    img#img-b               The lower image, which is different on each page
	div.botTxt              Holds the explanatory text when required
	div.answers             Holds the buttons 1-6, as required
	div.navCtl              Holds the "Prev/Next" buttons, as needed

### Element heights (top to bottom)

    html                -
    body                -
    #devBar             hidden
    div.container       padding-top: 15px
    div#pages           -
    div#game            -
    div.middleImg       -
    table.toptable      
    td#imgdiv-a         
    img#img-a           
    td#imgdiv-b         
    img#img-b           
    div.middleImg       -
    div.botText         72px minimum (if not wrapped) (if visible)
    div#answers         -
    div.navCtl          
    div#pages           -
    div#abandon-div     34px (if visible)
    div.container       padding-bottom: 20px
    body                -
    html                -

\newpage

## Image Dimensions

The images are all PNG format, 8-bit/color RGBA, non-interlaced.
There are five images, one for each page, in the introduction: `intro1.png` to `intro5.png`. They have the dimensions 748px x 470px.
Apart from the intro screens, the other images are 748px x 291px, two on each screen, one at the top, one at the bottom.

The image at the top remains constant (this is different from the original test, where the bottom image remains constant). Its name is `top-constant.png`

The other images change on each page in a psuedo-random fashion. I have name them in the format:

    t3<x>2<y>1<z>.png

where:

* `t` stands for tile
* 3 is the leftmost peg, which can hold 3 hoops
* `<x>` is a sequence of letters describing which hoops are on the peg denoted by the preceding number, from top to bottom, using the letters `y`, `b` and `w` for Yellow, Black and White, respectively.
* 2 is the middle peg, which can hold 2 hoops
* `<y>` is the sequence of hoops from top to bottom on the middle peg
* 1 is the rightmost peg, which can hold 1 hoop
* `<z>` is the sequence of hoops from top to bottom on the rightmost peg

Thus, we have the images:

    t32by1w.png, t32wy1b.png, t3bw21y.png, t3w2b1y.png, t3w2yb1.png, t3wb2y1.png, t3wy2b1.png, t3y2b1w.png, t3yb21w.png, t3ybw21.png, t3yw21b.png, t3yw2b1.png, t3ywb21.png

\newpage

## Description of Scaling Algorithm

#### Pseudo-code for scaling algorithm

```
get natural width/height (naturalFullWidth/Height)
get window width/height ($(window).width()/height)

vertical shrink = window height / naturalFullHeight
horizontal shrink = window width / naturalFullWidth

scale = vShrink < hShrink ? vShrink : hShrink

targetHeight = naturalFullHeight * scale
targetWidth = naturalFullWidth * scale

targetMiddleHeight = targetHeight - heightExtras

# height/width ratio of .middleImg
middleHWRatio = 1.15

# what innerWidth of .gridContainer would create targetMiddleHeight?
targetMiddleWidth = targetMiddleHeight * middleHWRatio

# set margins on .gridContainer to achieve targetWidth and targetHeight
margins = (window.width - widthExtra) / 2
```

#### JavaScript code for scaling algorithm

```js
var topWidth = 748, topHeight = 291, botWidth = 748, botHeight = 291;

var widthExtra =
    ($('.container').outerWidth(true) - $('.container').width()) +
    ($('#pages').outerWidth(true) - $('#pages').width());

var heightExtra =
    ($('.container').outerHeight(true) - $('.container').height()) +
    ($('.topTxt').is(':visible') ? $('.topTxt').height() : 0) +
    ($('#imgdiv-a').is(':visible') ? $('#imgdiv-a').outerHeight(true) - $('#imgdiv-a').height() : 0) +
    ($('#imgdiv-b').is(':visible') ? $('#imgdiv-b').outerHeight(true) - $('#imgdiv-b').height() : 0) +
    ($('.botTxt').is(':visible') ? $('.botTxt').height() : 0) +
    ($('#answers').is(':visible') ? $('#answers').height() : 0) +
    ($('.navTxt').is(':visible') ? $('.navTxt').height() : 0) +
    ($('.navCtl').is(':visible') ? $('.navCtl').height() : 0);

var naturalFullWidth = widthExtra + topWidth;
var naturalFullHeight = heightExtra + topHeight + botHeight;

var scaleV = ($(window).height()) / naturalFullHeight;
var scaleH = $(window).width() / naturalFullWidth;
var scale = scaleV <= scaleH ? scaleV : scaleH;

var targetWidth = naturalFullWidth * scale;
var targetHeight = naturalFullHeight * scale;
var targetMiddleHeight = targetHeight - heightExtra;
var middleHWRatio = 1.15;
var targetMiddleWidth = targetMiddleHeight * middleHWRatio;

var setMargins = ($(window).width() - widthExtra - targetMiddleWidth) / 2;
if (setMargins > 0) {
    $('.middleImg').css('margin-left', setMargins);
    $('.middleImg').css('margin-right', setMargins);
} else {
    $('.middleImg').css('margin-left', 0);
    $('.middleImg').css('margin-right', 0);
}
```

\newpage

## Worked Examples

>Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208

### 1280x1024

    topWidth: 748, topHeight: 291, botWidth: 748, botHeight: 291
    widthExtra = 
        (container.outerWidth [1280] - container.width [1260]) [20] + 
        pages.outerWidth [1260] - pages.width [1260]) [0] + 
        == 20
    heightExtra =
        (container.outerHeight [839] -  container.height [804]) [35] + 
        topTxt.height [0] + 
        (#imgdiv-a.outerHeight [294] - #imgdiv-a.height [274]) [20] + 
         (#imgdiv-b.outerHeight [294] - #imgdiv-b.height [274]) [20] + 
        botTxt.height [-36]  + 
        #answers.height [96] +
        navTxt.height [0] +
        navCtl.height [-15] +
        == 120
    naturalFullWidth =
        widthExtra [20] + topWidth [748] == 768
    naturalFullHeight =
        heightExtra [120] + topHeight [291] + botHeight [291]
        == 702
    scaleV = window.height [1024] / naturalFullHeight [702] == 1.46
    scaleH = window.width [1280] / naturalFullWidth [768] == 1.67
    scale = scaleV [1.46] <= scaleH  [1.67] ? 1.46
    targetWidth = naturalFullWidth [768] * scale [1.46] == 1120.27
    targetHeight = naturalFullHeight [702] * scale [1.46] == 1024.00
    targetMiddleHeight = targetHeight [1024] - heightExtra [120] == 904
    targetMiddleWidth = targetMiddleHeight [904] * middleHWRatio [1.15] == 1039
    setMargins = window.width [1280] - widthExtra [20] - targetMiddleWidth [1039]) / 2 == 110
    setMargins > 0: true
        middleImg.margin-left = 110
        middleImg.margin-right = 110

### 640x480

    topWidth: 748, topHeight: 291, botWidth: 748, botHeight: 291
    widthExtra = 
        (container.outerWidth [640] - container.width [620]) [20] + 
        pages.outerWidth [620] - pages.width [620]) [0] + 
        == 20
    heightExtra =
        (container.outerHeight [454] -  container.height [419]) [35] + 
        topTxt.height [0] + 
        (#imgdiv-a.outerHeight [132] - #imgdiv-a.height [112]) [20] + 
         (#imgdiv-b.outerHeight [132] - #imgdiv-b.height [112]) [20] + 
        botTxt.height [-28]  + 
        #answers.height [60] +
        navTxt.height [0] +
        navCtl.height [-15] +
        == 92
    naturalFullWidth =
        widthExtra [20] + topWidth [748] == 768
    naturalFullHeight =
        heightExtra [92] + topHeight [291] + botHeight [291]
        == 674
    scaleV = window.height [480] / naturalFullHeight [674] == 0.71
    scaleH = window.width [640] / naturalFullWidth [768] == 0.83
    scale = scaleV [0.71] <= scaleH  [0.83] ? 0.71
    targetWidth = naturalFullWidth [768] * scale [0.71] == 546
    targetHeight = naturalFullHeight [674] * scale [0.71] == 480
    targetMiddleHeight = targetHeight [480] - heightExtra [92] == 388
    targetMiddleWidth = targetMiddleHeight [388] * middleHWRatio [1.15] == 446
    setMargins = window.width [640] - widthExtra [20] - targetMiddleWidth [446]) / 2 == 86
    setMargins > 0: true
        middleImg.margin-left = 86
        middleImg.margin-right = 86

### 320x480

    topWidth: 748, topHeight: 291, botWidth: 748, botHeight: 291
    widthExtra = 
        (container.outerWidth [320] - container.width [300]) [20] + 
        pages.outerWidth [300] - pages.width [300]) [0] + 
        == 20
    heightExtra =
        (container.outerHeight [339] -  container.height [304]) [35] + 
        topTxt.height [0] + 
        (#imgdiv-a.outerHeight [76] - #imgdiv-a.height [56]) [20] + 
        (#imgdiv-b.outerHeight [76] - #imgdiv-b.height [56]) [20] + 
        botTxt.height [-28]  + 
        #answers.height [38] +
        navTxt.height [0] +
        navCtl.height [-15] +
        == 70
    naturalFullWidth =
        widthExtra [20] + topWidth [748] 
        == 768
    naturalFullHeight =
        heightExtra [70] + topHeight [291] + botHeight [291]
        == 652
    scaleV = window.height [480] / naturalFullHeight [652] == 0.74
    scaleH = window.width [320] / naturalFullWidth [768] == 0.42
    scale = scaleV [0.74] <= scaleH  [0.42] ? 0.42
    targetWidth = naturalFullWidth [768] * scale [0.42] == 320
    targetHeight = naturalFullHeight [652] * scale [0.42] == 271
    targetMiddleHeight = targetHeight [271] - heightExtra [70] == 201
    targetMiddleWidth = targetMiddleHeight [201] * middleHWRatio [1.15] == 231
    setMargins = window.width [320] - widthExtra [20] - targetMiddleWidth [231]) / 2 == 34
    setMargins > 0: true
        middleImg.margin-left = 34
        middleImg.margin-right = 34

### 750x1334

    topWidth: 748, topHeight: 291, botWidth: 748, botHeight: 291
    widthExtra = 
        (container.outerWidth [750] - container.width [730]) [20] + 
        pages.outerWidth [730] - pages.width [730]) [0] + 
        == 20
    heightExtra =
        (container.outerHeight [601] -  container.height [566]) [35] + 
        topTxt.height [0] + 
        (#imgdiv-a.outerHeight [187] - #imgdiv-a.height [167]) [20] + 
        (#imgdiv-b.outerHeight [187] - #imgdiv-b.height [167]) [20] + 
        botTxt.height [-28]  + 
        #answers.height [96] +
        navTxt.height [0] +
        navCtl.height [-15] +
        == 128
    naturalFullWidth =
        widthExtra [20] + topWidth [748] == 768
    naturalFullHeight =
        heightExtra [128] + topHeight [291] + botHeight [291]
        == 710
    scaleV = window.height [1334] / naturalFullHeight [710] == 1.88
    scaleH = window.width [750] / naturalFullWidth [768] == 0.98
    scale = scaleV [1.88] <= scaleH  [0.98] ? 0.98
    targetWidth = naturalFullWidth [768] * scale [0.98] == 750
    targetHeight = naturalFullHeight [710] * scale [0.98] == 693
    targetMiddleHeight = targetHeight [693] - heightExtra [128] == 565
    targetMiddleWidth = targetMiddleHeight [565] * middleHWRatio [1.15] == 650
    setMargins = window.width [750] - widthExtra [20] - targetMiddleWidth [650]) / 2 == 39
    setMargins > 0: true
        middleImg.margin-left = 39
        middleImg.margin-right = 39

### 1242x2208

    topWidth: 748, topHeight: 291, botWidth: 748, botHeight: 291
    widthExtra = 
        (container.outerWidth [1242] - container.width [1222]) [20] + 
        pages.outerWidth [1222] - pages.width [1222]) [0] + 
        == 20
    heightExtra =
        (container.outerHeight [909] -  container.height [874]) [35] + 
        topTxt.height [0] + 
        (#imgdiv-a.outerHeight [328] - #imgdiv-a.height [308]) [20] + 
        (#imgdiv-b.outerHeight [328] - #imgdiv-b.height [308]) [20] + 
        botTxt.height [-36]  + 
        #answers.height [96] +
        navTxt.height [0] +
        navCtl.height [-15] +
        == 120
    naturalFullWidth =
        widthExtra [20] + topWidth [748] == 768
    naturalFullHeight =
        heightExtra [120] + topHeight [291] + botHeight [291]
        == 702
    scaleV = window.height [2208] / naturalFullHeight [702] == 3.15
    scaleH = window.width [1242] / naturalFullWidth [768] == 1.62
    scale = scaleV [3.15] <= scaleH  [1.62] ? 1.62
    targetWidth = naturalFullWidth [768] * scale [1.62] == 1242
    targetHeight = naturalFullHeight [702] * scale [1.62] == 1135
    targetMiddleHeight = targetHeight [1135] - heightExtra [120] == 1015
    targetMiddleWidth = targetMiddleHeight [1015] * middleHWRatio [1.15] == 1167
    setMargins = window.width [1242] - widthExtra [20] - targetMiddleWidth [1167]) / 2 == 27
    setMargins > 0: true
        middleImg.margin-left = 27
        middleImg.margin-right = 27

\newpage

## List of Libraries

>names of any included libraries (e.g. node.js)

    jquery.js
    jquery-ui.css
    modernizr.js
    browser-sync.js
    bootstrap.css
    bootstrap-sass

The build system was created by yeoman running on node.js via npm. It uses the gulp task runner to perform SASS compilation, testing, linting, synchronised browsing, minification, and front-end package management via bower. The CSS framework is Bootstrap, though I have overridden a lot of it to make things simpler. The code in main.js uses jQuery.

    http://yeoman.io/
    https://nodejs.org/
    https://www.npmjs.com
    http://gulpjs.com
    http://sass-lang.com/
    https://bower.io/
    http://getbootstrap.com/
    https://jquery.com/

\newpage

## Database table for Hoops Quiz

    (Table) cp.hoops
    Comment:None
    Journaled:No
    Page Size:8K Pages:3 Overflow Pages:None
    Structure:HEAP
    Compression:None

    Key Field   Type        Null    Default Comment
    sesh_id     INTEGER4    No      None    Session ID
    ntests      INTEGER4    No      None    Number of puzzles completed
    tinstruct   INGRESDATE  No      None    Time the instructions were shown to the user
    tstart      INGRESDATE  No      None    Time the quiz was started
    tfinish     INGRESDATE  No      None    Time the quiz was finished
    tinsert     INGRESDATE  No      'now'   Time the row was inserted into the database (default 'now')
    responses   LONG VARCHAR No     None    JSON returned at end of quiz, to be parsed by backend
    duration1   INTEGER2    Yes     None    Time taken to answer puzzle
    puzzle1     INTEGER1    Yes     None    Puzzle chosen by algorithm
    elapsed1    INTEGER2    Yes     None    Cumulative time elapsed
    answer1     INTEGER1    Yes     None    Answer given by user
    correct1    INTEGER1    Yes     None    Correct answer
    ...
    duration18  INTEGER2    Yes     None    Time taken to answer puzzle
    puzzle18    INTEGER1    Yes     None    Puzzle chosen by algorithm
    elapsed18   INTEGER2    Yes     None    Cumulative time elapsed
    answer18    INTEGER1    Yes     None    Answer given by user
    correct18   INTEGER1    Yes     None    Correct answer
    
    Secondary Indices:None
    Constraints:None
    Rules:None
    Grants:None

\newpage

## Appendix

### Image details

    intro1.png:       PNG image data, 748 x 470
    intro2.png:       PNG image data, 748 x 470
    intro3.png:       PNG image data, 748 x 470
    intro4.png:       PNG image data, 748 x 644
    intro5-orig.png:  PNG image data, 748 x 723
    intro5.png:       PNG image data, 748 x 487
    t32by1w.png:      PNG image data, 748 x 291
    t32wy1b.png:      PNG image data, 748 x 291
    t3bw21y.png:      PNG image data, 748 x 291
    t3w2b1y.png:      PNG image data, 748 x 291
    t3w2yb1.png:      PNG image data, 748 x 291
    t3wb2y1.png:      PNG image data, 748 x 291
    t3wy2b1.png:      PNG image data, 748 x 291
    t3y2b1w.png:      PNG image data, 748 x 291
    t3yb21w.png:      PNG image data, 748 x 291
    t3ybw21.png:      PNG image data, 748 x 291
    t3yw21b.png:      PNG image data, 748 x 291
    t3yw2b1.png:      PNG image data, 748 x 291
    t3ywb21.png:      PNG image data, 748 x 291
    top-constant.png: PNG image data, 748 x 291


