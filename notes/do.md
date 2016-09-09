## todo

before meeting: docs ready, cgis pushed, git lsd printout

hoops scrolls off bottom: intro1 intro2
clear click border

hoops doc
record cumulative time, number answered


* Include worked examples of re-sizing in documentation.
* Fix data bug in hoops which appears to be resulting in incorrect data being output. Please check the output thoroughly
* I'm glad you've been able to get a dummy CGI saving to database and have sent me the hoops documentation and database field types, however all the other jobs from our last meeting are still in the ToDo list.
* Please discuss the hoops data format/algorithm with Jonathan rather than spending time trying to deduce it from the code.  All I care about is getting a working system - if 10 minutes of his time can save hours of yours then that's a win as far as I'm concerned.
* I'm away for a week now so our next meeting is on 29th Aug.  As this is a fortnight I'd expect you can completely finish all the tasks from our previous meeting (as listed below) by then.
* Assuming the tasks below are finished (and only then), please look at the cognitive tests Jonathan deployed last year with a view to redoing their presentation to make the interfaces fully responsive to size changes if they are not already.  All I'm looking for here is an initial verbal assessment - I don't want specs or code at this stage.
* I'll contact Jonathan to advise him of his role in what I've requested you to do as outlined above.
* You mentioed you might need to take odd days leave while I'm away. 
Please consider this pre-approved but, once you know them, drop me an email regardless for each date prior to taking it and ensure it goes into your calendar.
* We'll discuss priororising the Lind library work at a future meeting.

Matrix still looks crap on phone: 
    Too much space, Abandon should stick to bottom, Can multiple click
    matrix looks shite on rotated phone - should use media queries to flow images
did scaleImagesCBSimple() work? 
    push cbsimple to red
Matrices and Hoops documentation and attach them to the appropriate bugs general.git\dev\pandoc.md
    algorithm workings (though algorithm works)
    db comments -> db doc -> ay eml | tee bugzilla
backend insert - save data to database from CGIs



* Please send me electronically the Matrices and Hoops documentation and attach them to the appropriate bugs.
* Fix data bug in hoops which appears to be resulting in incorrect data being output. [This is #1 priority]
* Save data for both quizzes to database from CGIs.

supposed to do worked examples...
resource hints: preload, prefetch etc
there is still a border left around the last clicked image map...

* Implement re-sizing in Hoops and finish the interface for that program.
* Complete documentation for Matrix
* Complete documentation for Hoops
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208


### scaleImagesCBnew()

get the various heights with jquery
max height of 
width-wise, if there is enough height, there will be no margins on the images and they will scale to fit anyway (width: 100%)
// missing some widths and heights?


Galaxy Core Prime - 800 x 480


get code to print worked examples
hoops scales but not brilliantly - text, buttons scroll off bottom. margin-left, margin-right being calculated and inserted on resize - scaleImages()
fossilize... look at fossil bugs bb-quizzes.fossil
aycalc
    abandon still scrolls off in some dimensions - does it? (`#abandon-div` is outside `#page`)
    js keeps it roughly square but that is not exactly what we want, too much whitespace at the bottom for a start


