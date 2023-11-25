#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H
#include "raylib.h"
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

    Vector2 getZoom();
    Vector2 getDistance();
    Vector2 getOffset();
    Vector2 getDimensions();
    Vector2 getPadding();
    char* getLabelX();
    char* getLabelY();

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

    void setValue(float& attribute, float value);

    void update();
    void draw();

};

#endif