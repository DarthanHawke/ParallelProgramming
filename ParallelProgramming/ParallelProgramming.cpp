#include <iostream>
#include <ctime>
#include "LabStandart.cpp"
#include "LabWinAPI.cpp"
#include "LabThread.cpp"


inline _int64 HightTime() {
	_asm {
		rdtsc
	}
}


_int64 pft_start, time_start;
_int64 pft_finish, time_finish;


#define SPEED_START_CONSOLE pft_start = HightTime();
#define SPEED_FINISH_CONSOLE pft_finish = HightTime(); std::cout << "Result speed = " << pft_finish - pft_start << ";\n";
#define TIME_START_CONSOLE time_start = clock();
#define TIME_FINISH_CONSOLE time_finish = clock(); std::cout << "Result time = " << double(time_finish - time_start) / CLOCKS_PER_SEC << "s;\n";


int main()
{
	std::cout << "One thread:\n";

	TIME_START_CONSOLE
	SPEED_START_CONSOLE

	pp_lbst::lbst onethread;
	std::cout << "Result = " << onethread.alter_sign(onethread.array) << ";\n";

	SPEED_FINISH_CONSOLE
	TIME_FINISH_CONSOLE


	std::cout << "\nFour thread WinAPI:\n";
	
	TIME_START_CONSOLE
	SPEED_START_CONSOLE

	pp_lbwapi::lbwapi fourthreadwin;
	std::cout << "Result = " << fourthreadwin.sign_parallel(fourthreadwin.array) << ";\n";

	SPEED_FINISH_CONSOLE
	TIME_FINISH_CONSOLE


	std::cout << "\nFour thread:\n";

	TIME_START_CONSOLE
	SPEED_START_CONSOLE

	pp_lbthrd::lbthrd fourthread;
	std::cout << "Result = " << fourthread.sign_parallel(fourthread.array) << ";\n";

	SPEED_FINISH_CONSOLE
	TIME_FINISH_CONSOLE

	return 0;
}
