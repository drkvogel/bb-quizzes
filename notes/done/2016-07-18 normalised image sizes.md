

## done

(after being ill for about 2 weeks, 4 days off sick)

imagemap does not match image on 10, 13, 14, 15, 16, 17, 18, 19 - change map or image
on those images where the imagemap does not match, the border of the clickable `area` is left visible after showing the next page

the first live quiz is page 5, so 10, 13, 14, 15, 16, 17, 18, 19 are

    2016-07-18 15:43:26 cbird@q108-vlubuntu ~/Projects/bb-quizzes/matrix/yo
    $ bpython 
    >>> r = map(lambda x: x - 4, a)
    >>> r
    [6, 9, 10, 11, 12, 13, 14, 15]

list of palette images, some of which don't match the imagemap:

     blank-3x2-palette.png:      PNG image data, 680 x 365
     blank-4x2-palette.png:      PNG image data, 755 x 295
     intro1/intro1-palette.png:  PNG image data, 680 x 365
     intro2/intro2-palette.png:  PNG image data, 680 x 365
     intro3/intro3-palette.png:  PNG image data, 755 x 295
     ex1/ex1-palette.png:        PNG image data, 755 x 295
     ex2/ex2-palette.png:        PNG image data, 680 x 365
     ex3/ex3-palette.png:        PNG image data, 680 x 365
     ex4/ex4-palette.png:        PNG image data, 680 x 365
     ex5/ex5-palette.png:        PNG image data, 680 x 365
    !ex6/ex6-palette.png:        PNG image data, 857 x 293
     ex7/ex7-palette.png:        PNG image data, 755 x 295
     ex8/ex8-palette.png:        PNG image data, 755 x 295
    !ex9/ex9-palette.png:        PNG image data, 857 x 293
    !ex10/ex10-palette.png:      PNG image data, 857 x 293
    !ex11/ex11-palette.png:      PNG image data, 857 x 293
    !ex12/ex12-palette.png:      PNG image data, 857 x 293
    !ex13/ex13-palette.png:      PNG image data, 858 x 293
    !ex14/ex14-palette.png:      PNG image data, 791 x 261
    !ex15/ex15-palette.png:      PNG image data, 860 x 284

i.e. the 3x3 ones that aren't 755 x 295
in ex7-palette.png, which is "correct", each tile is 170px x 135px, and the difference horizontally and vertically between each tile is 25px.
and in ex6, ex9, ex10, ex11 (roughly), 12, 13, 15; but the spacing is 56px horizontally and 17px vertically
ex14 is different: the tiles are roughly 100 x 100, and the spacing is 122 x 53, roughly - they are not consistent
think easier to doctor images to be same dimensions than to swap in different area maps..
saved palette-755×295.xcf as template

to fit in the border of the tiles copied from ex7, the pasted area is 168 x 133
rather than carefully selecting 168 x 133 in the old palette image, carefully selecting same area within the target template:
fuzzy select inside border from source, add contents with rectangle select, add to current selection, copy, then:
fuzzy select inside border in destination, and do "Paste Into"

or: Colour Select all the whitespace, Invert Selection (ctrl-i), Rectangle Select with Intersect, copy, then paste into

in ex13, tiles have white inside them, so Colour Select was selecting that as well...

imagemap itself is a bit off, methinks...

Mon Jul 18 16:37:52 2016
Now have a 755 x 295 version of ex6

    2016-07-18 15:34:37 cbird@q108-vlubuntu ~/Projects/bb-quizzes/matrix/yo/app/images
    $ eog **/*palette.png   # recursive glob, even though: $ shopt globstar == globstar off?

Blisk doesn't show dimensions of page or device, sent feature request:
>When you choose a mobile device, it would be useful to see the resolution of that device displayed somewhere, and likewise the current dimensions of the web panel. Otherwise, great work!