#include <iostream>

#include "Forest.h"

int main()
{
    Forest f(5, 5);
    f.AddTree(1, 1, "Tree 1", "RED");
    f.AddTree(3, 2, "Tree 2", "GREEN");
    
    f.Draw();

    return 0;
}