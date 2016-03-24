
## notes

html div to use (intro1-3, 2x2, 3x3, thanks, abandon etc)
sprite sheet to use
list of indices into sprite sheet for top and bottom grids
correct answer

### css grid layout

http://jsfiddle.net/Madmartigan/34UCn/5/

```html
    <div class="wrapper">
        <div>
             <img><img><img>
             <img><img><img>
             <img><img><img>
             <img><img><img>
        </div>
    </div>
```

```css
.wrapper {
    overflow:hidden;
    width:320px;
}
.wrapper div {
    /* any width up to (total img width) * (num_columns) */
    /* the rest will be chopped off by overflow:hidden */
    width:330px;
    
    /* chops off top "padding" of inner div (first row imgs top margin) */
    margin-top:-10px;
}
img {
    width:100px;
    height:75px;
    float:left;
    margin:10px 10px 0 0;
}

/* decoration */
img {
     background:blue;   
}
.wrapper {
    background:red;
}
```
