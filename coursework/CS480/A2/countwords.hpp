
#include <iostream>
#include "exec.hpp"
void *countfunct(void *argument);
void counter(struct dictNode *root,string word,int minimum);
int recurcount(struct dictNode *root);
bool search(struct dictNode *root,string searchword);