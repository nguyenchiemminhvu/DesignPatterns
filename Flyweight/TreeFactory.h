#ifndef __TREE_FACTORY_H__
#define __TREE_FACTORY_H__

#include <vector>
#include "singleton.h"
#include "TreeType.h"

class TreeFactory : public Singleton<TreeFactory>
{
public:
    static TreeType * GetTreeType(std::string name, std::string color)
    {
        TreeType * type = nullptr;

        for (int i = 0; i < m_types.size(); i++)
        {
            if (m_types[i].GetName() == name && m_types[i].GetColor() == color)
            {
                type = &m_types[i];
            }
        }

        if (type == nullptr)
        {
            m_types.push_back(TreeType(name, color));
            type = &m_types[m_types.size() - 1];
        }

        return type; 
    }

private:
    static std::vector<TreeType> m_types;
};

std::vector<TreeType> TreeFactory::m_types;

#endif // __TREE_FACTORY_H__