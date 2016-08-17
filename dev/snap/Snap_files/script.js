function SelectRadio(buttonId) 
{ 
    var rButton = document.getElementById(buttonId);
    rButton.checked = true;
    rButton.click();
}

function Script_noBackButton()
{
	location.hash='#no-';
    if(location.hash == '#no-')
    {
        location.hash='#_';
        window.onhashchange=function()
        {
            if(location.hash == '#no-')
            {
                location.hash='#_';
            }
        };
    }
}
Script_noBackButton();
