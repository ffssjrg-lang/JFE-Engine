#include "EngineCore.hpp"
#include <cmath>

extern "C" {

void jfe_init_fighter(JFEFighter* fighter, float x) {
    fighter->x = x;
    fighter->health = 100;
}

void jfe_move(JFEFighter* fighter, float amount) {
    fighter->x += amount;
}

int jfe_attack(JFEFighter* attacker, JFEFighter* target) {
    if (attacker->health <= 0 || target->health <= 0)
        return 0;

    float distance = std::abs(attacker->x - target->x);

    if (distance <= 1.5f) {
        target->health -= 10;

        if (target->health < 0)
            target->health = 0;

        return 1;
    }

    return 0;
}

}
