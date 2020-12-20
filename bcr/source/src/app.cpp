#include "../include/BarChart.h"

int main(int argc, char const *argv[])
{
    Animation animation;
   
    animation.initialize(argc, argv);
   
    while(not animation.end())
    {
        animation.process_events();
        animation.update();
        animation.render();

    }
    return 0;
}
