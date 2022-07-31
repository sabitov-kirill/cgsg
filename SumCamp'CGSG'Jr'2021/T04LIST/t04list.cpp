#include <iostream>

#include "debug.h"

namespace ks6
{
  template <typename Type>
  class list
  {
  private:
    struct entry
    {
      Type Data;
      entry *Next;

      entry( Type NewData, entry *NewNext = nullptr ) : Data(NewData), Next(NewNext)
      {
      }
    } *Start;
    int LengthPrivate;

  public:
    const int &Length;

    list() : Start(nullptr), LengthPrivate(0), Length(LengthPrivate)
    {
    }

    list( list &L ) : Start(nullptr), LengthPrivate(0), Length(LengthPrivate)
    {
      entry **ptr_copy = &L.Start;
      entry **ptr_set = &Start;

      while (*ptr_copy != nullptr)
      {
        *ptr_set = new entry((*ptr_copy)->Data);
        ptr_set = &(*ptr_set)->Next;
        ptr_copy = &(*ptr_copy)->Next;

        LengthPrivate++;
      }
    }

    ~list()
    {
      while (Start != nullptr)
      {
        entry *old = Start;
        Start = Start->Next;
        delete old;
        LengthPrivate--;
      }
    }

    void DeadInsideGremlin( void )
    {
      int dead_inside = 1000;
      while(dead_inside > 0)
        PushBack(dead_inside), dead_inside -= 7;
    }

    list & PushFront( Type NewData )
    {
      Start = new entry(NewData, Start);
      LengthPrivate++;

      return *this;  
    }

    list & PushBack( Type NewData )
    {
      entry **ptr = &Start;

      while (*ptr != nullptr)
        ptr = &(*ptr)->Next;
      *ptr = new entry(NewData);
      LengthPrivate++;

      return *this;
    }

    Type PopFront( void )
    {
      if (Start != nullptr)
      {
        entry *old = Start;
        Type old_data = old->Data;

        Start = Start->Next;
        delete old;
        LengthPrivate--;

        return old_data;
      }
      return Type(0);
    }

    Type PopBack( void )
    {
      if (Start != nullptr)
      {
        entry **ptr = &Start;

        while ((*ptr)->Next != nullptr)
          ptr = &(*ptr)->Next;

        Type old_data = (*ptr)->Data;
        delete *ptr, *ptr = nullptr;
        LengthPrivate--;

        return old_data;
      }
      return Type(0);
    }

    bool PopFront( Type &OldData )
    {
      if (Start != nullptr)
      {
        entry *old = Start;
        Start = Start->Next;

        OldData = old->Data;
        delete old;
        LengthPrivate--;

        return true;
      }
      return false;
    }

    bool PopBack( Type &OldData )
    {
      if (Start != nullptr)
      {
        entry **ptr = &Start;

        while ((*ptr)->Next != nullptr)
          ptr = &(*ptr)->Next;

        OldData = (*ptr)->Data;
        delete *ptr, *ptr = nullptr;
        LengthPrivate--;

        return true;
      }
      return false;
    }

    void Clear( void )
    {
      while (Start != nullptr)
      {
        entry *old = Start;
        Start = Start->Next;
        delete old;
        LengthPrivate--;
      }
    }

    bool IsEmpty( void ) const
    {
      return Start != nullptr;
    }

    Type & operator[] ( int Index )
    {
      entry **ptr = &Start;

      for (int i = 0; i < Index && i < Length - 1; i++)
        ptr = &(*ptr)->Next;
      return (*ptr)->Data;
    }

    list & operator= ( list &L )
    {
      if (Start != nullptr)
        Clear();

      entry **ptr_copy = &L.Start;
      entry **ptr_set = &Start;

      while (*ptr_copy != nullptr)
      {
        *ptr_set = new entry((*ptr_copy)->Data);
        ptr_set = &(*ptr_set)->Next;
        ptr_copy = &(*ptr_copy)->Next;

        LengthPrivate++;
      }
      return *this;
    }
  };
}

template <typename Type>
std::ostream & operator<<( std::ostream &Out, ks6::list<Type> &L )
{
  Out << "{ ";
  for (int i = 0; i < L.Length; i++)
    Out << L[i] << (i == L.Length - 1 ? " }" : ", ");
  return Out;
}

int main( void )
{
  ks6::list<double> L;

  L.PushFront(1).PushFront(10.15).PushFront(993);

  ks6::list<double> LOld = L;
  LOld.PushBack(1000);
  double a = LOld[5];
  std::cout << "TEST LIST - " << LOld << std::endl;
  LOld.Clear();

  double f = L.PopBack();
  double g = L.PopFront();
  double h = L.PopBack();

  ks6::list<int> flex;
  flex.DeadInsideGremlin();
  std::cout << "asd LIST - " << flex;
  return 30;
}