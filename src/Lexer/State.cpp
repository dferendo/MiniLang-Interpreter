//
// Created by dylan on 14/03/2017.
//

#include "State.h"

bool lexer::checkFinalState(STATE &currentState) {
    switch (currentState) {
        case S_01:
        case S_02:
        case S_03:
        case S_05:
        case S_06:
        case S_08:
        case S_09:
        case S_11:
        case S_12:
        case S_14:
        case S_15:
        case S_16:
        case S_17:
        case S_19:
            return true;
        case S_00:
        case S_04:
        case S_07:
        case S_10:
        case S_13:
        case S_18:
        case S_20:
        case S_ERR:
            return false;
    }
    return S_ERR;
}
