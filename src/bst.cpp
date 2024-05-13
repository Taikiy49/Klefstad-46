#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"
#include "timer.h"
#include "avltree.h"
#include "bstree.h"

using namespace std;

void BST::pre_order_print(ostream & out, Node * t){}
void BST::in_order_print(ostream & out, Node * t){}
void BST::post_order_print(ostream & out, Node * t){}

ostream & operator<<(ostream & out, BST & L){}
BST::~BST(){
    free_tree(root);
}

void BST::free_tree(Node * t){}

void error(string word, string msg){}
void insert_all_words(int k, string file_name, BST & L){}
void find_all_words(int k, string file_name, BST & L){}
void remove_all_words(int k, string file_name, BST & L){}
void measure_BST(string file_name, BST & L){}
void measure_BSTs(string input_file){}
