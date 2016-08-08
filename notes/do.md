## todo

Galaxy Core Prime - 800 x 480

* Implement the re-sizing algorithm for Matrix as specified previously (cap to stop shrinking at 320px)
* Implement re-sizing in Hoops and finish the interface for that program.
* Complete documentation for Matrix and produce similar for Hoops

* description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208


determine the scaling in each of the horizontal and vertical directions required to fit the window
  scaling of what? 
  height and width of whole thing without scaling? which is what? the natural size? depends on how big the viewport is...
then resize using the smaller of these factors as a parameter

### scaleImagesCBnew()

get the various heights with jquery
max height of 
width-wise, if there is enough height, there will be no margins on the images and they will scale to fit anyway (width: 100%)
// missing some widths and heights?




get code to print worked examples
hoops scales but not brilliantly - text, buttons scroll off bottom. margin-left, margin-right being calculated and inserted on resize - scaleImages()
fossilize... look at fossil bugs bb-quizzes.fossil
aycalc
    abandon still scrolls off in some dimensions - does it? (`#abandon-div` is outside `#page`)
    js keeps it roughly square but that is not exactly what we want, too much whitespace at the bottom for a start


