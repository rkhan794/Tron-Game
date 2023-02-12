#include "controller.hxx"
#include "model.hxx"

Controller::Controller()
        : view_(model_)
{ }

void
Controller::on_key_up(ge211::Key key)
{
    if (key == ge211::Key::code('h'))
    {
        model_.bike_blue.is_boosting = false;
        model_.bike_blue.boost();
    }
    if (key == ge211::Key::code('f'))
    {
        model_.bike_orange.is_boosting = false;
        model_.bike_orange.boost();
    }
}

void
Controller::on_key_down(ge211::Key key)
{
    if (key == ge211::Key::code('h'))
    {
        model_.bike_blue.is_boosting = true;
        model_.bike_blue.boost();
    }
    if (key == ge211::Key::code('f'))
    {
        model_.bike_orange.is_boosting = true;
        model_.bike_orange.boost();
    }
}

void
Controller::on_key(ge211::Key key)
{
    // Quit
    if (key == ge211::Key::code('q'))
    {
        quit();
    }

    // Launch game
    if (key == ge211::Key::code(' '))
    {
        model_.launch();
    }

    if (key == ge211::Key::code('r'))
    {
        model_.game_reset();
    }

    if(key == ge211::Key::code('w'))
    {
        model_.bike_orange.turn_up();
    }

    if(key == ge211::Key::code('a'))
    {
        model_.bike_orange.turn_left();
    }

    if(key == ge211::Key::code('s'))
    {
        model_.bike_orange.turn_down();
    }

    if(key == ge211::Key::code('d'))
    {
        model_.bike_orange.turn_right();
    }

    if(key == ge211::Key::code('i'))
    {
        model_.bike_blue.turn_up();
    }

    if(key == ge211::Key::code('j'))
    {
        model_.bike_blue.turn_left();
    }

    if(key == ge211::Key::code('k'))
    {
        model_.bike_blue.turn_down();
    }

    if(key == ge211::Key::code('l'))
    {
        model_.bike_blue.turn_right();
    }
}

void
Controller::on_frame(double time)
{
    model_.on_frame(time);
}


ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}


void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}
