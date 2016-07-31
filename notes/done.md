## done


get rid of the other ones (intro1/2/3) - the only ones in use are:

    "templateId": "home",
    "templateId": "quiz2x2",
    "templateId": "quiz3x3",
    "templateId": "getReady",
    "templateId": "thanks",

description of images - size of icons and spacings between them for the 2 layouts for the Hoops system
553:31  error  event is defined but never used  no-unused-vars # `/*eslint-disable no-unused-vars*/ `
hoops - implement form submit
hoops - take off "Next" on intro test, forcing user to make a guess
hoops: scaleImages() on show, not just resize
hoops: abandon didn't work - put abandon-modal in html

shrink containing div - too big-
with `.top, .bot { width: 100%; }`, image map doesn't work-x
log IP?-x
matrix incorrect gone off to side- .my_modal_content set width, not max width
send result automatically with submit
description of images - size of icons and spacings between them for the 2 layouts for the Matrix system

* Alter systems so that data is uploaded to server automatically when last screen in test is completed (Jonathan has working code for this which can provide template).  
    - function finished()-/
* After test is completed user should be directed to a simple "Thank You" screen.


hoops media query breakpoint - override
goes awry >window width >=992 - like a media query breakpoint
http://localhost:9001/styles/main.css
bower_components/bootstrap-sass/assets/stylesheets/bootstrap/_grid.scss:10
```css
@(min-width: 992px)
.container {
    width: 970px;
}
```

2nd to last image (coloured squares) bottom grid not aligned with image map

hoops: image stops stretching horizontally because .container has a set width - clear this and it will stretch the whole width

    @media (min-width: 768px)
    .container {
        width: 750px;
    }

Google docs - too few options, annoying "features" e.g. spellcheck can't turn off
doing this - in text, md - have to format it all differently so would have to spend ages making it into a Word doc...
though pandoc can do this
what about images?

    2016-07-29 01:32:24 kvogel@yoga3-vlubuntu ~/Projects/bb-quizzes/doc/matrix
    $ pandoc -o ~/Dropbox/matrix.docx -f markdown -t docx matrix-doc.md
    $ \ls ~/Dropbox

https://docs.google.com/document/d/12csdd4ncqbiC-Kw6C2bjopYhiiZJoaMxMkKj0DiDBYU/edit#heading=h.fsk7l5xa17k5











hoops - use unmin imageMapResizer?-x doesn't use 
sticky footer?-x

git log a single file:

    $ gitk ~/Projects/bb-quizzes/hoops/yo/app/index.html
    $ git log -p ~/Projects/bb-quizzes/hoops/yo/app/index.html

fossil workflow too slow/labourious, use text-
unfuddle?-x
dev prev button doesn't work now unless navbar fits on one line-x