# Matrix Quiz : structure, technology and algorithms

<https://docs.google.com/document/d/1gcFqC2Ys2w95EOjHP7wLUNbz98NkUM6AFgYvDMaRavY/>

* representation of the `<div>`s in the page, description of the purpose of each.
* image dimensions
* names of any included libraries (e.g. node.js)
* description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208

## Contents

A document describing the structure, technology and sizing algorithms in the main web-page of the Matrices questionnaire.

* A pictorial representation of the `<div>`s in the page, accompanied by a brief description of the purpose of each.
* image dimensions
* included libraries
* A description (with pseudo-code) of the algorithm used to determine the scaling of the image elements
* Worked numeric examples for various screen resolutions

---



## Layout

  
    body                HTML <body> tag
    div.container       Added by Yeoman/Bootstrap to add page margins. Possibly not needed.
    div#pages           A container for the pages, one of which is shown at a time
    div#quiz2x2.quiz    A page div, the 2x2 quiz is shown in this example.
    div                 Unnecessary, removed.
    div.gridContainer   Used to keep grids together and scaled relative to  each other, and to centre using left and right margins
    .grid2x2            Contains the top grid image
    .grid3x2            Contains the bottom grid image, and some padding to distance it from the top grid
    img.top             The top grid image, which is changed by main.js
    img.bot             The bottom grid image, which is changed by main.js
    div.botText         Holds the explanatory text when required

## Description of scaling algorithm


    # body > div.container > div#pages > div#quiz2x2.quiz > div.gridContainer > .grid2x2 .grid3x2

    # get the margin widths
    margins =   ($('.container').outerWidth(true) - $('.container').width()) + 
                ($('#pages').outerWidth(true) - $('#pages').width())

    #  subtract from the viewport width – height, divide by 2 for left and right margins
    setMargin = ($(window).width() - ($(window).height() - $('.botText').height()) - margins) / 2

    if (setMargin > 0):
        $('.gridContainer').css('margin-left', setMargin) # set the margins to (screen width - height) / 2
        $('.gridContainer').css('margin-right', setMargin)
    else:
        $('.gridContainer').css('margin-left', 0)  # set the margins to (screen width - height) / 2
        $('.gridContainer').css('margin-right', 0)

## Worked examples

Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208.

1308 x 598:

    margins = ($('.container').outerWidth(true)[1308] - $('.container').width())[1278]
    * ($('#pages').outerWidth(true)[1278] - $('#pages').width()[1278]) == 30

    setMargin = ($(window).width()[1308] - ($(window).height()[598] - $('.botText').height()[-18]) - margins[30]) / 2 == 331

1280x1024

640x480

320x480

750x1334

1242x2208

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

## Details of image sizes

    2016-07-01 14:55:26 ~/Projects/bb-quizzes/matrix/yo/app/images
    $ find . | xargs file > tmp.txt




