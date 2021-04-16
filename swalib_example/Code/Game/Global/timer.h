#ifndef _TIMER_H_
#define _TIMER_H_

// Class to control time.
class cTimer
{
private:
	const double	m_fFixedTick;	// Time between every tick process. Seconds.
	double	m_fMaxElapsedTime;	// Max. elapsed time to process. Seconds.
	LARGE_INTEGER	m_Frequency;	// Freq. of the performance counter.
	LARGE_INTEGER	m_PreviousTime, m_CurrentTime;	// Iteration times.
	double	m_fElapsedTime;	// Time between iterations. Storing time remaining from previous process.
	double	m_fTotalTime;	// Total time for every g_fFixedTick since it started. Secs.
	double	m_fTimeBetwSlots;	// Time elpased between 2 Slot calls.

public:
	// Constructor.
	cTimer(double fFixedTick);

	// Set/Get Member variables.
	inline void SetMaxElapsedTime(double fElapsedTime) { m_fMaxElapsedTime = fElapsedTime; }
	inline double GetFixedTick() const { return m_fFixedTick; }
	inline double GetTimeBetwSlots() const { return m_fTimeBetwSlots; }
	inline double GetElapsedTime() const { return m_fElapsedTime; }
	inline double GetTotalTime() const { return m_fTotalTime; }

	// To call before ProcessSlots.
	void InitSlotsToProcess();

	// Process timer. True if there are next ticks to process.
	bool ProcessSlots();
};

#endif // !_TIMER_H_

