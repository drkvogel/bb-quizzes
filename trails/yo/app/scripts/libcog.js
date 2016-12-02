
function debounce(func, wait, immediate) {
    console.log('debounce');
    var timeout;
    return function() {
        var context = this, args = arguments; // JavaScript functions have a built-in object called the arguments object.
        var later = function() {
            timeout = null;
            if (!immediate) {
                func.apply(context, args); // apply() built-in calls func with args in array
            }
        };
        var callNow = immediate && !timeout;
        clearTimeout(timeout);
        timeout = setTimeout(later, wait || 200);
        if (callNow) {
            func.apply(context, args);
        }
    }
}



// var JD = {};

// JD.debounce = function(func, wait, immediate) {
//     var timeout;
//     return function() {
//         var context = this,
//             args = arguments;
//         var later = function() {
//             timeout = null;
//             if ( !immediate ) {
//                 func.apply(context, args);
//             }
//         };
//         var callNow = immediate && !timeout;
//         clearTimeout(timeout);
//         timeout = setTimeout(later, wait || 200);
//         if ( callNow ) {
//             func.apply(context, args);
//         }
//     };
// };

// JD.firstName = function() {
//     console.log('John');
// };

// JD.lastName = function() {
//     console.log('Dugan');
// };
// window.addEventListener('resize', JD.debounce(JD.lastName, 400));
// window.addEventListener('resize', JD.debounce(JD.firstName, 400, true));
