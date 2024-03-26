#include "loadingScreen/loadingScreen.h"
#include "startScreen/startScreen.h"

int main()
{
    LoadingScreen loadingScreen;
    loadingScreen.run();
    StartScreen startScreen;
    startScreen.run();
    return 0;
}

/*
#include "startScreen/startScreen.h"

int main()
{
    StartScreen startScreen;
    startScreen.run();
    return 0;
}
*/
