#include "view.hxx"
#include "model.hxx"

using Color = ge211::Color;
//using Sprite_set = ge211::Sprite_set;

View::View(Model const& model)
        : model_(model),
          board_sprite_(Dimensions{74, 74},
                        Color(0,2,39)),
          orange_player_sprite_(Dimensions{5,5},model_.bike_orange.bike_color),
          blue_player_sprite_(Dimensions{5,5}, model_.bike_blue.bike_color)

{ }

View::Dimensions
View::initial_window_dimensions() const
{
    return Dimensions(800,800);
}

void
View::draw(ge211::Sprite_set& set)
{
    for(int i = 0; i < 800; i = i + 80)
    {
        for(int j = 0; j < 800; j = j + 80)
        {
            set.add_sprite(board_sprite_, Position{i+3,j+3},0);
        }
    }
    if(model_.bike_blue.is_live || !model_.game_over){
        set.add_sprite(blue_player_sprite_, model_.bike_blue.hitbox.top_left());
        for (auto pos : model_.bike_blue.trails) {
            set.add_sprite(blue_player_sprite_, pos.up_left_by(Dimensions{2,2}),
                           1);
        }
    }

    if(model_.bike_orange.is_live || !model_.game_over){
        set.add_sprite(orange_player_sprite_, model_.bike_orange.hitbox.top_left());
        for (auto pos : model_.bike_orange.trails) {
            set.add_sprite(orange_player_sprite_, pos.up_left_by(Dimensions{2,2}),
                           1);
        }
    }
}
