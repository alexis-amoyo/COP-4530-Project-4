#ifndef BET_H
#define BET_H

#include <iostream>
#include <initializer_list>
#include <utility>
#include <stack>
#include <string>
#include <sstream>

#include "token.h"
#include "opnum.h"

using namespace std;

template <typename Token>
class BET{
    private:
        struct BinaryNode{
	        Token        element;
            BinaryNode   *left;
            BinaryNode   *right;

	        BinaryNode( const Token & e = Token{ }, BinaryNode * l = nullptr, BinaryNode * r = nullptr ) : element{ e }, left{ l }, right{ r } { }
	    };

    public:
        explicit BET();
        BET(const list<Token> & postfix);
        ~BET();
        BET(const BET&);
        const BET& operator=(const BET&);
        bool buildFromPostfix(const list<Token> & postfix);

        //recursive functions w/ priv helper
        void printInfixExpression();
        void printPostfixExpression();
        bool empty();
        int depth();
        int breadth();
        int leaves();
        size_t size();

        //personal helper functions for postfix
        int precedence(string);
        bool isOperator(string);
        int max(int, int);

    private:
        //Functions
        void printInfixExpression(BinaryNode *n);
        void makeEmpty(BinaryNode* &t);
        BinaryNode * clone(BinaryNode *t);
        void printPostfixExpression(BinaryNode *n);
        size_t size(BinaryNode *t);
        int leaves(BinaryNode *t);
        int depth(BinaryNode *t);
        int breadth(BinaryNode *t);
        int getLevelBreadth(BinaryNode *t, int);
        void init();

        //Priv Variables
	    BinaryNode *root;
};
    
#include "bet.hpp"
#endif
