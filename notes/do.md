## todo

hoops - allow explan text to be wider
hoops - abandon seems to trigger of its own accord
hoops - implement form submit

* Implement the re-sizing algorithm for Matrix as specified previously (cap to stop shrinking at 320px)
* Implement re-sizing in Hoops and finish the interface for that program.
* Complete documentation for Matrix and produce similar for Hoops,

Matrix : structure, technology and algorithms
Hoops : structure, technology and algorithms
* representation of the <div>s in the page, description of the purpose of each.
* image sizes
* names of any included libraries (e.g. node.js)
* description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208


description of images - size of icons and spacings between them for the 2 layouts for the Hoops system

hoops scales on dev gulp serve, and on red, and http://kvogel.net/hoops/...
but not brilliantly - text, buttons scroll off bottom
margin-left, margin-right being calculated and inserted on resize

```html
    <div style="margin-left: 386.5px; margin-right: 386.5px;" class="container">
      <div id="pages"> <!-- style="display: none"> -->
        ...
      </div> <!-- pages -->
      <div style="display: none;" id="abandon-div" class="row">
        <button class="btn" id="abandon-btn" href="#">Abandon</button>
      </div>
    </div>
```



use pesticide.io
fossilize... 
look at fossil bugs bb-quizzes.fossil

aycalc
    abandon still scrolls off in some dimensions - does it? (`#abandon-div` is outside `#page`)
    js keeps it roughly square but that is not exactly what we want, too much whitespace at the bottom for a start
    abandon button vanishes


/home/cbird/Projects/general/dev/web/responsive/responsive.md

