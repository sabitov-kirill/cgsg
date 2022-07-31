/* LAST UPDATE: 18.07.2021
 * PROGRAMMER : KS6
 * FILE NAME  : PifTable_table.cpp
 * PURPOSE    : PifTableagore table output task.
 */

#include <iostream>
#include <string>
#include <clocale>
#include "pif_table.h""

void PifTable::MaxNumLen()
{
	int max_num = static_cast<int>((begin + count * step - 1) * (begin + count * step - 1));

	max_num_len = static_cast<int>(std::to_string(max_num).length()) + 4;
}

void PifTable::GetInfo()
{
	std::cout << "Enter pifagore table first number: ";
	std::cin >> PifTable::begin;
	std::cout << "Enter pifagore table numbers step: ";
	std::cin >> PifTable::step;
	std::cout << "Enter pifagore table numbers count: ";
	std::cin >> PifTable::count;
}

void PifTable::Output()
{
	MaxNumLen();

	for (float i = begin; i <= begin + step * count; i += step)
	{
		for (float j = begin; j <= begin + step * count; j += step)
		{
			std::cout.width(max_num_len);
			std::cout.precision(3);
			std::cout << std::fixed << i * j << " ";
		}
		std::cout << std::endl;
	}
	std::cin.get();
}

/* END OF 'PifTable_table.cpp' FILE */