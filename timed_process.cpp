	#include "timed_process.hpp"

	timed_process_manager* timed_process_manager::singleton_instance = nullptr;

	timed_process_manager *timed_process_manager::Instance()
	{
		if (singleton_instance == nullptr)
		{
			singleton_instance = new timed_process_manager;
			fprintf(stdout, "timed process manager created\n");
		}
		return singleton_instance;
	}

	void timed_process_manager::StartProcess()
	{
		while (true)
		{
			clock_t now = clock();
			for (auto it = processList.begin(); it != processList.end(); ++it)
			{
				auto val = *it;
				uint32_t idle = (now-val->last_process_time) / CLOCKS_PER_SEC;
				if (idle < val->per_second)
					continue;
				else if (idle > val->per_second)
					fprintf(stdout, "Idle detected: %d second(s)\n", idle);
				
				printf("clock: %d :: ", now);
				try { (*val->f) (); }
				catch (std::exception& e)
				{
					fprintf(stderr, "Error handled while function processing: %s\n", e.what());
				}
				std::cout << "\n";
				val->last_process_time = now;
			}
		}
	}

	void timed_process_manager::AddProcess(uint32_t per_second, void (*f)(void))
	{
		processList.insert(new timed_process(per_second, f));
	}

	timed_process_manager::timed_process_manager()
	{
	}

	timed_process_manager::~timed_process_manager()
	{

		for (auto it = processList.begin(); it != processList.end(); ++it)
		{
			auto val = *it;
			free(val);
		}
		fprintf(stdout, "timed process manager destroyed\n");
	}
