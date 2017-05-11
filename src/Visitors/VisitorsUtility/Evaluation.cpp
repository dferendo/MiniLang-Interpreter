//
// Created by dylan on 10/05/2017.
//
#include "../../../include/Visitors/VisitorsUtility/Evaluation.h"

void visitor::Evaluation::setStringEvaluation(const std::string &stringEvaluation) {
    lastTypeUsed = STRING;
    Evaluation::stringEvaluation = stringEvaluation;
}

void visitor::Evaluation::setRealEvaluation(double realEvaluation) {
    lastTypeUsed = REAL;
    Evaluation::realEvaluation = realEvaluation;
}

void visitor::Evaluation::setIntEvaluation(int intEvaluation) {
    lastTypeUsed = INT;
    Evaluation::intEvaluation = intEvaluation;
}

void visitor::Evaluation::setBoolEvaluation(bool boolEvaluation) {
    lastTypeUsed = BOOL;
    Evaluation::boolEvaluation = boolEvaluation;
}

const std::string &visitor::Evaluation::getStringEvaluation() const {
    return stringEvaluation;
}

double visitor::Evaluation::getRealEvaluation() const {
    return realEvaluation;
}

int visitor::Evaluation::getIntEvaluation() const {
    return intEvaluation;
}

bool visitor::Evaluation::getBoolEvaluation() const {
    return boolEvaluation;
}
