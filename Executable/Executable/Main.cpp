#include <iostream>
#include <Windows.h>

// function_one() will be used as our target.
void function_one()
{
	std::cout << "::FunctionOne()\n";
}

// function_two() will be used to replace function_one().
void function_two()
{
	std::cout << "::FunctionTwo()\n";
}

int main()
{
	// Looping forever.
	while(true)
	{
		// Getting function_one() and function_two() addresses.
		void* func_one_pointer = &function_one;
		void* func_two_pointer = &function_two;

		// Printing out function_one() and function_two() addresses.
		printf("function_one() address: %p\n", func_one_pointer);
		printf("function_two() address: %p\n", func_two_pointer);

		// Calling function_one() and function_two();
		function_one();
		function_two();

		// Sleeping for 100 MS.
		Sleep(100);

		// Cleaning console.
		system("CLS");
	}

	return 0;
}