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

>description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.

Uses same scaling algorithm as the Matrix puzzle.

\newpage

## Worked Examples

>Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208

todo

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

## Appendix

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
    duration1   INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle1     INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed1    INTEGER4    Yes     None    Cumulative time elapsed
    answer1     INTEGER4    Yes     None    Answer given by user
    correct1    INTEGER4    Yes     None    Correct answer
    duration2   INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle2     INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed2    INTEGER4    Yes     None    Cumulative time elapsed
    answer2     INTEGER4    Yes     None    Answer given by user
    correct2    INTEGER4    Yes     None    Correct answer
    duration3   INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle3     INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed3    INTEGER4    Yes     None    Cumulative time elapsed
    answer3     INTEGER4    Yes     None    Answer given by user
    correct3    INTEGER4    Yes     None    Correct answer
    duration4   INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle4     INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed4    INTEGER4    Yes     None    Cumulative time elapsed
    answer4     INTEGER4    Yes     None    Answer given by user
    correct4    INTEGER4    Yes     None    Correct answer
    duration5   INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle5     INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed5    INTEGER4    Yes     None    Cumulative time elapsed
    answer5     INTEGER4    Yes     None    Answer given by user
    correct5    INTEGER4    Yes     None    Correct answer
    duration6   INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle6     INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed6    INTEGER4    Yes     None    Cumulative time elapsed
    answer6     INTEGER4    Yes     None    Answer given by user
    correct6    INTEGER4    Yes     None    Correct answer
    duration7   INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle7     INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed7    INTEGER4    Yes     None    Cumulative time elapsed
    answer7     INTEGER4    Yes     None    Answer given by user
    correct7    INTEGER4    Yes     None    Correct answer
    duration8   INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle8     INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed8    INTEGER4    Yes     None    Cumulative time elapsed
    answer8     INTEGER4    Yes     None    Answer given by user
    correct8    INTEGER4    Yes     None    Correct answer
    duration9   INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle9     INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed9    INTEGER4    Yes     None    Cumulative time elapsed
    answer9     INTEGER4    Yes     None    Answer given by user
    correct9    INTEGER4    Yes     None    Correct answer
    duration10  INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle10    INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed10   INTEGER4    Yes     None    Cumulative time elapsed
    answer10    INTEGER4    Yes     None    Answer given by user
    correct10   INTEGER4    Yes     None    Correct answer
    duration11  INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle11    INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed11   INTEGER4    Yes     None    Cumulative time elapsed
    answer11    INTEGER4    Yes     None    Answer given by user
    correct11   INTEGER4    Yes     None    Correct answer
    duration12  INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle12    INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed12   INTEGER4    Yes     None    Cumulative time elapsed
    answer12    INTEGER4    Yes     None    Answer given by user
    correct12   INTEGER4    Yes     None    Correct answer
    duration13  INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle13    INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed13   INTEGER4    Yes     None    Cumulative time elapsed
    answer13    INTEGER4    Yes     None    Answer given by user
    correct13   INTEGER4    Yes     None    Correct answer
    duration14  INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle14    INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed14   INTEGER4    Yes     None    Cumulative time elapsed
    answer14    INTEGER4    Yes     None    Answer given by user
    correct14   INTEGER4    Yes     None    Correct answer
    duration15  INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle15    INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed15   INTEGER4    Yes     None    Cumulative time elapsed
    answer15    INTEGER4    Yes     None    Answer given by user
    correct15   INTEGER4    Yes     None    Correct answer
    duration16  INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle16    INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed16   INTEGER4    Yes     None    Cumulative time elapsed
    answer16    INTEGER4    Yes     None    Answer given by user
    correct16   INTEGER4    Yes     None    Correct answer
    duration17  INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle17    INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed17   INTEGER4    Yes     None    Cumulative time elapsed
    answer17    INTEGER4    Yes     None    Answer given by user
    correct17   INTEGER4    Yes     None    Correct answer
    duration18  INTEGER4    Yes     None    Time taken to answer puzzle
    puzzle18    INTEGER4    Yes     None    Puzzle chosen by algorithm
    elapsed18   INTEGER4    Yes     None    Cumulative time elapsed
    answer18    INTEGER4    Yes     None    Answer given by user
    correct18   INTEGER4    Yes     None    Correct answer
    
    Secondary Indices:None
    Constraints:None
    Rules:None
    Grants:None