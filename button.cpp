#include "button.h"


Button::Button(int x, int y, int minWidth, int minHeight, int maxWidth, int maxHeight, int width, int height, char* content, Color color, void (*f)(void)) {
    m_x = x;
    m_y = y;
    m_minWidth = minWidth;
    m_minHeight = minHeight;
    m_maxWidth = maxWidth;
    m_maxHeight = maxHeight;
    m_width = width;
    m_height = height;
    m_content = content;
    m_color = color;
    m_hcolor = color;
    m_f = f;
}

Button::Button(int x, int y, int width, int height, char* content, Color color, void (*f)(void)) {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_content = content;
    m_color = color;
    m_hcolor = color;
    m_f = f;
}

void Button::checkMouse()  {
    Vector2 currentMousePos = {static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())};
    if (currentMousePos.x <= m_x + m_width && currentMousePos.x >= m_x && currentMousePos.y >= m_y && currentMousePos.y <= m_y + m_height) {
        m_color = Color{100, 200, 100, 255};
        draw();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            m_color = Color{80, 180, 80, 255};
            draw();
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            (*m_f)();
        }
    } else {
        m_color = Color{m_hcolor};
    }
}
    
void Button::setContent(char* content) {
    m_content = content;
}

void Button::draw() {
    Vector2 currentMousePos = {static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())};
    DrawRectangle(m_x, m_y, m_width, m_height, m_color);
    DrawText(m_content, m_x + 10, m_y + m_height/2 - 10, 20, BLACK);
}

