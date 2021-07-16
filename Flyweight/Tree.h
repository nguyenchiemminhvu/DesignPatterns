#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>

#include "TreeType.h"

class Tree
{
public:
    Tree(int row, int col, TreeType type)
        : m_row(row), m_col(col), m_type(type)
    {

    }

    ~Tree()
    {

    }

    void Update(std::vector<std::vector<TreeType>> *canvas)
    {
        if (m_row < 0 || m_row >= (*canvas).size() || m_col < 0 || m_col >= (*canvas)[m_row].size())
        {
            std::cout << "Can not plant this tree at position: " << m_row << " " << m_col << std::endl;
            return;
        }
        (*canvas)[m_row][m_col] = m_type;
    }

private:
    int m_row;
    int m_col;
    TreeType m_type;
};

#endif // __TREE_H__