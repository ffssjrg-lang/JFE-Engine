#include "EngineCore.hpp"
#include <cstdio>

int main() {
    JFEFighter player1;
    JFEFighter player2;

    jfe_init_fighter(&player1, 0.0f);
    jfe_init_fighter(&player2, 1.0f);

    printf("JFE Fighting Engine\n");
    printf("Player 1 Health: %d\n", player1.health);
    printf("Player 2 Health: %d\n", player2.health);

    int hit = jfe_attack(&player1, &player2);

    printf("Attack: %s\n", hit ? "HIT" : "MISS");
    printf("Player 2 Health After Attack: %d\n",
           player2.health);

    return 0;
}
