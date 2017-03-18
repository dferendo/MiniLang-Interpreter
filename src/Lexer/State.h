//
// Created by dylan on 14/03/2017.
//

#ifndef COMPILERTHEORY_STATE_H
#define COMPILERTHEORY_STATE_H

namespace lexer {

    /**
     * Shows all the states available for the machine. There are in total 22 states, including an error State.
     * TODO
     */
    enum STATE {
        S_00 = 0,
        S_01 = 1,
        S_02 = 2,
        S_03 = 3,
        S_04 = 4,
        S_05 = 5,
        S_06 = 6,
        S_07 = 7,
        S_08 = 8,
        S_09 = 9,
        S_10 = 10,
        S_11 = 11,
        S_12 = 12,
        S_13 = 13,
        S_14 = 14,
        S_15 = 15,
        S_16 = 16,
        S_17 = 17,
        S_18 = 18,
        S_19 = 19,
        S_ERR = 21,
        S_TOTAL = S_ERR + 1
    };

    /**
     * TODO:
     * @param currentState
     * @return
     */
    bool checkFinalState(STATE &currentState);
}
#endif //COMPILERTHEORY_STATE_H
