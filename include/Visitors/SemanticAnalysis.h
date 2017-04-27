//
// Created by dylan on 25/04/2017.
//

#ifndef COMPILERTHEORY_SEMANTICANALYSIS_H
#define COMPILERTHEORY_SEMANTICANALYSIS_H

#include <stack>
#include "Visitor.h"
#include "Scope.h"

namespace visitor {

    class SemanticAnalysis : public Visitor {
    private:
        typedef struct ReturnCheckForFunctionDeclaration {
            bool isReturnFound;
            lexer::TOKEN functionReturnType;
        } ReturnCheckForFunctionDeclaration;

        std::stack<Scope *> allScopes;

        lexer::TOKEN lastToken;

        ReturnCheckForFunctionDeclaration returnCheckForFunctionDeclaration;

        void pushScope(Scope *scope);

        Scope * popScope();

        Scope * getTopScope();

        lexer::TOKEN returnTokenOfIdentifierInAllScopes(std::stack<Scope *> scopes, std::string &identifier);

        std::vector<ast::ASTFormalParam *> * returnFunctionParamsInAllScopes(std::stack<Scope *> scopes,
                                                                             std::string &identifier);

        int handleOperatorType(lexer::TOKEN lhs, lexer::TOKEN rhs, std::string binaryOperator);
    public:
        virtual void visit(ast::ASTNode *node) override;

        virtual void visit(ast::ASTVariableDeclaration *node) override;

        virtual void visit(ast::ASTAssignment *node) override;

        virtual void visit(ast::ASTPrintStatement *node) override;

        virtual void visit(ast::ASTBlock *node) override;

        virtual void visit(ast::ASTIfStatement *node) override;

        virtual void visit(ast::ASTWhileStatement *node) override;

        virtual void visit(ast::ASTReturnStatement *node) override;

        virtual void visit(ast::ASTFormalParam *node) override;

        virtual void visit(ast::ASTFunctionDeclaration *node) override;

        virtual void visit(ast::ASTBooleanLiteral *node) override;

        virtual void visit(ast::ASTIntegerLiteral *node) override;

        virtual void visit(ast::ASTRealLiteral *node) override;

        virtual void visit(ast::ASTStringLiteral *node) override;

        virtual void visit(ast::ASTIdentifier *node) override;

        virtual void visit(ast::ASTSubExpression *node) override;

        virtual void visit(ast::ASTFunctionCall *node) override;

        virtual void visit(ast::ASTUnary *node) override;

        virtual void visit(ast::ASTBinaryExprNode *node) override;
    };

}
#endif //COMPILERTHEORY_SEMANTICANALYSIS_H
