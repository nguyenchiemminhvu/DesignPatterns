#ifndef __TREE_TYPE_H__
#define __TREE_TYPE_H__

#include <string>

class TreeType
{
public:
    TreeType()
        : m_name(""), m_color("")
    {

    }

    TreeType(std::string name, std::string color)
        : m_name(name), m_color(color)
    {

    }

    std::string GetName()
    {
        return m_name;
    }

    std::string GetColor()
    {
        return m_color;
    }

private:
    std::string m_name;
    std::string m_color;
};

#endif // __TREE_TYPE_H__