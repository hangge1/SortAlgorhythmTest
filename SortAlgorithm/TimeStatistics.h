#pragma once

//时间统计用的类
class TimeStatistics
{
public:
    TimeStatistics()
    {
        SetStartPoint();
    }

    ~TimeStatistics()
    {
        Stop();
    }

    float GetTime_s() const
    {
        return GetTime_us() / 1000000.f;
    }

    float GetTime_ms() const
    {
        return GetTime_us() / 1000.f;
    }

    //如果已经停止，就返回停止时的统计时间，否则返回实时时间!
    float GetTime_us() const
    {
        if(HasStop) return (float)Duration;
        
        return (float)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }

    void Stop()
    {
        if(!HasStop) HasStop = true;
        Duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }

    void Restart()
    {
        SetStartPoint();
        HasStop = false;
    }
private:
    void SetStartPoint()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    std::chrono::high_resolution_clock::time_point start;
    long long Duration = 0;
    bool HasStop = false;
};