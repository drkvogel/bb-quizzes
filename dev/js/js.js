
// http://eslint.org/docs/rules/no-use-before-define

/*eslint no-use-before-define: "error"*/
/*eslint-env es6*/

//alert(a);
console.log('a: ' + String(a));
var a = 10;

f();
function f() {}

function g() {
    return b;
}
var b = 1;

// With blockBindings: true
{
    //alert(c);
    //let c = 1;
    console.log('c: ' + String(c));
    c = 10;
}
