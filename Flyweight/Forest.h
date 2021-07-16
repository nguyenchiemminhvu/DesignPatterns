#ifndef __FOREST_H__
#define __FOREST_H__

#include <vector>

#include "Tree.h"
#include "TreeType.h"
#include "TreeFactory.h"

class Forest
{
public:
    Forest(int num_row, int num_col)
    {
        m_canvas.resize(num_row);
        for (int i = 0; i < num_row; i++)
        {
            m_canvas.resize(num_col);
        }
    }

    ~Forest()
    {

    }

    void AddTree(int row, int col, std::string name, std::string color)
    {
        TreeType * type = TreeFactory::GetInstance()->GetTreeType(name, color);
        Tree t(row, col, *type);
        t.Update(&m_canvas);
    }

    void Draw()
    {
        for (int i = 0; i < m_canvas.size(); i++)
        {
            for (int j = 0; j < m_canvas[i].size(); j++)
            {
                if (m_canvas[i][j].GetName().empty())
                {
                    std::cout << "# ";
                }
                else
                {
                    std::cout << m_canvas[i][j].GetColor()[0] << " ";
                }
            }

            std::cout << std::endl;
        }
    }

private:
    std::vector<std::vector<TreeType>> m_canvas;
};

#endif // __FOREST_H__