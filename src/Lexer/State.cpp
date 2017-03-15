//
// Created by dylan on 14/03/2017.
//

#include "State.h"

bool lexer::checkFinalState(STATE &currentState) {
    switch (currentState) {
        case S_01:
        case S_02:
            return true;
        case S_00:
        case S_ERR:
            return false;
    }
    return false;
}
