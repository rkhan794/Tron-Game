#pragma once

#include <ge211.hxx>

class Bike
{
    using Position = ge211::Posn<int>;

    using Velocity = ge211::Dims<int>;

    using Color = ge211::Color;

    using Rectangle = ge211::Rect<int>;

public:
    // The color of the bike
    Color bike_color;

    // The initial velocity of the bike, set by the constructor
    Velocity initial_velocity;

    // The hit-box of the bike (bike is a square of x by x size)
    Rectangle hitbox;

    // Center of the "bike"
    // Position center;

    // Is the bike moving (true); if in resting position, false
    bool is_live;

    // // The position of the bike
    // Position initialPosition;

    // Check if the bike is boosting
    bool is_boosting;

    int boost_multiplier;


    // Stores a vector of positions for the trail
    std::vector<Position> trails;

    // Constructor for the bike class
    Bike(Color const& color, Velocity const& initVel, Position
    initial_position);

    // bike turns upward
    void turn_up();

    // bike turns downward
    void turn_down();

    // bike turns right
    void turn_right();

    // bike turns left
    void turn_left();

    // Updates the bike's position based on velocity and updates the trail
    // vector
    void update_position(double time);

    // Sets the bike's velocity to double
    void boost();

    // Sets the bike rectangle to the
    void set_position(Position posn);

    // Creates a new bike object to calculate its next move
    Bike calc_next_move(double time);
};
