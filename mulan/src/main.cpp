#include <sgg/graphics.h>
#include <sgg/audio.h>
#include <mulan/game.hpp>
#include <memory>
#include <mulan/defines.hpp>

std::unique_ptr<game> game_ptr = nullptr;

void draw()
{
    (*game_ptr).draw();
}

void update(float ms)
{
    game_ptr->update(ms);
}
struct graphics_exitor : public exitor  {
	void exit() override {graphics::stopMessageLoop();}
};

int main(int argc, char** argv)
{
	graphics::createWindow(1200, 800, "Mulan V0.1");
        graphics::preloadBitmaps(ASSETS_PATH);

        initAudio();

	game_ptr = std::make_unique<game>(std::make_unique< graphics_exitor>()); 

	graphics::setCanvasSize(28, 16);  
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::startMessageLoop(); 


        endAudio();

	return 0;

}
