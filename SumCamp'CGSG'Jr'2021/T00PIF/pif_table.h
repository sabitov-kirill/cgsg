/* LAST UPDATE: 18.07.2021
 * PROGRAMMER : KS6
 * FILE NAME  : PifTable_table.h
 * PURPOSE    : PifTableagore table output task.
 */

struct PifTable {
	float begin, step;
	int count;

private:
	int max_num_len;
	void MaxNumLen();
public:
	void GetInfo();
	void Output();
};

/* END OF 'PifTable_table.cpp' FILE */