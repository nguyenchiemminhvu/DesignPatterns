#include <iostream>
#include <functional>
#include <vector>

class SkillManager
{
public:
    static void kick()
    {
        std::cout << "Performing kick!" << std::endl;
    }

    static void hold()
    {
        std::cout << "Holding!" << std::endl;
    }

    static void punch()
    {
        std::cout << "Performing punch!" << std::endl;
    }

    static void dodge()
    {
        std::cout << "Dodging!" << std::endl;
    }

    static void sit()
    {
        std::cout << "Sitting!" << std::endl;
    }
};

class ComboHandler
{
public:
    ComboHandler* nextHandler;

    struct ComboStep
    {
        char key;
        std::function<void()> action;
    };

    std::vector<ComboStep> combo;
    size_t currentIndex;

    ComboHandler(const std::vector<ComboStep>& c)
        : combo(c), currentIndex(0)
    {
    }

    virtual void handleCombo(char key)
    {
        if (currentIndex >= combo.size())
        {
            currentIndex = 0;  // Reset the index if it's out of range
        }

        if (key == combo[currentIndex].key)
        {
            combo[currentIndex].action();  // Execute the corresponding skill/action
            currentIndex++;
            if (currentIndex == combo.size())
            {
                std::cout << "Combo executed!" << std::endl;
                currentIndex = 0;  // Reset the index for the next combo
            }
        }
        else
        {
            currentIndex = 0;  // Reset the index if there's no match
        }

        if (nextHandler != nullptr)
        {
            nextHandler->handleCombo(key);
        }
    }

    void setNextHandler(ComboHandler* handler)
    {
        nextHandler = handler;
    }
};

class ComboAttack1Handler : public ComboHandler
{
public:
    ComboAttack1Handler() : ComboHandler({
        {'Z', SkillManager::hold},
        {'X', SkillManager::punch},
        {'X', SkillManager::punch},
        {'Z', SkillManager::dodge},
        {'X', SkillManager::kick}
    })
    {
    }
};

class ComboAttack2Handler : public ComboHandler
{
public:
    ComboAttack2Handler() : ComboHandler({
        {'X', SkillManager::punch},
        {'Z', SkillManager::dodge},
        {'X', SkillManager::punch},
        {'Z', SkillManager::sit},
        {'X', SkillManager::punch}
    })
    {
    }
};

int main()
{
    // Create the combo handlers
    ComboHandler* combo1 = new ComboAttack1Handler();
    ComboHandler* combo2 = new ComboAttack2Handler();

    // Set up the chain of responsibility
    combo1->setNextHandler(combo2);

    // Simulate key presses
    std::vector<char> keyPresses = {'Z', 'X', 'X', 'Z', 'X'};
    for (char key : keyPresses)
    {
        combo1->handleCombo(key);
    }

    // Clean up
    delete combo1;
    delete combo2;

    return 0;
}