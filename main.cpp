#include <iostream>
#include "timed_process.hpp"

using namespace std;

void fun1(void)
{
	cout << __func__ ;
	
}
void fun2(void)
{
	size_t j = 0;
	for (size_t i = 0; i < SIZE_MAX/10000000000; i++)
	{
		if (i%2 ==0)
			j++;
		else
			j--;
	}
	cout << __func__ ;
}

int main(int argc, char const *argv[])
{
	timed_process_manager* TPM = TPM->Instance();

	/*
	TPM->AddProcess(PER_SECOND(2), per2Sec);
	TPM->AddProcess(PER_MINUTE(1), per1min);
	*/
	TPM->AddProcess(TPM->PER_SECOND*2, fun1);
	TPM->AddProcess(TPM->PER_SECOND*1, fun2);

	TPM->StartProcess();

	return 0;
}

