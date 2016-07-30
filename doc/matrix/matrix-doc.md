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


images/intro1/intro1-sol5.png:     PNG image data, 420 x 340, 8-bit/color RGBA, non-interlaced
images/intro1/intro1-palette.png:  PNG image data, 680 x 365, 8-bit/color RGBA, non-interlaced

images/ex5/ex5-sol2.png:           PNG image data, 420 x 340, 8-bit/color RGBA, non-interlaced
images/ex5/ex5-palette.png:        PNG image data, 680 x 365, 8-bit/color RGBA, non-interlaced

images/ex7/ex7-sol1.png:           PNG image data, 510 x 405, 8-bit/color RGBA, non-interlaced
images/ex7/ex7-palette.png:        PNG image data, 755 x 295, 8-bit/color RGBA, non-interlaced

images/ex13/ex13-sol4.png:         PNG image data, 511 x 411, 8-bit colormap, non-interlaced
images/ex13/ex13-palette.png:      PNG image data, 755 x 295, 8-bit/color RGBA, non-interlaced

images/ex14/ex14-sol6.png:         PNG image data, 307 x 302, 8-bit colormap, non-interlaced
images/ex14/ex14-palette.png:      PNG image data, 755 x 295, 8-bit/color RGBA, non-interlaced
the one with the coloured squares - top and bottom are clearly different sizes

images/ex15/ex15-sol6.png:         PNG image data, 534 x 422, 8-bit colormap, non-interlaced
images/ex15/ex15-palette.png:      PNG image data, 755 x 295, 8-bit/color RGBA, non-interlaced

but all palette images overlayed with imagemaps are consistent
and differences in top images not really noticeable

### 2x2


top image:      420px x 340px
each tile is    210px x 170px
with no space between them

bottom image:   680px x 365px
3 tiles wide x 2 tiles high
each tile is    210px x 170px
there is a gap of 25px between each tile, horizontally and vertically

# 3x3 problem

top image:      510px x 405px
each tile is    170px x 135px
with no space between them

bottom image:   755px x 295px
4 tiles wide x 2 tiles high
each tile is    170px x 135px
there is a gap of 25px between each tile, horizontally and vertically






