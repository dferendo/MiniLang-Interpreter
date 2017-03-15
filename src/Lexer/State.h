//
// Created by dylan on 14/03/2017.
//

#ifndef COMPILERTHEORY_STATE_H
#define COMPILERTHEORY_STATE_H

namespace lexer {

    /**
     * Shows all the states available for the machine.
     */
    enum STATE {
        S_00 = 0, S_01 = 1, S_02 = 2, S_ERR = 3, S_TOTAL = S_ERR
    };

    bool checkFinalState(STATE &currentState);
}
#endif //COMPILERTHEORY_STATE_H
