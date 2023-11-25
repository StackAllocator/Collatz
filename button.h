#ifndef DATE_H
#define DATE_H
#include "raylib.h"
#include <string>
#include <tuple>
#include <iostream>


class Button
{
private:
    int m_x{};
    int m_y{};  
    int m_minWidth{};
    int m_minHeight{};
    int m_maxWidth{};
    int m_maxHeight{};
    int m_height{};
    int m_width{};
    char* m_content{};
    Color m_color{};
    Color m_hcolor{};
    void (*m_f)(void);
public:
    Button(int x, int y, int minWidth, int minHeight, int maxWidth, int maxHeight, int height, int width, char* content, Color color, void (*f)(void));
    Button(int x, int y, int height, int width, char* content, Color color, void (*f)(void));
    
    void draw();

    void checkMouse();

    void setContent(char* content);

    int getHeight() const {return m_height;}
    int getWidth() const {return m_width;}
    std::string getContent() const {return m_content;}
    getX() const {return m_x;}
    getY() const {return m_y;}
};

#endif 