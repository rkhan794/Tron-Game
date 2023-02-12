#pragma once

#include <ge211.hxx>
#include "bike.hxx"

using String = std::string;

class Model
{
public:
    Model();

    Bike bike_orange;

    Bike bike_blue;

    // Is the game over or not
    bool game_over;

    // Who is the winner
    String winner;

    // ge211::Mixer& mixer;

    // Sets the position of the bikes
    void set_bike_positions();

    // Launches the bikes; sets their is_live bool to true
    void launch();

    // Does this thing every frame
    void on_frame(double time);

    // Resets the game
    void game_reset();
};
