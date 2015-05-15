// Interface to window related methods.

#ifndef WINDOW_ADAPTER_H_
#define WINDOW_ADAPTER_H_

#include <string>

#include "bandit/adapters/ImageAdapter.h"

class WindowAdapter
{
  public:
    WindowAdapter() : title(""), width(0), height(0) {}
    WindowAdapter(std::string title, float width, float height) :
        title(title), width(width), height(height) {}
    virtual ~WindowAdapter() {}
    

    // Creates a window where images can be rendered.
    virtual void CreateWindow() = 0;

    // Destroys a previously created window.
    virtual void DestroyWindow() = 0;

    // Renders an image in the window.
    // virtual void Render(ImageAdapter* image) = 0;

  protected:
    // Title displayed at the top of the window.
    std::string title;

    // Window width, in pixels.
    float width;

    // Window height, in pixels.
    float height;
};

#endif // WINDOW_ADAPTER_H_