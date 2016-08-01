## todo

* Implement the re-sizing algorithm for Matrix as specified previously (cap to stop shrinking at 320px)
* Implement re-sizing in Hoops and finish the interface for that program.
* Complete documentation for Matrix and produce similar for Hoops

Matrix : structure, technology and algorithms
Hoops : structure, technology and algorithms

* representation of the `<div>`s in the page, description of the purpose of each.
* image sizes
* names of any included libraries (e.g. node.js)
* description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208

>determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.

determine the scaling in each of the horizontal and vertical directions required to fit the window
  scaling of what? 
  height and width of whole thing without scaling? which is what? the natural size? depends on how big the viewport is...
then resize using the smaller of these factors as a parameter

### scaleImagesCBsimple()

    setMargins = ($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;

// missing some widths and heights?
try to keep the `div.gridContainer` element square by setting margins
abandon button scrolls off the bottom at extreme width and short height.

### scaleImagesCBnew()

get the various heights with jquery
max height of 
width-wise, if there is enough height, there will be no margins on the images and they will scale to fit anyway (width: 100%)

### scaleImagesAY()

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

widthExtra
heightExtra

fullWidth = widthExtra + $('.bot').width()
fullHeight = heightExtra + $('.top').height() + $('bot').height()


### width (symmetrical about y axis)

    html                -
    body                -
    #devBar             hidden
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

* div.container padding: 15px 10px 20px 10px; (N, E, S, W)
* div#pages has margin: auto but always fills div.container
* hard-code natural image sizes - see "Can we get the native/natural height of images?"

    2x2, 3x2
    img.top natural: 420 x 340
    img.bot natural: 680 x 365

    3x3, 4x2
    img.top natural: 510 x 405
    img.bot natural: 755 x 295

### height

    html                -
    body                -
    #devBar             hidden
    div.container       padding-top: 15px
    div#pages           -
    div#quiz2x2.quiz    -
    div.gridContainer   margins set by calc
    img.top (natural)   340px (quiz2x2) | 405px (quiz3x3)
    div.grid3x2         padding-top: 5% e.g. 34px
    img.bot (natural)   365px (quiz2x2) | 295px (quiz3x3)
    div#quiz2x2.quiz    -
    div#pages           -
    div.container       padding-bottom: 20px
    body                -
    html                -


get code to print worked examples

matrix element heights (top to bottom)

    #devBar          usually hidden
    padding         fixed?
    .topTxt          fixed, unless width small enough to cause text to wrap  
    .gridContainer   the element we want to scale so that it's height combined with the other elements' heights will fit in the viewport
      .grid3x2 padding-top: 5%
    .botTxt          fixed, unless width small enough to cause text to wrap
    .navCtl          fixed
    padding         fixed?

hoops element heights (top to bottom)

    devBar          usually hidden
    padding         fixed?
    topTxt          fixed, unless width small enough to cause text to wrap  
    middleImg       the element we want to scale so that it's height combined with the other elements' heights will fit in the viewport
    botTxt          fixed, unless width small enough to cause text to wrap
    navCtl          fixed
    padding         fixed?


hoops scales but not brilliantly - text, buttons scroll off bottom. margin-left, margin-right being calculated and inserted on resize - scaleImages()

fossilize... look at fossil bugs bb-quizzes.fossil
aycalc
    abandon still scrolls off in some dimensions - does it? (`#abandon-div` is outside `#page`)
    js keeps it roughly square but that is not exactly what we want, too much whitespace at the bottom for a start

