#pragma once

#include "model.hxx"

class View
{
public:

    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Rectangle = ge211::Rect<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;

    bool delete_sprite;



private:
    Model const& model_;
    ge211::Rectangle_sprite const board_sprite_;
    ge211::Rectangle_sprite const orange_player_sprite_;
    ge211::Rectangle_sprite const blue_player_sprite_;

};
