### Display grids

Tue Mar 15 01:22:49 2016 images renamed to better reflect order
range of dimensions: 

    dim         sq width    grid type
    ---------------------------------
    1260x170    210         2x2 3x2 
    1470x170    210         2x2 3x2 
    1680x170    210         2x2 3x2 
    1890x170    210         2x2 3x2 
    1360x135    170         3x3 4x2
    2040x135    170         3x3 4x2
    2380x135    170         3x3 4x2
    2720x135    170         3x3 4x2

so, two types of grid, with different image dimensions:

    grid        images
    -------------------
    2x2 3x2     210x170
    3x3 4x2     170x135

    image                dimensions  squares sq.w    grid
    --------------------------------------------------------
    intro1.png           1260x170    6x1     210     2x2 3x2
    intro2.png           1260x170    6x1     210     2x2 3x2
    intro3.png           2380x135    14x1    170     3x3 4x2
    matrix_ex1.png       1360x135    8x1     170     3x3 4x2
    matrix_ex2.png       1680x135    8x1     210     2x2 3x2
    matrix_ex3.png       1470x170    7x1     210     2x2 3x2
    matrix_ex4.png       1890x170    9x1     210     2x2 3x2
    matrix_ex5.png       1260x170    6x1     210     2x2 3x2
    matrix_ex6.png       2380x135    14x1    170     3x3 4x2
    matrix_ex7.png       2720x135    16x1    170     3x3 4x2
    matrix_ex8.png       2040x135    12x1    170     3x3 4x2
    matrix_ex9.png       2720x135    16x1    170     3x3 4x2
    matrix_ex10.png      2720x135    16x1    170     3x3 4x2
    matrix_ex11.png      2720x135    16x1    170     3x3 4x2
    matrix_ex12.png      2720x135    16x1    170     3x3 4x2
    matrix_ex13.png      2720x135    16x1    170     3x3 4x2
    matrix_ex14.png      2720x135    16x1    170     3x3 4x2
    matrix_ex15.png      2720x135    16x1    170     3x3 4x2

n.b. CSS class ids are not allowed to start with a number! so "2x2" is invalid...

and again! lower grid cells were id'd "1a, 1b, 1c" etc which are invalid ids... renamed "cell-1a" etc