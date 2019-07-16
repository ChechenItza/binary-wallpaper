# binary-wallpaper
Qt Widgets application that takes your text, converts it to a binary representation, and puts it on an image.  

![Window](https://github.com/ChechenItza/binary-wallpaper/blob/examples/window.png)


![Window](https://github.com/ChechenItza/binary-wallpaper/blob/examples/wallpaper.png)
<i>Resultant image</i>

## Notes on usage
* Spaces are converted to binary as well. The spaces on resultant image separate letters (each letter is 8 bits long).  
* Wallpapers are saved in the current folder as "walppaper.png".  
* QImage quality is set to 89 because starting at 90 the image size increases dramatically (from 56KB to 8MB) without any noticeable visual changes.  

