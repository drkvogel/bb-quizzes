function noBackButton() {
    location.hash='#no-';
    if(location.hash == '#no-') {
        location.hash='#_';
        window.onhashchange = function() {
            if(location.hash == '#no-') {
                location.hash='#_';
            }
        };
    }
}

noBackButton(); // ??

function now() { //milliseconds for elapsed time calculation
    var d = new Date();
    return d.getTime();
}

