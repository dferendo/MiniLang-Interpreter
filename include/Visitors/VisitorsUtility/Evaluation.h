//
// Created by dylan on 10/05/2017.
//

#ifndef COMPILERTHEORY_LASTEVALUATION_H
#define COMPILERTHEORY_LASTEVALUATION_H

#include <string>

/**
 * Macro used to determine the type of the evaluation that will be used by the template.
 */
// TODO Macros
#define TYPE(x) ((x) == (1) ? (double) : ((x) == (2) ? (int) : ((x) == (3) ? (bool) : string)))

namespace visitor {

    enum TYPE_USED {
        STRING = 0,
        REAL = 1,
        INT = 2,
        BOOL = 3
    };

    /**
     * Holds the evaluation of an expression.
     */
    class Evaluation {
    public:
        TYPE_USED lastTypeUsed;
    private:
        std::string stringEvaluation = "";

        double realEvaluation = 0;

        int intEvaluation = 0;

        bool boolEvaluation = false;
    public:
        void setStringEvaluation(const std::string &stringEvaluation);

        void setRealEvaluation(double realEvaluation);

        void setIntEvaluation(int intEvaluation);

        void setBoolEvaluation(bool boolEvaluation);

        const std::string &getStringEvaluation() const;

        double getRealEvaluation() const;

        int getIntEvaluation() const;

        bool getBoolEvaluation() const;

        virtual ~Evaluation();
    };
}
#endif //COMPILERTHEORY_LASTEVALUATION_H
