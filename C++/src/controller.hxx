#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void on_frame(double time) override;
    void on_key(ge211::Key) override;
    void on_key_down(ge211::Key) override;
    void on_key_up(ge211::Key) override;
    ge211::Dims<int> initial_window_dimensions() const override;
    void draw(ge211::Sprite_set& set) override;

private:
    Model model_;
    View view_;
};
