#include <iostream>
#include <functional>
#include <vector>

class SkillManager
{
public:
    enum ComboID
    {
        UNKNOWN,
        HOLD_AND_ATTACK,
        PUNCH_BELOW_THE_BELT
    };

    static void kick()
    {
        std::cout << "Kick!" << std::endl;
    }

    static void hold()
    {
        std::cout << "Holding!" << std::endl;
    }

    static void punch()
    {
        std::cout << "Punch!" << std::endl;
    }

    static void dodge()
    {
        std::cout << "Dodging!" << std::endl;
    }

    static void sit()
    {
        std::cout << "Sitting!" << std::endl;
    }

    static bool Combo1Performable()
    {
        return comboID == UNKNOWN || comboID == HOLD_AND_ATTACK;
    }

    static bool Combo2Performable()
    {
        return comboID == UNKNOWN || comboID == PUNCH_BELOW_THE_BELT;
    }

    static ComboID comboID;
};

SkillManager::ComboID SkillManager::comboID = SkillManager::UNKNOWN;

class ComboHandler
{
public:
    ComboHandler* nextHandler;
    SkillManager::ComboID comboID;

    struct ComboStep
    {
        char key;
        std::function<bool()> precondition;
        std::function<void()> action;
    };

    std::vector<ComboStep> combo;
    size_t currentIndex;

    ComboHandler(const std::vector<ComboStep>& c, SkillManager::ComboID id)
        : combo(c), currentIndex(0), comboID(id), nextHandler(nullptr)
    {
    }

    virtual void handleCombo(char key)
    {
        if (currentIndex >= combo.size())
        {
            currentIndex = 0;  // Reset the index if it's out of range
        }

        if (key == combo[currentIndex].key && combo[currentIndex].precondition())
        {
            SkillManager::comboID = comboID;
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
            SkillManager::comboID = SkillManager::ComboID::UNKNOWN;
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
        {'Z', SkillManager::Combo1Performable, SkillManager::hold},
        {'X', SkillManager::Combo1Performable, SkillManager::punch},
        {'X', SkillManager::Combo1Performable, SkillManager::punch},
        {'Z', SkillManager::Combo1Performable, SkillManager::dodge},
        {'X', SkillManager::Combo1Performable, SkillManager::kick}
    }, SkillManager::HOLD_AND_ATTACK)
    {
    }
};

class ComboAttack2Handler : public ComboHandler
{
public:
    ComboAttack2Handler() : ComboHandler({
        {'X', SkillManager::Combo2Performable, SkillManager::punch},
        {'Z', SkillManager::Combo2Performable, SkillManager::dodge},
        {'X', SkillManager::Combo2Performable, SkillManager::punch},
        {'Z', SkillManager::Combo2Performable, SkillManager::sit},
        {'X', SkillManager::Combo2Performable, SkillManager::punch}
    }, SkillManager::PUNCH_BELOW_THE_BELT)
    {
    }
};

int main()
{
    // Set the combo ID in the SkillManager
    SkillManager::comboID = SkillManager::UNKNOWN;

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

    keyPresses = {'X', 'Z', 'X', 'Z', 'X'};
    for (char key : keyPresses)
    {
        combo1->handleCombo(key);
    }

    // Clean up
    delete combo1;
    delete combo2;

    return 0;
}