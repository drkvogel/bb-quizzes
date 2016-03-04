var NUM_PAGES = 19;
var levels = [
    "matrix_ex1", "matrix_ex2", "matrix_ex3", "transition", "matrix_ex4", "matrix_ex5", "matrix_ex6", "matrix_ex7", "matrix_ex8", "matrix_ex9", "matrix_ex10", "matrix_ex11", "matrix_ex12", "matrix_ex13", "matrix_ex14", "matrix_ex15", "matrix_ex16", "matrix_ex17", "matrix_ex18"
];
var level_TRANSITION = 123;
var isLive      = [0,0,0,level_TRANSITION,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1];
var Buttons     = [6,6,8,level_TRANSITION,8,6,6,6,6,8,8,8,8,8,8,8,8,8,8];
var Expected    = [4,4,5,level_TRANSITION,3,2,3,0,3,5,0,5,3,0,7,6,7,2,6];

// js doesn't have array width specifier like C++
// [NUM_PAGES]
// [NUM_PAGES][8]

var layout_questions = [
    [4,4,4,-1,-1,-1,-1,-1],
    [4,4,4,-1,-1,-1,-1,-1],
    [8,9,10,0,1,2,4,5],
    [-1,-1,-1,-1,-1,-1,-1,-1],
    [1,1,1,2,2,2,3,3],
    [6,7,5,-1,-1,-1,-1,-1],
    [0,1,2,-1,-1,-1,-1,-1],
    [0,1,2,-1,-1,-1,-1,-1],
    [4,2,0,-1,-1,-1,-1,-1],
    [0,1,2,3,4,5,6,7],
    [0,1,2,3,4,5,6,7],
    [0,1,2,3,4,5,6,7],
    [0,1,2,3,4,5,6,7],
    [0,1,2,3,4,5,6,7],
    [0,1,2,3,4,5,6,7],
    [0,1,2,3,4,5,6,7],
    [0,1,2,3,4,5,6,7],
    [8,9,10,11,12,13,14,15],
    [0,1,2,3,4,5,6,7]
];  // top images

var layout_buttons =[
    [0,1,2,3,4,5,-1,-1],
    [0,1,2,3,4,5,-1,-1],
    [7,1,3,12,8,6,9,13],
    [-1,-1,-1,-1,-1,-1,-1,-1],
    [0,1,2,3,4,5,6,7],
    [0,1,2,5,3,4,-1,-1],
    [2,1,5,3,4,6,-1,-1],
    [3,4,5,6,7,8,-1,-1],
    [0,1,2,3,4,5,-1,-1],
    [2,1,8,9,10,11,12,13],
    [8,9,10,11,12,13,14,15],
    [6,8,2,0,9,10,11,4],
    [8,9,10,11,12,13,14,15],
    [8,9,10,11,12,13,14,15],
    [8,9,10,11,12,13,14,15],
    [8,9,10,11,12,13,14,15],
    [8,9,10,11,12,13,14,15],
    [0,1,2,3,4,5,6,7],
    [8,9,10,11,12,13,14,15]
];   // bottom images