Hoops Quiz : structure, technology and algorithms

Google docs - too few options, annoying "features" e.g. spellcheck can't turn off
doing this - in text, md - have to format it all differently so would have to spend ages making it into a Word doc...
though pandoc can do this
what about images?

    2016-07-29 01:32:24 kvogel@yoga3-vlubuntu ~/Projects/bb-quizzes/doc/matrix
    $ pandoc -o ~/Dropbox/matrix.docx -f markdown -t docx matrix-doc.md
    $ \ls ~/Dropbox

https://docs.google.com/document/d/12csdd4ncqbiC-Kw6C2bjopYhiiZJoaMxMkKj0DiDBYU/edit#heading=h.fsk7l5xa17k5

* representation of the <div>s in the page, description of the purpose of each.
* image dimensions
* names of any included libraries (e.g. node.js)
* description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.
* Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208


## Description of page elements

>representation of the <div>s in the page, description of the purpose of each.




## Image Dimensions

The images are all PNG format, 8-bit/color RGBA, non-interlaced.
There are five images, one for each page, in the introduction: `intro1.png` to `intro5.png`. They have the dimensions 748px x 470px.
Apart from the intro screens, the other images are 748px x 291px, two on each screen, one at the top, one at the bottom.

The image at the top remains constant (this is different from the original test, where the bottom image remains constant). Its name is `top-constant.png`

The other images change on each page in a psuedo-random fashion. I have name them in the format:

    t3<x>2<y>1<z>.png

where:

`t` stands for tile
3 is the leftmost peg, which can hold 3 hoops
`<x>` is a sequence of letters describing which hoops are on the peg denoted by the preceding number, from top to bottom, using the letters `y`, `b` and `w` for Yellow, Black and White, respectively.
2 is the middle peg, which can hold 2 hoops
`<y>` is the sequence of hoops from top to bottom on the middle peg
1 is the rightmost peg, which can hold 1 hoop
`<z>` is the sequence of hoops from top to bottom on the rightmost peg

Thus, we have the images:

    t32by1w.png, t32wy1b.png, t3bw21y.png, t3w2b1y.png, t3w2yb1.png, t3wb2y1.png, t3wy2b1.png, t3y2b1w.png, t3yb21w.png, t3ybw21.png, t3yw21b.png, t3yw2b1.png, t3ywb21.png


## List of Libraries

>names of any included libraries (e.g. node.js)


## Description of Scaling Algorithm

>description with pseudo-code of scaling algorithm based around the method I outlined - i.e. determine separately the scaling in each of the horizontal and vertical directions required to fit the window, then resize using the smaller of these factors as a parameter.


## Worked Examples

>Worked numeric examples for screen resolutions of (HxV) 1280x1024, 640x480, 320x480, 750x1334 and 1242x2208

## Appendix

    2016-07-31 01:08:01 kvogel@yoga3-vlubuntu ~/Projects/bb-quizzes/hoops/yo/app/images
    $ file *
    intro1.png:       PNG image data, 748 x 470, 8-bit/color RGBA, non-interlaced
    intro2.png:       PNG image data, 748 x 470, 8-bit/color RGBA, non-interlaced
    intro3.png:       PNG image data, 748 x 470, 8-bit/color RGBA, non-interlaced
    intro4.png:       PNG image data, 748 x 644, 8-bit/color RGBA, non-interlaced
    intro5-orig.png:  PNG image data, 748 x 723, 8-bit/color RGBA, non-interlaced
    intro5.png:       PNG image data, 748 x 487, 8-bit/color RGBA, non-interlaced
    t32by1w.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t32wy1b.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3bw21y.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3w2b1y.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3w2yb1.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3wb2y1.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3wy2b1.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3y2b1w.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3yb21w.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3ybw21.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3yw21b.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3yw2b1.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    t3ywb21.png:      PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
    top-constant.png: PNG image data, 748 x 291, 8-bit/color RGBA, non-interlaced
