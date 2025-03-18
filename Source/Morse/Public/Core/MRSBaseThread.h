/*****************************************************************
* @file   MRSBaseThread.h
 * @brief  /
 * 
 * @author Nicolas Brugie.
 * @date   March 2025
 * @copyright Copyright 2025 NicoBrugie. All rights reserved.
 *********************************************************************/
#pragma once

#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "HAL/ThreadSafeBool.h"
#include "Logging/StructuredLog.h"
#include "Misc/SingleThreadRunnable.h"

class MORSE_API MRSThreadBase : public FRunnable
{
public:

    MRSThreadBase(const FTimespan& InUpdateFrequency, const TCHAR* ThreadDescription)
        : Stopping(false)
        , ThreadTickRate(InUpdateFrequency)
    {
        Paused.AtomicSet(false);
        Thread = FRunnableThread::Create(this, ThreadDescription, 128 * 1024, TPri_Normal, FPlatformAffinity::GetPoolThreadMask());
    }

    virtual ~MRSThreadBase()
    {
        if (Thread != nullptr)
        {
            Thread->Kill(true); 
            delete Thread;
        }
    }

    void Wait(float Seconds)
    {
        FPlatformProcess::Sleep(Seconds);
    };

    virtual void ThreadTick(double dDeltaTime)
    {
    };
    
    virtual bool Init() override
    {
        StartTime = FPlatformTime::Seconds();
        return true;
    }

    virtual uint32 Run() override
    {
        HasStopped.AtomicSet(false);

        while (!Stopping)
        {
            if (Paused)
            {
                if (!IsVerifiedSuspended)
                {
                    IsVerifiedSuspended.AtomicSet(true);
                }
                continue;
            }

            Wait(ThreadTickRate.GetTotalSeconds());

            double Now = FPlatformTime::Seconds();
            double ElapsedMilliseconds = (Now - StartTime) * 1000.0;

            ThreadTick(ElapsedMilliseconds);
            StartTime = Now;
        }

        HasStopped.AtomicSet(true);
        return 0;
    }

    virtual void Stop() override
    {
        SetPaused(true);
        Stopping = true;
    }

    void SetPaused(bool MakePaused)
    {
        Paused.AtomicSet(MakePaused);
        if (!Paused)
        {
            IsVerifiedSuspended.AtomicSet(false);
        }
    }
    
    bool ThreadIsPaused()
    {
        return Paused;
    }

    bool ThreadIsVerifiedSuspended()
    {
        return IsVerifiedSuspended;
    }

    bool ThreadHasStopped()
    {
        return HasStopped;
    }

protected:
    double StartTime;

    FThreadSafeBool Paused;
    FThreadSafeBool IsVerifiedSuspended;
    FThreadSafeBool HasStopped;

    bool Stopping;
    FRunnableThread* Thread;
    FTimespan ThreadTickRate;
};
