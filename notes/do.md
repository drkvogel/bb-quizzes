## todo

* Implement the re-sizing algorithm for Matrix as specified previously (cap to stop shrinking at 320px)
* Implement re-sizing in Hoops and finish the interface for that program.
* Complete documentation for Matrix and produce similar for Hoops,
* Alter systems so that data is uploaded to server automatically when last screen in test is completed (Jonathan has working code for this which can provide template).  If possible a busy/hourglass cursor could be displayed while data is uploading [don't spend more than an hour on this - if it's not easy to do, then forget it].  After test is completed user should be directed to a simple "Thank You" screen.

Matrix : structure, technology and algorithms
Hoops : structure, technology and algorithms
* representation of the <div>s in the page, description of the purpose of each.
* image sizes
* names of any included libraries (e.g. node.js)
* description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208



git log a single file:

    $ gitk ~/Projects/bb-quizzes/hoops/yo/app/index.html
    $ git log -p ~/Projects/bb-quizzes/hoops/yo/app/index.html

use pesticide.io
fossilize... 
look at fossil bugs bb-quizzes.fossil

aycalc
    abandon still scrolls off in some dimensions - does it? (`#abandon-div` is outside `#page`)
    js keeps it roughly square but that is not exactly what we want, too much whitespace at the bottom for a start
    abandon button vanishes



2nd to last image (coloured squares) bottom grid not aligned with image map

hoops: image stops stretching horizontally because .container has a set width - clear this and it will stretch the whole width

    @media (min-width: 768px)
    .container {
        width: 750px;
    }

/home/cbird/Projects/general/dev/web/responsive/responsive.md