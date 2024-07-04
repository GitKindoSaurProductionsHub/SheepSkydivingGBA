#ifndef BIRD_HPP
#define BIRD_HPP

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_bird.h"
#include "misc.hpp"

class BirdObj
{
private:
    struct Position
    {
        bn::fixed x = 0;
        bn::fixed y = 0;
    } position;

    struct Size
    {
        bn::fixed width = 16;
        bn::fixed height = 16;
        bn::fixed halfWidth = 8;
        bn::fixed halfHeight = 8;
    } size;

    struct Collider
    {
        bn::fixed x = 0;
        bn::fixed y = 0;
        bn::fixed width = 10;
        bn::fixed height = 10;
    } collider;

    struct MinMaxFlySpeed
    {
        bn::fixed min = 0.5f;
        bn::fixed max = 2.0f;
    } minMaxFlySpeed;

    struct MinMaxFlyHeight
    {
        bn::fixed min = 0;
        bn::fixed max = 0;
    } minMaxFlyHeight;

    bool comeFromLeft = true;
    bn::fixed topScreenOffset = 30;
    bn::fixed flySpeed = 0.5f;

    bn::sprite_ptr sprite;
    bn::sprite_animate_action<2> spriteAnimation;
    
    void SetupMinMaxFlyHeight();
    void SetupSizeDimensions();
    
public:
    BirdObj();
    ~BirdObj();
    
    void Update();
    void Respawn(int randomDirection, bn::fixed randomPosition, bn::fixed randomFlySpeed);
    
    Position ReturnPosition();
    Size ReturnSize();
    Collider ReturnCollider();
    MinMaxFlySpeed ReturnMinMaxFlySpeed();
    MinMaxFlyHeight ReturnMinMaxFlyHeight();
};

#endif // BIRD_HPP