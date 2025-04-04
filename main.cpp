#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <string>

class X11Button {
    Display* display;
    Window window;
    GC gc; // Graphics context
    int button_x, button_y, button_w, button_h;
    bool button_clicked = false;

public:
    X11Button() : button_x(150), button_y(100), button_w(100), button_h(40) {
        display = XOpenDisplay(nullptr);
        if (!display) {
            std::cerr << "Cannot open X display\n";
            exit(1);
        }

        window = XCreateSimpleWindow(
            display, RootWindow(display, 0),
            0, 0, 400, 300, // x,y, width,height
            1, BlackPixel(display, 0), // border
            WhitePixel(display, 0) // background
        );

        // Set up graphics context for drawing
        gc = XCreateGC(display, window, 0, nullptr);
        XSetForeground(display, gc, BlackPixel(display, 0));

        // Listen to mouse clicks and exposure events
        XSelectInput(display, window, ExposureMask | ButtonPressMask | ButtonReleaseMask);
        XMapWindow(display, window);
    }

    void drawButton() {
        // Draw button rectangle
        XSetForeground(display, gc, button_clicked ? 0x888888 : 0xCCCCCC); // Gray color
        XFillRectangle(display, window, gc, button_x, button_y, button_w, button_h);
        
        // Draw button border
        XSetForeground(display, gc, BlackPixel(display, 0));
        XDrawRectangle(display, window, gc, button_x, button_y, button_w, button_h);
        
        // Draw button text
        std::string text = "Click Me!";
        XDrawString(display, window, gc, 
                    button_x + 20, button_y + 25, 
                    text.c_str(), text.length());
    }

    void run() {
        XEvent event;
        while (true) {
            XNextEvent(display, &event);
            switch (event.type) {
                case Expose:
                    drawButton();
                    break;
                case ButtonPress:
                    if (event.xbutton.x >= button_x && event.xbutton.x <= button_x + button_w &&
                        event.xbutton.y >= button_y && event.xbutton.y <= button_y + button_h) {
                        button_clicked = true;
                        drawButton();
                        std::cout << "Button pressed!\n";
                    }
                    break;
                case ButtonRelease:
                    if (button_clicked) {
                        button_clicked = false;
                        drawButton();
                    }
                    break;
            }
        }
    }

    ~X11Button() {
        XFreeGC(display, gc);
        XDestroyWindow(display, window);
        XCloseDisplay(display);
    }
};

int main() {
    X11Button app;
    app.run();
    return 0;
}