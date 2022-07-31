#include <iostream>
#include <fstream>
#include <string>

template <typename T>
void swap( T &A, T &B )
{
  T tmp = A;
  A = B;
  B = tmp;
}

template <typename T>
struct array
{
  T *Data;
  int length;

  // default constructor
  array() : length(0), Data(nullptr)
  {
  }

  // constructor by size
  array( int N ) : length(N), Data(new T[N])
  {
  }

  // copying constuctor
  array( const array &A ) : length(A.length), Data(new T[A.length])
  {
    for (int i = 0; i < A.length; i++)
      Data[i] = A.Data[i];
  }

  // constructor by template type array
  array( T *Data, int N ) : length(N), Data(new T[N])
  {
    for (int i = 0; i < N; i++)
      this->Data[i] = Data[i];
  }

  ~array()
  {
    if (Data != nullptr)
      delete[] Data;
  }

  void load( const std::string &FileName )
  {
    if (Data != nullptr)
      delete[] Data;

    try
    {
      std::fstream f;

      f.open("flex.txt", std::fstream::in);
      f >> length;
      Data = new T[length];
      for (int i = 0; i < length; i++)
      f >> Data[i];
      f.close();
    }
    catch (std::bad_alloc &)
    {
      std::cout << "Memory allocation error!..";
    }
  }

  void save( const std::string &FileName )
  {
    std::fstream f;

    f.open( "flex_out.txt", std::fstream::out );
    for (int i = 0; i < length; i++)
      f << Data[i] << std::endl;
    f.close();
  }

  void sort( const int Start, const int End ) const
  {
    if (Data == nullptr)
      return;

    T middle = Data[static_cast<int>((Start + End) / 2)];
    int i = Start, j = End;

    while (i <= j)
    {
      while (Data[i] < middle)
        i++;
      while (Data[j] > middle)
        j--;
      if (i <= j)
      {
        swap( Data[i], Data[j] );
        i++, j--;
      }
    }

    if (j > Start)
      sort( Start, j );
    if (i < End)
      sort( i, End );
  }

  void sort()
  {
    if (Data == nullptr)
      return;
    sort(0, length - 1);
  }

  T & operator [] ( int Index )
  {
    if (Index >= 0 && Index <= length)
      return Data[Index];
    if (Index < 0  && Index >= -length)
      return Data[Index + length];
    return Data[0];
  }

  array & operator = ( array &A )
  {
    if (Data != nullptr)
      delete[] Data;

    length = A.length;
    Data = new T[A.length];
    for (int i = 0; i < A.length; i++)
      Data[i] = A.Data[i];
    return *this;
  }

  array operator + ( const array &A ) const
  {
    array sum(length + A.length);

    int n = 0;
    for (int i = 0; i < length; i++, n++)
      sum.Data[n] = Data[i];
    for (int i = 0; i < length; i++, n++)
      sum.Data[n] = A.Data[i];

    return sum;
  }
};

std::string operator* ( std::string Str, int Num )
{
  std::string a;

  for (int i = 0; i < Num; i++)
    for (int j = 0; j < Str.length(); j++)
      a += Str[j];

  return a;
}

int main()
{
  array<double> arr;
  double a[] = {1, 1.2, 3, 4};

  arr.load("flex.txt");
  arr.load("flex_out.txt");

  arr[9] = 1;
  array<double> arr1;
  arr1 = arr;
  array<double> arr2(arr1);
  array<double> arr3(a, 4);
  double ff = arr3[-5];
  array<double> arr4 = arr1 + arr2;

  std::string flex_mega = std::string("Konev, qq! ") * 3;

  arr.sort();
  arr.save("flex_out.txt");

  return 30;
}