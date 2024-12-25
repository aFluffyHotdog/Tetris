//
// Created by Thitwut Pattanasuttinont on 2024-12-20.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <raylib.h>
#include <string>


class Button {
    public:
        Button(float x, float y, const std::string buttonText, bool selected);
        /// Draws the button on the screen
        void Draw() const;
        /// Returns true if button is being selected
        bool getSelected() const;
        void setSelected(bool selected);

    private:
        Rectangle rect{};
        Color color{};
        std::string text;
        bool isSelected;

};



#endif //BUTTON_H
