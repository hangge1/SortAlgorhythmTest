#pragma once

//ʱ��ͳ���õ���
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

    //����Ѿ�ֹͣ���ͷ���ֹͣʱ��ͳ��ʱ�䣬���򷵻�ʵʱʱ��!
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