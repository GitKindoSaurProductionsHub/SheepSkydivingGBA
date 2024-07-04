#include "background.hpp"

BackgroundObj::BackgroundObj(bn::fixed posX, bn::fixed posY) : background(bn::regular_bg_items::skybackground.create_bg(posX, posY))
{
    position.x = background.position().x();
    position.y = background.position().y();
}

BackgroundObj::~BackgroundObj()
{

}

void BackgroundObj::Update()
{
    if(!isParachuteActive)
    {
        currentScrollSpeed += scrollAccelaration;
        if(currentScrollSpeed >= maxScrollSpeed) currentScrollSpeed = maxScrollSpeed;
    }
    else
    {
        currentScrollSpeed -= scrollAccelaration;
        if(currentScrollSpeed <= maxParachuteScrollSpeed) currentScrollSpeed = maxParachuteScrollSpeed;
    }

    position.x += currentScrollSpeed;
    background.set_position(position.x, position.y);
}

void BackgroundObj::SetIsParachuteActive(bool input)
{
    if(isParachuteActive == input) return;
    isParachuteActive = input;
}

bn::fixed BackgroundObj::ReturnCurrentScrollSpeed()
{
    return currentScrollSpeed;
}