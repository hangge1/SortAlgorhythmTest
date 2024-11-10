#pragma once

class Tool
{
public:
    static Tool& Get()
    {
        static Tool tool;
        return tool;
    }

    int GetRamdom()
    {
        return rand();
    }

    int GetRandom(int MinNum, int MaxNum)
    {
        return (rand() % (MaxNum - MinNum + 1)) + MinNum;
    }

private:
    Tool()
    {
        srand((unsigned)time(NULL));
    }
};