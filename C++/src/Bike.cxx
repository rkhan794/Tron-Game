#include "Bike.hxx"
#include <math.h>
using namespace ge211;



Bike::Bike(Color const& color, Velocity const& initVel, Position
initial_position)
        : bike_color(color),
          initial_velocity(initVel),
          hitbox(initial_position.x, initial_position.y,5,5),
          is_live(false),
          // initialPosition(0,0),
          is_boosting(false),
          boost_multiplier(1),
          trails()

{}

void
Bike::turn_up()
{

    if(initial_velocity.height == 0){
        initial_velocity.height = -abs(initial_velocity.width);
        initial_velocity.width = 0;
    }

}

void
Bike::turn_down()
{
    if(initial_velocity.height == 0){
        initial_velocity.height = abs(initial_velocity.width);
        initial_velocity.width = 0;
    }
}

void
Bike::turn_right()
{
    if(initial_velocity.width == 0){
        initial_velocity.width = abs(initial_velocity.height);
        initial_velocity.height = 0;
    }
}

void
Bike::turn_left()
{
    if(initial_velocity.width == 0){
        initial_velocity.width = -abs(initial_velocity.height);
        initial_velocity.height = 0;
    }
}

void
Bike::update_position(double time)
{
    Position prev_posn = hitbox.center();

    hitbox.x += (int)round((initial_velocity.width) * time *
            boost_multiplier);
    hitbox.y += (int)round((initial_velocity.height) * time *
                           boost_multiplier);

    trails.push_back(prev_posn);


    // Calculating trails for pos.x
    int increment_i;
    if(initial_velocity.width > 0) {
        increment_i = 1;
    }
    else {
        increment_i = -1;
    }
    for(int i = prev_posn.x; i != hitbox.center().x; i = i + increment_i) {
        if (i != hitbox.center().x) {
            Position missing_position = {i, hitbox.center().y};
            trails.push_back(missing_position);
        }
    }

    // Calculating trails for pos.y
    int increment_j;
    if(initial_velocity.height > 0) {
        increment_j = 1;
    }
    else {
        increment_j = -1;
    }
    for(int j = prev_posn.y; j != hitbox.center().y; j = j + increment_j){
        if(j != hitbox.center().y){
            Position missing_position = {hitbox.center().x,j};
            trails.push_back(missing_position);
        }
    }
}

void
Bike::boost()
{
    if(is_boosting)
    {
        boost_multiplier = 3;
    }
    else
    {
        boost_multiplier = 1;
    }
}

void
Bike::set_position(Position posn)
{
    hitbox.x = posn.x - hitbox.width/2;
    hitbox.y = posn.y - hitbox.height/2;
}

Bike
Bike::calc_next_move(double time)
{
    Bike result(*this);

    result.hitbox.x += (int)round((initial_velocity.width) * time *
            boost_multiplier);

    result.hitbox.y += (int)round((initial_velocity.height) * time *
            boost_multiplier);

    return result;
}



