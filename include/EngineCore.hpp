#pragma once

struct JFEFighter {
    float x;
    int health;
};

extern "C" {

void jfe_init_fighter(JFEFighter* fighter, float x);
void jfe_move(JFEFighter* fighter, float amount);
int jfe_attack(JFEFighter* attacker, JFEFighter* target);

}
