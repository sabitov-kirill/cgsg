#include <fstream>
#include <string>
#include <array>

template <typename T>
void swap(T& A, T& B)
{
	T tmp = A;
	A = B;
	B = tmp;
}

template <typename T>
void sort(T *Mass, int Start, int N)
{
	T middle = Mass[static_cast<int>((Start + N) / 2)];
	int i = Start, j = N;

	while (i <= j)
	{
		while (Mass[i] < middle)
			i++;
		while (Mass[j] > middle)
			j--;
		if (i <= j)
		{
			swap(Mass[i], Mass[j]);
			i++, j--;
		}
	}

	if (j > Start)
		sort(Mass, Start, j);
	if (i < N)
		sort(Mass, i, N);
}

int main()
{
	std::fstream f;
	int N;

	// get numbers
	f.open("flex.txt", std::fstream::in);
	f >> N;
	double *mass = static_cast<double *>(malloc(sizeof(double) * N));
	for (int i = 0; i < N; i++)
		f >> mass[i];
	f.close();

	// sort numbers
	sort(mass, 0, N - 1);

	// write numbers
	f.open("flex_out.txt", std::fstream::out);
	for (int i = 0; i < N; i++)
		f << mass[i] << std::endl;
	f.close();

	free(mass);
}