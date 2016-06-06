


## learns


GIMP has an ImageMap plugin (Tools -> Filters -> Web -> Image Map...) to make making image maps quicker.

The `usemap` attribute of `<img>` is what connects it to the `<map>`. `#` prefix seems to be necessary in this link.

If you hover over the parts of the map with devtools open and the element picker enabled, the parts of the map will be hightlighted.

The fact that the name has spaces, e.g. `usemap="#3x2 matrix image map"` does not seem to matter.

If there is a "default" shape, i.e. `<area shape="default" href="#" />`, then the whole map is clickable even if there are gaps between the hot areas, and this specifies the default link - not what we want in this case. i.e. removing this line means the spaces between the choices in the matrix lower grid (the "palette") are not clickable.



From GIMP ImageMap plugin (Tools -> Filters -> Web -> Image Map...):

```html
<img src="intro1-palette.png" width="680" height="365" border="0" usemap="#3x2 matrix image map" />
```

The `usemap` attribute of `<img>` is what connects it to the `<map>`. `#` prefix seems to be necessary in link:

```html
<map name="3x2 matrix image map">
    <!-- #$-:Image map file created by GIMP Image Map plug-in -->
    <!-- #$-:GIMP Image Map plug-in by Maurits Rijk -->
    <!-- #$-:Please do not edit lines starting with "#$" -->
    <!-- #$VERSION:2.3 -->
    <!-- #$AUTHOR:Chris Bird -->
    <area id="bot0" shape="rect" coords="0,0,210,170" href="#" />
    <area id="bot1" shape="rect" coords="234,0,442,165" href="#" />
    <area id="bot2" shape="rect" coords="468,0,676,165" href="#" />
    <area id="bot3" shape="rect" coords="0,195,208,360" href="#" />
    <area id="bot4" shape="rect" coords="234,195,442,360" href="#" />
    <area id="bot5" shape="rect" coords="468,195,676,360" href="#" />
    <area shape="default" href="#" />
    </map>
```







Image map created by http://www.image-maps.com/map_image.php:

```html
<img id="Image-Maps-Com-image-maps-2016-06-05-203931" src="http://www.image-maps.com/m/private/0/pb3rmku4u30s3pk8aphisa7af6_intro1-palette.png" border="0" width="680" height="365" orgWidth="680" orgHeight="365" usemap="#image-maps-2016-06-05-203931" alt="" />
<map name="image-maps-2016-06-05-203931" id="ImageMapsCom-image-maps-2016-06-05-203931">
<area id="bot0" alt="Answer palette" title="Matrix Puzzle" href="http://red.ctsu.ox.ac.uk/~cp/cjb/matrix" shape="rect" coords="0,0,207,170" style="outline:none;" target="_self"     />
<area id="bot1" alt="" title="" href="#" shape="rect" coords="235,2,447,172" style="outline:none;" target="_self"     />
<area id="bot2" alt="" title="" href="#" shape="rect" coords="NaN,NaN,NaN,NaN" style="outline:none;" target="_self"     />
<area id="bot3" alt="" title="" href="#" shape="rect" coords="1,192,NaN,NaN" style="outline:none;" target="_self"     />
<area id="bot3" alt="" title="" href="#" shape="rect" coords="0,190,208,365" style="outline:none;" target="_self"     />
<area id="bot4" alt="" title="" href="#" shape="rect" coords="235,196,445,365" style="outline:none;" target="_self"     />
<area id="bot5" alt="" title="" href="#" shape="rect" coords="470,197,680,365" style="outline:none;" target="_self"     />
<area shape="rect" coords="678,363,680,365" alt="Image Map" style="outline:none;" title="Image Map" href="http://www.image-maps.com/index.php?aff=mapped_users_0" />
</map>
```

tidied up:

```html
<img id="palette" src="intro1-palette.png" border="0" width="680" height="365" orgWidth="680" orgHeight="365" usemap="#image-map" alt="" />
<map name="#image-map" id="#image-map">
<area id="bot0" alt="" title="" href="#" shape="rect" coords="0,0,207,170" style="outline:none;" target="_self" />
<area id="bot1" alt="" title="" href="#" shape="rect" coords="235,2,447,172" style="outline:none;" target="_self" />
<area id="bot2" alt="" title="" href="#" shape="rect" coords="NaN,NaN,NaN,NaN" style="outline:none;" target="_self" />
<area id="bot3" alt="" title="" href="#" shape="rect" coords="1,192,NaN,NaN" style="outline:none;" target="_self" />
<area id="bot3" alt="" title="" href="#" shape="rect" coords="0,190,208,365" style="outline:none;" target="_self" />
<area id="bot4" alt="" title="" href="#" shape="rect" coords="235,196,445,365" style="outline:none;" target="_self" />
<area id="bot5" alt="" title="" href="#" shape="rect" coords="470,197,680,365" style="outline:none;" target="_self" />
<area id="xxxx" alt="" title="" href="#" shape="rect" coords="678,363,680,365" style="outline:none;"  target="_self" />
</map>
```
