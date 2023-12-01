#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H
#include "raylib.h"
#include <iostream>
class Coordinatesystem{
private:
    float m_ZoomX;
    float m_ZoomY;
    float m_DistanceX;
    float m_DistanceY;
    float m_OffsetX;
    float m_OffsetY;
    char* m_LabelX;
    char* m_LabelY;
    float m_width;
    float m_height;
    float m_x;
    float m_y;
    float m_paddingX;
    float m_paddingY;
public:
    Coordinatesystem();
    Coordinatesystem(Coordinatesystem& system);
    Coordinatesystem(float x = 0, float y = 0, float width = 1920, float height = 1080, float zoomX = 1, float zoomY = 1, float distanceX = 20, float distanceY = 20, float offsetX = 0, float offsetY = 0, char* labelX = "X", char* labelY = "Y", float paddingX = 30, float paddingY = 30);

    Vector2 getZoom();
    Vector2 getDistance();
    Vector2 getOffset();
    Vector2 getDimensions();
    Vector2 getPadding();
    char* getLabelX();
    char* getLabelY();
    float getX();
    float getY();
    float getX0();
    float getY0();
    void setLabelX(char* label);
    void setLabelY(char* label);
    void setOffsetX(float offset);
    void setOffsetY(float offset);
    void setWidth(float width);
    void setHeight(float height);
    void setZoomX(float zoom);
    void setZoomY(float zoom);
    void setDistanceX(float distance);
    void setDistanceY(float distance);
    void setPaddingX(float padding);
    void setPaddingY(float padding);
    void setX(float x);
    void setY(float y);

    float adjust(float val, bool x);

    void setValue(float& attribute, float value);

    void update();
    void draw(bool line = false);

};

#endif