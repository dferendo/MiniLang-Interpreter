//
// Created by dylan on 27/03/2017.
//

#include "UnexpectedTokenWhileParsing.h"

exceptions::UnexpectedTokenWhileParsing::UnexpectedTokenWhileParsing(const std::string &reasonForError)
        : reasonForError(reasonForError) {}
