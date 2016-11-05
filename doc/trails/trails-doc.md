
# Trails Quiz : structure, technology and algorithms

## Contents

* Representation of the elements in the page, description of the purpose of each.
* Image dimensions
* Description of scaling algorithm
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208
* Names of any included libraries

\newpage

## Description of page elements

![trails layout](trails-layout.png "trails layout")

>representation of the HTML elements in the trails puzzle, with a description of the purpose of each.

    body                    HTML <body> tag
    #devBar                 hidden    
    div.container           Used to add page margins
    div#pages               Container to switch the pages
    div.page#game           Container for the main puzzle
    [TODO]
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
    [TODO]
    div.botText         72px minimum (if not wrapped) (if visible)
    div#answers         -
    div.navCtl          
    div#pages           -
    div#abandon-div     34px (if visible)
    div.container       padding-bottom: 20px
    body                -
    html                -

\newpage

## Image details

[TODO]
svg
object


\newpage

## Description of Scaling Algorithm

#### Pseudo-code for scaling algorithm

[TODO]

#### JavaScript code for scaling algorithm

[TODO]

\newpage

## Worked Examples

>Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208

### 1280x1024


### 640x480


### 320x480


### 750x1334


### 1242x2208


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

## Database table for trails Quiz

    (Table) cp.trails
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
    [TODO]    
    Secondary Indices:None
    Constraints:None
    Rules:None
    Grants:None

\newpage

## Appendix

