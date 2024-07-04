#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_skybackground.h"

class BackgroundObj
{
private:
    struct Position
    {
        bn::fixed x = 0;
        bn::fixed y = 0;
    } position;

    bn::fixed currentScrollSpeed = 0.0f;
    bn::fixed scrollAccelaration = 0.05f;
    bn::fixed maxScrollSpeed = 3.0f;
    bn::fixed maxParachuteScrollSpeed = 0.5f;

    bool isParachuteActive = false;

    bn::regular_bg_ptr background;

public:
    BackgroundObj(bn::fixed posX, bn::fixed posY);
    ~BackgroundObj();

    void Update();
    void SetIsParachuteActive(bool input);

    bn::fixed ReturnCurrentScrollSpeed();
};

#endif // BACKGROUND_HPP