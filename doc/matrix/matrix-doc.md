# Matrix Quiz : structure, technology and algorithms

A document describing the structure, technology and sizing algorithms in the main web-page of the Matrices questionnaire.

## Contents

* A pictorial representation of the `<div>`s in the page, accompanied by a brief description of the purpose of each.
* Image dimensions
* A description of the algorithm used to determine the scaling of the image elements
* Worked numeric examples for various screen resolutions
* Included libraries

\newpage
\pagebreak

## Layout

![matrix 2x2 layout](matrix-layout.png "matrix 2x2 layout")
  
    body                HTML <body> tag
    div.container       Used to add margins around the content
    div#pages           A container for the pages, one of which is shown at a time
    div#quiz2x2.quiz    A page div, the 2x2 quiz is shown in this example
    div.gridContainer   Used to keep grids together and scaled relative to each other, and to centre using left and right margins
    .grid2x2            Contains the top grid image
    .grid3x2            Contains the bottom grid image, and padding to distance it from the top grid
    img.top             The top grid image, which is changed by main.js
    img.bot             The bottom grid image, which is changed by main.js
    div.botText         Holds the explanatory text when required

\newpage

### Natural image sizes

    2x2, 3x2
    img.top natural: 420 x 340
    img.bot natural: 680 x 365

    3x3, 4x2
    img.top natural: 510 x 405
    img.bot natural: 755 x 295

### Width (symmetrical about y axis)

    html                -
    body                -
    div.container       10px
    div#pages           -
    div#quiz2x2.quiz    -
    div.gridContainer   margins set by calc
    div.grid3x2         margin: auto, width: 81% e.g. 65.1px
    img.bot (natural)   680px (quiz2x2) | 755px (quiz3x3)
    div.grid3x2         margin: auto, width: 81% e.g. 65.1px
    div.gridContainer   margins set by calc
    div#quiz2x2.quiz    -
    div#pages           -  
    div.container       10px
    body                -
    html                -


notes:

* div.container padding: 15px 10px 20px 10px; (N, E, S, W)
* div#pages has margin: auto but always fills div.container
* hard-code natural image sizes - see "Can we get the native/natural height of images?"

### Height

    html                -
    body                -
    #devBar             hidden
    div.container       padding-top: 15px
    div#pages           -
    div#quiz2x2.quiz    -
    div.gridContainer   -
    img.top (natural)   340px (quiz2x2) | 405px (quiz3x3)
    div.grid3x2         padding-top: 5% e.g. 34px
    img.bot (natural)   365px (quiz2x2) | 295px (quiz3x3)
    div.gridContainer   -
    div.botText         72px minimum (if not wrapped) (if visible)
    div#quiz2x2.quiz    -
    div#pages           -
    div#abandon-div     34px (if visible)
    div.container       padding-bottom: 20px
    body                -
    html                -

\newpage

## Details of image sizes

### 2x2 Puzzle

![2x2 top image](2x2-top.png "2x2 top image")

* The top image is 420px x 340px, 2 tiles wide by 2 tiles high
* Each tile is 210px x 170px, with no space between them

![2x2 bottom image](2x2-bottom.png "2x2 bottom image")

* The bottom image is 680px x 365px, 3 tiles wide x 2 tiles high
* Each tile is 210px x 170px and there is a gap of 25px between each tile, horizontally and vertically.

# 3x3 Puzzle

![3x3 top image](3x3-top.png "3x3 top image")

* The top image is 510px x 405px, 3 tiles wide by 3 tiles high
* Each tile is 170px x 135px, with no space between them

* The bottom image is 755px x 295px, 4 tiles wide x 2 tiles high
* Each tile is 170px x 135px and there is a gap of 25px between each tile, horizontally and vertically.

![3x3 bottom image](3x3-bottom.png "3x3 bottom image")

\newpage

## Description Of Scaling Algorithms

### scaleImagesCBsimple()

#### Pseudo-code

    setMargins = (window.width - (window.height() - heightExtra) - widthExtra) / 2;

* Tries to keep the `div.gridContainer` element square by setting the margins of `.gridContainer`
* The abandon button scrolls off the bottom at extreme width and short height.

#### JavaScript code

```js
var widthExtra =
    ($('.container').outerWidth(true) - $('.container').width()) +
    ($('#pages').outerWidth(true) - $('#pages').width());

var heightExtra = // required height of .gridContainer
    ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
    ($('.botText').is(':visible') ? $('.botText').height() : 0);

var setMargins = ($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;

if (setMargins > 0) {
    $('.gridContainer').css('margin-left', setMargins);
    $('.gridContainer').css('margin-right', setMargins);
} else { // content should shrink width-wise if needed
    $('.gridContainer').css('margin-left', 0);
    $('.gridContainer').css('margin-right', 0);
}
```

### New Scaling Algorithm

#### Pseudo-code

```
    get natural width/height (naturalFullWidth/Height)
    get window width/height ($(window).width()/height)

    # allow 200px for text at bottom
    # window - 200px height needs to fit natural width/height

    vertical shrink = (window height - 200px) / naturalFullHeight
    horizontal shrink = window width / naturalFullWidth

    scale = vShrink < hShrink ? vShrink : hShrink

    targetHeight = naturalFullHeight * scale
    targetWidth = naturalFullWidth * scale

    targetMiddleHeight = targetHeight - heightExtras

    # need h/w ratio of .gridContainer
    # Typical dimensions: 162 x 144
    # 162 / 144 == 1.125
    middleHWRatio = 1.125

    # what innerWidth of .gridContainer would create targetMiddleHeight?
    targetMiddleWidth = targetMiddleHeight * middleHWRatio

    # set margins on .gridContainer to achieve targetWidth and targetHeight
    margins = (window.width - widthExtra) / 2
```

#### JavaScript code

```js
        var topWidth, topHeight, botWidth, botHeight;
        if (currentPage().templateId == 'quiz2x2') {
            topWidth = 420;
            topHeight = 340;
            botWidth = 680;
            botHeight = 365;
        } else if (page.templateId == 'quiz3x3') {
            topWidth = 510;
            topHeight = 405;
            botWidth = 755;
            botHeight = 295;
        }

        var widthExtra =
            ($('.container').outerWidth(true) - $('.container').width()) +
            ($('#pages').outerWidth(true) - $('#pages').width());

        var heightExtra =
            ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
            ($('.botText').is(':visible') ? $('.botText').height() : 0);

        var naturalFullWidth = widthExtra + botWidth; // bottom image widest
        var naturalFullHeight = heightExtra + topHeight + botHeight;

        var scaleV = ($(window).height() - 200) / naturalFullHeight;
        var scaleH = $(window).width() / naturalFullWidth;
        var scale = scaleV <= scaleH ? scaleV : scaleH;

        var targetWidth = naturalFullWidth * scale;
        var targetHeight = naturalFullHeight * scale;
        var targetMiddleHeight = targetHeight - heightExtras;

        var middleHWRatio = 1.125
        var targetMiddleWidth = targetMiddleHeight * middleHWRatio;

        setMargin = ($(window).width - widthExtra) / 2
        $('.gridContainer').css('margin-left', setMargin);
        $('.gridContainer').css('margin-right', setMargin);
```

### Can we get the native/natural height of images in JavaScript?

In order to work out the natural, unscaled dimensions of the content, in order to scale them to fit the viewport, we need to know the original dimensions of the images. Could we do this programmatically? 

This is slighty tricky: there are native javascript attributes: `.naturalWidth` / `.naturalHeight` but for IE, in **IE9+**

    var width = $(this).get(0).naturalWidth; var height = $(this).get(0).naturalHeight; // current element
    var width = $("selector").get(0).naturalWidth; var height = $("selector").get(0).naturalHeight; // selected element

There is a plugin that adds `.naturalHeight()` and `.naturalWidth()` to jQuery.
Workaround for IE6-IE8: create a `new Image()` element, and get the width and height of that.
As we know the image dimensions and they are not going to change, we might as well hard-code them.

\newpage

## Worked examples

Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208.

1308 x 598

botHeight = 365
botWidth = 680
topHeight = 340
topWidth = 420
widthExtra = 20
heightExtra = 72
middleHWRatio = 1.125
naturalFullHeight = 777
naturalFullWidth = 700

scaleH = 1.8685714285714285
scaleV = 0.5122265122265123
scale = 0.5122265122265123
targetWidth = 358.56
targetHeight = 398
targetMiddleWidth = 366.75
targetMiddleHeight = 326
setMargins = 460.63

1280x1024

botHeight = 365
botWidth = 680
heightExtra = 72
topHeight = 340
topWidth = 420
widthExtra = 20
middleHWRatio = 1.125
naturalFullHeight = 777
naturalFullWidth = 700

scaleH = 1.8285714285714285
scaleV = 1.0604890604890604
scale = 1.0604890604890604
targetWidth = 742.34
targetHeight = 824
targetMiddleHeight = 752
targetMiddleWidth = 846
setMargins = 207

640x480

botWidth = 680
botHeight = 365
topWidth = 420
topHeight = 340
widthExtra = 20
heightExtra = 60
middleHWRatio = 1.125
naturalFullWidth = 700
naturalFullHeight = 765

scaleH = 0.9142857142857143
scaleV = 0.3660130718954248
scale = 0.3660130718954248
targetWidth = 256.21
targetHeight = 280
targetMiddleWidth = 247.5
targetMiddleHeight = 220
setMargins = 186.25


320x480

botWidth = 680
botHeight = 365
topWidth = 420
topHeight = 340
widthExtra = 20
heightExtra = 120
middleHWRatio = 1.125
naturalFullWidth = 700
naturalFullHeight = 825

scaleH = 0.45714285714285713
scaleV = 0.3393939393939394
scale = 0.3393939393939394
targetWidth = 237.58
targetHeight = 280
targetMiddleWidth = 180
targetMiddleHeight = 160
setMargins = 60

750x1334

botWidth = 680
botHeight = 365
topWidth = 420
topHeight = 340
widthExtra = 20
heightExtra = 60
middleHWRatio = 1.125
naturalFullWidth = 700
naturalFullHeight = 765

scaleH = 1.072857142857143
scaleV = 1.4823529411764707
scale = 1.072857142857143
targetWidth = 751
targetHeight = 820.73
targetMiddleWidth = 855.83
targetMiddleHeight = 760.74
setMargins = -62.41


1242x2208

botWidth = 680
botHeight = 365
topWidth = 420
topHeight = 340
widthExtra = 20
heightExtra = 72
middleHWRatio = 1.125
naturalFullWidth = 700
naturalFullHeight = 777

scaleH = 1.7757142857142858
scaleV = 2.584298584298584
scale = 1.7757142857142858
targetWidth = 1243
targetHeight = 1379.73
targetMiddleWidth = 1471.19625
targetMiddleHeight = 1307.73
setMargins = -124.09812499999998



\newpage

## List of included libraries

    jquery.js
    jquery-ui.css
    modernizr.js
    browser-sync.js
    bootstrap.css
    bootstrap-sass
    imageMapResizer.js

The build system was created by yeoman running on node.js via npm. It uses the gulp task runner to perform SASS compilation, testing, linting, synchronised browsing, minification, and front-end package management via bower.

The CSS framework is Bootstrap, though I have overridden a lot of it to make things simpler.
The code in main.js uses jQuery.

    http://yeoman.io/
    https://nodejs.org/
    https://www.npmjs.com
    http://gulpjs.com
    http://sass-lang.com/
    https://bower.io/
    http://getbootstrap.com/
    https://github.com/davidjbradshaw/image-map-resizer
    https://jquery.com/

\newpage
