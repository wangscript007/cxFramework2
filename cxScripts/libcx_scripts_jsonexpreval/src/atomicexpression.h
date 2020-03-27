#ifndef ATOMICEXPRESSION_H
#define ATOMICEXPRESSION_H

#include <string>
#include <json/json.h>
#include <vector>

#include "atomicexpressionside.h"

enum eEvalOperator {
    EVAL_OPERATOR_CONTAIN, // operator for multi items..
    EVAL_OPERATOR_CONTAIN_ICASE, // operator for multi items..
    EVAL_OPERATOR_REGEX,
    EVAL_OPERATOR_EQUAL,
    EVAL_OPERATOR_EQUAL_ICASE,
    EVAL_OPERATOR_STARTSWITH,
    EVAL_OPERATOR_STARTSWITH_ICASE,
    EVAL_OPERATOR_UNDEFINED
};

class AtomicExpression
{
public:
    AtomicExpression(std::vector<std::string> *staticTexts );

    bool compile( std::string expr );
    bool evaluate(const Json::Value & values);

    void setStaticTexts(std::vector<std::string> *value);

private:
    bool calcNegative(bool r);
    bool substractExpressions(const std::string &regex);

    std::vector<std::string> *staticTexts;
    std::string expr;
    AtomicExpressionSide left,right;
    eEvalOperator evalOperator;
    bool negativeExpression;

};

#endif // ATOMICEXPRESSION_H