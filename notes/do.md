## todo

before meeting: docs ready, cgis pushed, git lsd printout

Matrix still looks crap on phone: 
    Too much space, Abandon should stick to bottom, Can multiple click
    matrix looks shite on rotated phone - should use media queries to flow images
    Galaxy Core Prime - 800 x 480
thorough test with browserstack
did scaleImagesCBSimple() work? push cbsimple to red
Matrices and Hoops documentation and attach them to the appropriate bugs general.git\dev\pandoc.md
    algorithm workings (though algorithm works)
    db comments -> db doc -> ay eml | tee bugzilla

resource hints: preload, prefetch etc
there is still a border left around the last clicked image map...

scaleImagesCBnew():
get the various heights with jquery
max height of 
width-wise, if there is enough height, there will be no margins on the images and they will scale to fit anyway (width: 100%)
// missing some widths and heights?

hoops scales but not brilliantly - text, buttons scroll off bottom. margin-left, margin-right being calculated and inserted on resize - scaleImages()
fossilize... look at fossil bugs bb-quizzes.fossil
aycalc
    abandon still scrolls off in some dimensions - does it? (`#abandon-div` is outside `#page`)
    js keeps it roughly square but that is not exactly what we want, too much whitespace at the bottom for a start
