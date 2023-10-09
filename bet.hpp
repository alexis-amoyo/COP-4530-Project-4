//#include "bet.h"

//Default constructor
template<typename Token>
BET<Token>::BET(){
    init();
}

//Postfix Constructor
template<typename Token>
BET<Token>::BET(const list<Token> & postfix){
    root = new BinaryNode;
    buildFromPostfix(postfix);  //send here since it utilizes the same functions
}

//Destructor - call makeEmpty priv member function
template<typename Token>
BET<Token>::~BET(){
    //cout << "Terminating one postfix expression ..." << endl;
    makeEmpty(root);  //calls private member function
    //delete root;
    //delete leftChild;
    //delete rightChild;
}

//Copy Constructor
template<typename Token>
BET<Token>::BET(const BET& rhs){
    root = clone(rhs.root);
}

//Copy assignment operator
template<typename Token>
const BET<Token>& BET<Token>::operator=(const BET& rhs){
    root = clone(rhs.root);
    return *this;
}

//Build postfix expression from list
//Errors to check: unpaired opcode and operator w/ only one operand
template<typename Token>
bool BET<Token>::buildFromPostfix(const list<Token> & postfix){
    if(root != nullptr){
        makeEmpty(root);
    }
    if(postfix.empty() == true){
        return false;
    }

    stack<BinaryNode*> s;   //typename BinaryNode* since pushing it into stack

    for(const auto &itr : postfix){
        //build postfix expression

        /*
        if(token is operand){
            create new node w/ operand
            push new node into stack
        }
        if(token is operator){
            pop corresponding operands from stack
            create a new node w/ operator (+ operands as l/r children)
            push new node into stack 
        }
        if s.top is final tree return true
        */
       if(!isOperator(itr.getValue())){  //no parentheses to account for lol
            //cout << "squirtle\n";
            //cout << itr.getValue() << endl;
            BinaryNode *node = new BinaryNode(itr);
	    s.push(node);
       }
       else{
            //cout <<  "bulbasaur\n";

            //cout << itr.getValue() << endl;
            //cout << s.top() << endl;
            if(s.empty()){
		BinaryNode *node = new BinaryNode(itr);
            	s.push(node);
	    }
	    else{ 
            	BinaryNode *node = new BinaryNode(itr);
	    	BinaryNode *nodeR = s.top();
            	s.pop();
		//cout << s.empty() << endl;
            	if(s.empty()){
                	//operator w/ only one opcode
                	cout << "Error: Operator [" << itr.getValue() << "] has only one operand: ";
			cout << nodeR->element << endl;
                	return false;
            	}
            	//cout << "charmander\n";
            	BinaryNode *nodeL = s.top();
            	s.pop();
            	//cout << "pidgeot\n";
	
            	node->right = nodeR;
            	node->left = nodeL;
            	s.push(node);
            	//cout << "flygon\n";
            }
        }
    }

        root = s.top();
	s.pop();

        if(!s.empty()){
            //must return final tree at end; if empty no good
            cout << "Unpaired opcode: " << s.top()->element << endl;
            return false;
        }
    //cout << root->element << endl;
    return true;
}

//Print infix w/ priv function
template<typename Token>
void BET<Token>::printInfixExpression(){
    if(empty()){
        cout << "Empty tree" << endl;
    }
    else{
        printInfixExpression(root);
    }
    cout << endl;
}

//print postfix w/ priv function
template<typename Token>
void BET<Token>::printPostfixExpression(){
    if(empty()){
        cout << "Empty tree" << endl;
    }
    else{
        printPostfixExpression(root);
        cout << endl;
    }
    //cout << root->element << endl;
}

//check if empty
template<typename Token>
bool BET<Token>::empty(){
    return (root == nullptr);
}

//return depth w/ priv function
template<typename Token>
int BET<Token>::depth(){
    if(root == nullptr){
        //cout << "porygon\n";
        return -1;
    }
    else if(root->left == nullptr && root->right == nullptr){
        //cout << "corsola\n";
        return 0;
    }
    else{
        //cout << "sprigatito\n";
        return depth(root);
    }
}

//return breadth w/ priv function
template<typename Token>
int BET<Token>::breadth(){
    if(root == nullptr){
        //cout << "hi\n";
        return 0;
    }
    else if(root->left == nullptr && root->right == nullptr){
        return 1;
    }
    else{
        //cout << root->element.getValue() << endl;
        //cout << root->left->element.getValue() << endl;
        //cout << root->right->element.getValue() << endl;
        return breadth(root);
    }
}

//return leaves w/ priv function
template<typename Token>
int BET<Token>::leaves(){
    if(root == nullptr){
        return 0;
    }
    else{
        return leaves(root);
    }
}

//return number of nodes in tree with priv function
template<typename Token>
size_t BET<Token>::size(){
    if(root == nullptr){
        return 0;
    }
    else{
        return size(root);
    }
}

template<typename Token>
void BET<Token>::printInfixExpression(BinaryNode *n){
    //in order traversal
    //bool first = true;
    //bool last = true;
    bool parentheses = false;
    if(n != nullptr){
        //figure out parentheses?
        /*if(n->left == nullptr && n->right == nullptr){
		cout << n->element.getValue() << " ";
	}*/
	/*else if(n->left->left == nullptr && n->right->right == nullptr
		&& n->left->right == nullptr && n->right->left == nullptr){
		printInfixExpression(n->left);
		cout << n->element.getValue() << " ";
		printInfixExpression(n->right);
	}*/
	//else{
		if(isOperator(n->element.getValue()) && isOperator(n->left->element.getValue())){
			if(precedence(n->element.getValue()) > precedence(n->left->element.getValue())){
				cout << " ( ";
				parentheses = true;
			}
		}
		//cout << "\nEx: " << n->element.getValue() << " ";
        	printInfixExpression(n->left);
			
		if(parentheses){
                        cout << ") ";
                        parentheses = false;
                }

        	//cout << n->element.getValue() << " ";

		if(isOperator(n->element.getValue()) && isOperator(n->right->element.getValue())){
                        if(precedence(n->element.getValue()) >= precedence(n->right->element.getValue())){
                                cout << n->element.getValue() <<  " ( ";
                                parentheses = true;
			}
                }
		else{
			cout << n->element.getValue() << " ";
		}
		//cout << "\nEx: " << n->element.getValue() << " ";
		printInfixExpression(n->right);
		
		if(parentheses){
                        cout << ") ";
                        parentheses = false;
                }
	//}
    }    
}

//used for destructor
template<typename Token>
void BET<Token>::makeEmpty(BinaryNode* &t){
    if(t != nullptr){
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
        t = nullptr;
}

template<typename Token>
typename BET<Token>::BinaryNode * BET<Token>::clone(BinaryNode *t){
    if(t == nullptr){
        return nullptr;
    }
    else{
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
    }            
}

template<typename Token>
void BET<Token>::printPostfixExpression(BinaryNode *n){
    //post order traversal
    if(n != nullptr){
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << n->element.getValue() << " ";
    }
}

template<typename Token>
size_t BET<Token>::size(BinaryNode *t){
    if(t->left == nullptr && t->right == nullptr){
        return 1;
    }
    else{
        return (size(t->left) + size(t->right) + 1);
    }
}

template<typename Token>
int BET<Token>::leaves(BinaryNode *t){  //check to make sure it counts all leaves and does not recursion out of existence
    if(t->left == nullptr && t->right == nullptr){
        return 1;
    }
    else{
        return (leaves(t->left) + leaves(t->right));
    }
}

template<typename Token>
int BET<Token>::depth(BinaryNode *t){
    //maybe to do with 2^H <= n < 2^H+1 - 1
    if(t == nullptr){
        //cout << "uhhhh\n";
        return -1;
    }
    //cout << "oshawott\n";
    //cout << t->element.getValue() << endl;
    int leftTree = depth(t->left);
    //cout << leftTree << endl;
    //cout << "piplup\n";
    int rightTree = depth(t->right);
    //cout << rightTree << endl;
    //cout << max(leftTree, rightTree) << endl;
    return max(leftTree, rightTree) + 1;
}

template<typename Token>
int BET<Token>::max(int left, int right){
    if(left > right){
        //cout << left << endl;
        return left;
    }
    else{
        //cout << right << endl;
        return right;
    }
}

template<typename Token>
int BET<Token>::breadth(BinaryNode *t){
    //level order traversal, does not have to be recursive
    //implement reg get breadth with this breadth?

    int maxLevel = 0;
    int breadthEx = 0;
    int height = depth(t) + 1;
    //cout << "Uh\n";
    for(int level = 1; level <= height; level++){
        //cout << "hi\n";
        breadthEx = getLevelBreadth(t, level);
        //cout << breadthEx << endl;
        //cout << "oh\n";
        //cout << breadthEx << endl;
        if(breadthEx > maxLevel){
            //cout << "oof\n";
            maxLevel = breadthEx;
        }
    }
    //cout << "ouch\n";
    return maxLevel;
}

template<typename Token>
int BET<Token>::getLevelBreadth(BinaryNode *t, int level){
    if(t == nullptr){
        return 0;
    }
    else if(level == 1){
        return 1;
    }
    else if(level > 1){
        //cout << "Left: " << getLevelBreadth(t->left, level-1) << endl;
        //cout << "Right: " << getLevelBreadth(t->right, level-1) << endl;
        return getLevelBreadth(t->left, level-1) + getLevelBreadth(t->right, level-1);
    }
}

template<typename Token>
void BET<Token>::init(){
    root = new BinaryNode;
    //root->left = nullptr;
    //root->right = nullptr;
}

template<typename Token>
bool BET<Token>::isOperator(string val){
    if(val == "*" || val == "/" || val == "+" || val == "-"){
        return true;
    }
    return false;
}

template<typename Token>
int BET<Token>::precedence(string val){
    if(val == "/" || val == "*"){
        return 100;
    }
    else if(val == "+" || val == "-"){
        return 1;
    }
}
