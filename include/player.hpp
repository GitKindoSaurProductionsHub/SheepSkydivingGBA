#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_keypad.h"
#include "misc.hpp"

#include "bird.hpp"

#include "bn_sprite_items_player.h"
#include "bn_sprite_items_parachute.h"

class PlayerObj
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

    struct MinMaxFlyHeight
    {
        bn::fixed min = 0;
        bn::fixed max = 0;
    } minMaxFlyHeight;

    bn::sprite_ptr sheepSprite;
    bn::sprite_ptr parachuteSprite;
    
    bn::fixed currentFallSpeed = 0;
    bn::fixed fallAccelaration = 0.05f;
    bn::fixed maxFallSpeed = 3.0f;
    
    bn::fixed maxParachuteSpeed = 1;
    
    bn::fixed maxDriftSpeed = 1.5f;
    
    bn::fixed topScreenOffset = 30;

    bool parachuteActive = false;
    bool isPlayerAlive = true;

    void SetupMinMaxFlyHeight();
    void SetupSizeDimensions();

public:
    PlayerObj();
    ~PlayerObj();
    void Update();

    bool ReturnParachuteActive();
    bool IsColliding(BirdObj &bird);
    bool ReturnIsPlayerAlive();

    MinMaxFlyHeight ReturnMinMaxFlyHeight();
    Position ReturnPosition();
    Size ReturnSize();
};

#endif // PLAYER_HPP