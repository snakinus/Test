#include <iostream>

#include <xge/LinuxPlatform.h>
#include <xge/Game.h>
#include <xge/util/DataBuffer.h>
#include <xge/util/Resources.h>
#include "MGame.h"

using namespace std;
using namespace xge;

int main() {
    Log::addDefaultLogger();
    Resources::assets = new FileResources("assets/");
    Resources::userData = new FileResources("data/");
    LinuxPlatform platform;
    MGame game;
    platform.startGame(game);
    return 0;
}