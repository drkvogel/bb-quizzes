## todo

* Implement the re-sizing algorithm for Matrix as specified previously (cap to stop shrinking at 320px)
* Implement re-sizing in Hoops and finish the interface for that program.
* Complete documentation for Matrix and produce similar for Hoops

* description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208

>determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.

determine the scaling in each of the horizontal and vertical directions required to fit the window
  scaling of what? 
  height and width of whole thing without scaling? which is what? the natural size? depends on how big the viewport is...
then resize using the smaller of these factors as a parameter

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

fullWidth = widthExtra + $('.bot').width()
fullHeight = heightExtra + $('.top').height() + $('bot').height()

get code to print worked examples


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

