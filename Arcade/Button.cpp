//
// Created by Thitwut Pattanasuttinont on 2024-12-20.
//

#include "Button.h"
#include <iostream>
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 40
#define PADDING 20

Button::Button(float x, float y, std::string buttonText, const bool selected) {\
    const int textWidth = MeasureText(buttonText.c_str(), 20);
    const float buttonWidth = textWidth + (PADDING * 2.0);  // Add padding on both sides

    rect = { x - buttonWidth/2, y, buttonWidth, BUTTON_HEIGHT };  // Center at x position
    text = std::move(buttonText);
    isSelected = selected;
}


bool Button::getSelected() const {
    return isSelected;
}

void Button::setSelected(const bool selected) {
    isSelected = selected;
}

void Button::Draw() const {
    // Draw white border if selected
    if (isSelected) {
        DrawRectangleLinesEx(rect, 3, WHITE);
    }

    // Draw button text
    const char *cstr = text.c_str();
    DrawText(cstr,
            rect.x + PADDING,
            rect.y + (BUTTON_HEIGHT - PADDING)/2.0,
            20,
            WHITE);
}
