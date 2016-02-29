
function highlight(id)
{
    document.getElementById(id).style.backgroundColor = "Yellow";
}

function unhighlight(id)
{
    document.getElementById(id).style.backgroundColor = "Black";
}

function unhighlight(id,colour)
{
    if (colour == undefined)
        document.getElementById(id).style.backgroundColor = "White";
    else
        document.getElementById(id).style.backgroundColor = colour;
}

function now()
{    //milliseconds for elapsed time calculation
    var d = new Date();
    return d.getTime();
}
