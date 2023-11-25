#include "Coordinatesystem.h"

Coordinatesystem::Coordinatesystem() : m_ZoomX{1}
    , m_ZoomY{1} 
    , m_DistanceX{40}
    , m_DistanceY{40}
    , m_LabelX{"x"}
    , m_LabelY{"y"}
    , m_OffsetX{0}
    , m_OffsetY{0}
    , m_width{1920}
    , m_height{1080} 
    , m_paddingX{30}
    , m_paddingY(30) 
    {}
Coordinatesystem::Coordinatesystem(Coordinatesystem& system) : 
    m_ZoomX(system.getZoom().x)
    , m_ZoomY(system.getZoom().y)
    , m_DistanceX(system.getDistance().x)
    , m_DistanceY(system.getDistance().y)
    , m_LabelX(system.getLabelX())
    , m_LabelY(system.getLabelY())
    , m_OffsetX(system.getOffset().x)
    , m_OffsetY(system.getOffset().y) 
    , m_width(system.getDimensions().x)
    , m_height(system.getDimensions().y) 
    , m_paddingX(system.getPadding().x)
    , m_paddingY(system.getPadding().y) 
    {}

Vector2 Coordinatesystem::getZoom(){
    return Vector2{m_ZoomX, m_ZoomY};
}
Vector2 Coordinatesystem::getDistance() {
    return Vector2{m_DistanceX, m_DistanceY};
}
Vector2 Coordinatesystem::getOffset() {
    return Vector2{m_OffsetX, m_OffsetY};
}
char* Coordinatesystem::getLabelX(){
    return m_LabelX;
}
char* Coordinatesystem::getLabelY(){
    return m_LabelY;
}

void Coordinatesystem::setLabelX(char* label){
    m_LabelX = label;
    update();
}
void Coordinatesystem::setLabelY(char* label){
    m_LabelY = label;
    update();
}
Vector2 Coordinatesystem::getDimensions() {
    return Vector2{m_width, m_height};
}

Vector2 Coordinatesystem::getPadding() {
    return Vector2{m_paddingX, m_paddingY};
}

void Coordinatesystem::setValue(float& attribute, float value) {
    attribute = value;
}

void Coordinatesystem::setOffsetX(float offset){
    m_OffsetX = offset;
}
void Coordinatesystem::setOffsetY(float offset) {
    m_OffsetY = offset;
}
void Coordinatesystem::setWidth(float width) {
    m_width = width;
}
void Coordinatesystem::setHeight(float height) {
    m_height = height;
}
void Coordinatesystem::setZoomX(float zoom) {
    m_ZoomX = zoom;
}
void Coordinatesystem::setZoomY(float zoom) {
    m_ZoomY = zoom;
}
void Coordinatesystem::setDistanceX(float distance) {
    m_DistanceX = distance;
}
void Coordinatesystem::setDistanceY(float distance) {
    m_DistanceY = distance;
}
void Coordinatesystem::setPaddingX(float padding) {
    m_paddingX = padding;
}
void Coordinatesystem::setPaddingY(float padding) {
    m_paddingY = padding;
}


void Coordinatesystem::update() {
    if (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_X) && !IsKeyDown(KEY_Y))
    {
        setDistanceY(m_DistanceY + 1.0f);
        if (m_DistanceY >= 80 && m_ZoomY > 1)
        {
            setDistanceY(40.0f);
            setZoomY(m_ZoomY/2);
        }

        if (m_ZoomY < 1)
        {
            m_ZoomY = 1;
            m_DistanceY = 80;
        }
    }
    else if (IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_X) && !IsKeyDown(KEY_Y))
    {
        m_DistanceY--;
        if (m_DistanceY <= 40)
        {
            m_DistanceY = 80;
            m_ZoomY *= 2;
        }
    }
    // Zoom x-direction
    if (IsKeyDown(KEY_RIGHT))
    {
        m_DistanceX++;
        if (m_DistanceX >= 80 && m_ZoomX > 1)
        {
            m_DistanceX = 40;
            m_ZoomX /= 2;
        }

        if (m_ZoomX < 1)
        {
            m_ZoomX = 1;
            m_DistanceX = 80;
        }
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        m_DistanceX--;
        if (m_DistanceX <= 40)
        {
            m_DistanceX = 80;
            m_ZoomX *= 2;
        }
    }
    // Move Graph in x-direction
    if (IsKeyDown(KEY_D))
    {
        m_OffsetX += m_ZoomX;
        
    DrawText(TextFormat("OffsetX: %i", m_OffsetX), 200, 550, 20, BLACK);
    }
    if (IsKeyDown(KEY_A))
    {
        m_OffsetX -= m_ZoomX;
        
    DrawText(TextFormat("OffsetX: %i", m_OffsetX), 200, 550, 20, BLACK);
    }
    // Move Graph in y-direction
    if (IsKeyDown(KEY_W))
    {
        m_OffsetY += m_ZoomY;
        
    DrawText(TextFormat("OffsetY: %i", m_OffsetY), 200, 600, 20, BLACK);
    }
    if (IsKeyDown(KEY_S))
    {
        m_OffsetY -= m_ZoomY;
        
    DrawText(TextFormat("OffsetY: %i", m_OffsetY), 200, 600, 20, BLACK);
    }
    // Adjust padding
    if (IsKeyDown(KEY_X) && IsKeyDown(KEY_UP))
    {
        m_paddingX += m_DistanceX;
    }
    if (IsKeyDown(KEY_X) && IsKeyDown(KEY_DOWN) && m_paddingX >= 0)
    {
        m_paddingX -= m_DistanceX;
    }
    if (IsKeyDown(KEY_Y) && IsKeyDown(KEY_UP))
    {
        m_paddingY += m_DistanceY;
    }
    if (IsKeyDown(KEY_Y) && IsKeyDown(KEY_DOWN) && m_paddingY >= 0)
    {
        m_paddingY -= m_DistanceY;
    }
    DrawText(TextFormat("paddingX: %i", m_paddingX), 500, 50, 20, BLACK);
    DrawText(TextFormat("paddingY: %i", m_paddingY), 500, 100, 20, BLACK);
    DrawText(TextFormat("x: %i", m_x), 500, 150, 20, BLACK);
    DrawText(TextFormat("y: %i", m_y), 500, 200, 20, BLACK);
    DrawText(TextFormat("distanceX: %i", m_DistanceX), 500, 250, 20, BLACK);
    DrawText(TextFormat("distanceY: %i", m_DistanceY), 500, 300, 20, BLACK);
    DrawText(TextFormat("height: %i", m_height), 500, 350, 20, BLACK);
    DrawText(TextFormat("width: %i", m_width), 500, 400, 20, BLACK);
    DrawText(TextFormat("ZoomX: %i", m_ZoomX), 500, 450, 20, BLACK);
    DrawText(TextFormat("ZoomY: %i", m_ZoomY), 500, 500, 20, BLACK);
    DrawText(TextFormat("OffsetX: %i", m_OffsetX), 500, 550, 20, BLACK);
    DrawText(TextFormat("OffsetY: %i", m_OffsetY), 500, 600, 20, BLACK);
    draw();
}
void Coordinatesystem::draw() {
    DrawText(TextFormat("paddingX: %i", m_paddingX), 900, 50, 20, BLACK);
    DrawText(TextFormat("paddingY: %i", m_paddingY), 900, 100, 20, BLACK);
    DrawText(TextFormat("x: %i", m_x), 900, 150, 20, BLACK);
    DrawText(TextFormat("y: %i", m_y), 900, 200, 20, BLACK);
    DrawText(TextFormat("distanceX: %i", m_DistanceX), 900, 250, 20, BLACK);
    DrawText(TextFormat("distanceY: %i", m_DistanceY), 900, 300, 20, BLACK);
    DrawText(TextFormat("height: %i", m_height), 900, 350, 20, BLACK);
    DrawText(TextFormat("width: %i", m_width), 900, 400, 20, BLACK);
    DrawText(TextFormat("ZoomX: %i", m_ZoomX), 900, 450, 20, BLACK);
    DrawText(TextFormat("ZoomY: %i", m_ZoomY), 900, 500, 20, BLACK);
    DrawText(TextFormat("OffsetX: %i", m_OffsetX), 900, 550, 20, BLACK);
    DrawText(TextFormat("OffsetY: %i", m_OffsetY), 900, 600, 20, BLACK);
    DrawLine(m_paddingX, m_y, m_paddingX, m_y + m_height, BLACK);
    for (int i = 0; i <= m_height - m_paddingY; i += m_DistanceY)
    {
        int n = (int)((i * m_ZoomY) / m_DistanceY) + (m_OffsetY);
        DrawText(TextFormat("%i", n), 5, m_y + m_height - m_paddingY - i, 15, BLUE);
        DrawLine(m_x + m_paddingX - 5, m_y + m_height - m_paddingY - i, m_x + m_paddingX + 5, m_y + m_height - m_paddingY - i, BLACK);
    }
    DrawLine(m_x, m_y + m_height - m_paddingY, m_x + m_width, m_y + m_height - m_paddingY, BLACK);
    for (int i = 0; i < m_x + m_width; i += m_DistanceX)
    {
        int n = (i * m_ZoomX) / m_DistanceX + (m_OffsetX);
        DrawText(TextFormat("%i", n), m_paddingX + i, m_y + m_height - m_paddingY + 10, 15, BLACK);
        DrawLine(m_x + m_paddingX + i, m_y + m_height - m_paddingY + 5, m_x + m_paddingX + i, m_y + m_height - m_paddingY - 5, BLACK);
    }
    DrawLine(m_x, (m_y + m_height - m_paddingY), m_x + m_width, m_y + m_height - m_paddingY, GREEN);
}