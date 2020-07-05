#ifndef TIMED_PROCESS
#define TIMED_PROCESS

#include <time.h>
#include <bits/stdc++.h>

/*
#define PER_SECOND(n)   (n)
#define PER_MINUTE(n)   (PER_SECOND(n)*60)
#define PER_HOUR(n)     (PER_MINUTE(n)*60)
#define PER_DAY(n)      (PER_HOUR(n)*24)
#define PER_MONTH(n)    (PER_DAY(n)*30)
#define PER_YEAR(n)     (PER_MONTH(n)*12)
*/

struct timed_process {
	clock_t last_process_time;
	uint32_t per_second;
	void (*f)(void);

	timed_process(uint32_t per_second_, void (*f_)(void)) :
	last_process_time(clock()),
	per_second(per_second_),
	f(f_)
	{
	}
};

class timed_process_manager
{
public:
	enum TIMING {
		PER_SECOND	= 1,
		PER_MINUTE	= PER_SECOND*60,
		PER_HOUR	= PER_MINUTE*60,
		PER_DAY		= PER_HOUR*24,
		PER_MONTH	= PER_DAY*30,
		PER_YEAR	= PER_MONTH*12,
	};
private:
	static timed_process_manager *singleton_instance;
	std::unordered_multiset<timed_process*> processList;
public:
	static timed_process_manager *Instance();
	void StartProcess();
	void AddProcess(uint32_t, void (*)(void));
public:
	timed_process_manager();
	~timed_process_manager();
};

#endif
