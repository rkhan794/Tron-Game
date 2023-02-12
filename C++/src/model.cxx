#include "model.hxx"
#include "ge211_audio.hxx"

using Position = ge211::Posn<int>;


Model::Model()
        : bike_blue(ge211::Color(72, 210, 230), {0, 100}, {400, 40}),
          bike_orange(ge211::Color(253, 108, 0), {0, -100}, {400, 760}),
          game_over(false),
          winner("None")
          // mixer(mixer)
{}

void
Model::set_bike_positions()
{
    bike_blue.set_position(bike_blue.hitbox.center());
    bike_orange.set_position(bike_orange.hitbox.center());
}


void
Model::launch()
{
    // ge211::Music_track("resources/Tron_Light_Bikes_video_game_soundtr_"
                        //"(getmp3.pro).mp3", mixer);

    if(!game_over){
        bike_blue.is_live = true;
        bike_orange.is_live = true;
    }

}

void
Model::on_frame(double time)
{
    set_bike_positions();

    Position bb_center = bike_blue.hitbox.center();
    Position bo_center = bike_orange.hitbox.center();

    if(!bike_blue.is_live || !bike_orange.is_live){
        return;
    }

    // Check for blue bike edge collisions
    if(bb_center.x > 800 || bb_center.x < 0 || bb_center.y > 800 || bb_center
    .y < 0){
        bike_blue.is_live = false;
        // ge211::audio::Sound_effect("resources/07 - Sounds (Throw Disk).mp3",
                                   //mixer);
        game_over = true;
    }

    // Check for orange bike edge collisions
    if(bo_center.x > 800 || bo_center.x < 0 || bo_center.y > 800 || bo_center
    .y < 0){
        bike_orange.is_live = false;
        // ge211::audio::Sound_effect("resources/07 - Sounds (Throw Disk).mp3",
                                  // mixer);
        game_over = true;
    }

    // Check for blue bike trail collisions
    for(Position posn : bike_blue.trails){
        if (bb_center == posn){
            bike_blue.is_live = false;
            // ge211::audio::Sound_effect("resources/07 - Sounds (Throw Disk)"
                                       //".mp3", mixer);
            game_over = true;
            winner = "Orange";
        }
        else if (bo_center  == posn){
            bike_orange.is_live = false;
            // ge211::audio::Sound_effect("resources/07 - Sounds (Throw Disk)"
                                       //".mp3", mixer);
            game_over = true;
            winner = "Blue";
        }
    }

    // Check for orange bike trail collisions
    for(Position posn : bike_orange.trails){
        if (bb_center == posn){
            bike_blue.is_live = false;
            // ge211::audio::Sound_effect("resources/07 - Sounds (Throw Disk)"
                                       //".mp3", mixer);
            game_over = true;
            winner = "Orange";
        }
        else if (bo_center  == posn){
            bike_orange.is_live = false;
            // ge211::audio::Sound_effect("resources/07 - Sounds (Throw Disk)"
            //                            ".mp3", mixer);
            game_over = true;
            winner = "Blue";
        }
    }


    // Double checking to make sure that we don't jump over from position to
    // position
    int bb_trail_size = bike_blue.trails.size();
    int bo_trail_size = bike_orange.trails.size();

    int bb_boost_val = bike_blue.boost_multiplier;
    int bo_boost_val = bike_orange.boost_multiplier;

    int counter_b = 0;

    if(bb_trail_size > bb_boost_val + 5){
        counter_b = bb_trail_size - (bb_boost_val + 5);
    }

    int counter_o = 0;

    if(bo_trail_size > bo_boost_val + 5){
        counter_o = bo_trail_size - (bo_boost_val + 5);
    }

    // Blue crashes into orange trail
    for(int i = counter_b; i < bb_trail_size; i++){
        for(Position posn : bike_orange.trails){
            if (posn == bike_blue.trails[i]){
                bike_blue.is_live = false;
                // ge211::audio::Sound_effect("resources/07 - Sounds (Throw "
                //                            "Disk).mp3", mixer);
                game_over = true;
                winner = "Orange";
            }
        }
    }

    for(int i = counter_o; i < bo_trail_size; i++){
        for(Position posn : bike_blue.trails){
            if (posn == bike_orange.trails[i]){
                bike_orange.is_live = false;
                // ge211::audio::Sound_effect("resources/07 - Sounds (Throw "
                //                            "Disk).mp3", mixer);
                game_over = true;
                winner = "Blue";
            }
        }
    }

    Bike bb_future = bike_blue.calc_next_move(time);
    Bike bo_future = bike_orange.calc_next_move(time);

    for(Position pos : bike_blue.trails){
        if(bb_future.hitbox.center() == pos){
            bike_blue.is_live = false;
            game_over = true;
            winner = "Orange";
        }
    }

    bike_blue.update_position(time);
    bike_orange.update_position(time);
}

void
Model::game_reset()
{
    if(bike_blue.is_live && bike_orange.is_live){
        return;
    }
    Position bb_init_posn = {400, 40};
    Position bo_init_posn = {400, 760};

    bike_blue.set_position(bb_init_posn);
    bike_orange.set_position(bo_init_posn);

    bike_blue.initial_velocity = {0, 100};
    bike_orange.initial_velocity = {0, -100};

    bike_blue.trails.clear();
    bike_orange.trails.clear();

    game_over = false;
}