# glitch.gui

glitch.gui  -v0.1.0 

![ScreenShot1](https://github.com/lostjared/glitch.gui/blob/main/images/image.jpg?raw=true "screenshot1")

This is an application that allows you to generate interesting base images to use with text 2 image ai prompts. 

How it works:

    Supply a example image or video file, start an animation press Save or the s key to save a snapshot
    use the arrow keys, s to save, d to stop/start, e to step or the GUI to move through the supplied distortion filters.

Required libraries:
   OpenCV 4, http://github.com/lostjared/libacidcam - libacidcam, Qt6

To compile download and install libacidcam

    git clone https://github.com/lostjared/libacidcam.git
    cd libacidcam
    mkdir build && cd build
    cmake ../
    make -j8 && sudo make install

enter directory of glitch.gui

    qmake6
    make -j8
    ./glitch.gui