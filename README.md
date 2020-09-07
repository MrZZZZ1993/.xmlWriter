# .xmlWriter

When I want to load resources, such as pictures, from .xml files, it is inconvenient to write paths of images to .xml files.
So I write a little tool to automatically write all those paths to .xml files and all I need to do is to select images that I want to load.

I have three types of images: single image(I just show them and don't need to process them), single image with multiple frames(there are many frames in one image, so I
can use the image to play an animation) and multiple images(a set of pictures that each one represents a frame, I need to use all of them to play an animation).

How to use:
select one type that you want to load and click Add button. Then the program will jump to the corresponding interface.
When you finish adding, you could click Export button to generate a .xml file. You also could load a .xml file via "Import" button.
