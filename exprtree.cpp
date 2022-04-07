//--------------------------------------------------------------------
//		Lab 12									exprtree.cpp
//
//--------------------------------------------------------------------

#include "exprtree.h"
#include <iostream>

using namespace std;
//--------------------------------------------------------------------

ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr)
{
    dataItem = elem;
    left = leftPtr;
    right = rightPtr;
}

//--------------------------------------------------------------------

ExprTree::ExprTree()
{
    root = 0;
}

ExprTree::~ExprTree()
{
    clear();
}

//--------------------------------------------------------------------

void ExprTree::build()
{
    buildSub(root);
}

void ExprTree::buildSub(ExprTreeNode*& p)
{
    char ch;

    cin >> ch;

    if (ch != '\n')
    {
        p = new ExprTreeNode(ch, NULL, NULL);

        if (!isdigit(ch))
        {
            buildSub(p->left);
            buildSub(p->right);
        }
    }
}

//--------------------------------------------------------------------

void ExprTree::expression() const
{
    exprSub(root);
}

void ExprTree::exprSub(ExprTreeNode* p) const
{
    if (p != 0)
    {
        if (!isdigit(p->dataItem)) cout << '(';
        exprSub(p->left);
        cout << p->dataItem;
        exprSub(p->right);
        if (!isdigit(p->dataItem)) cout << ')';
    }
}

//--------------------------------------------------------------------

float ExprTree::evaluate() const
{
    if (!root)
        cout << "Tree is empty." << endl;
    return evaluateSub(root);
}

float ExprTree::evaluateSub(ExprTreeNode* p) const
{
    float l, r, result;   

    if (isdigit(p->dataItem))
        result = p->dataItem - '0';      
    else
    {
        l = evaluateSub(p->left);       
        r = evaluateSub(p->right);
        switch (p->dataItem)           
        {
        case '+':  result = l + r;  break;
        case '-':  result = l - r;  break;
        case '*':  result = l * r;  break;
        case '/':  result = l / r;
        }
    }
    return result;
}

//--------------------------------------------------------------------

void ExprTree::clear()
{
    clearSub(root);
    root = 0;
}

void ExprTree::clearSub(ExprTreeNode* p)
{
    if (p != 0)
    {
        clearSub(p->left);
        clearSub(p->right);
        delete p;
    }
}

//--------------------------------------------------------------------

void ExprTree::showStructure() const
{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showSub(root, 1);
		cout << endl;
	}
}

void ExprTree::showSub(ExprTreeNode* p, int level) const
{
    int j;

    if (p != 0)
    {
        showSub(p->right, level + 1);
        for (j = 0; j < level; j++)
            cout << "\t";
        cout << " " << p->dataItem;
        if ((p->left != 0) &&
            (p->right != 0))
            cout << "<";
        else if (p->right != 0)
            cout << "/";
        else if (p->left != 0)
            cout << "\\";
        cout << endl;
        showSub(p->left, level + 1);
    }
}

//--------------------------------------------------------------------
ExprTree::ExprTree(const ExprTree& valueTree)
{
    copySub(root, valueTree.root);
}


void ExprTree::copySub(ExprTreeNode*& dest, ExprTreeNode* source)
{
    if (source == 0) { return; }
    dest = new ExprTreeNode(source->dataItem, 0, 0);
    copySub(dest->left, source->left);
    copySub(dest->right, source->right);
}