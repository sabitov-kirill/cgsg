/* FILE NAME  : stock.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Stock Type handle modules.
 */

#ifndef __stock_h_
#define __stock_h_

#include "../kigl.h"

 // Template stock Type
template <typename Type>
class stock
{
private:
  Type* Array;           // Data storage array
  INT RealSize, MaxSize; // Current array size and current allocated memory size
  INT BlockSize;         // Block size to allocate memory. If equals to 0 allocating twice big size of previous

public:
  /* Stock Type constructor.
   * ARGUMENTS: None.
   */
  stock(VOID) : Array(nullptr), RealSize(0), MaxSize(0), BlockSize(0)
  {
  } // End of 'stock' constructor

  /* Stock Type constructor by size.
   * ARGUMENTS:
   *   - start block size:
   *       INT StartBlockSize;
   *   - block size to allocate memory, if 0 allocating twice big of previous:
   *       INT BlockSize;
   */
  stock(INT StartBlockSize, INT BlockSize = 0) : Array(new Type[StartBlockSize]), RealSize(0), MaxSize(StartBlockSize), BlockSize(BlockSize)
  {
  } // End of 'stock' constructor

  /* Stock Type constructor by size.
   * ARGUMENTS:
   *   - start block size:
   *       INT StartBlockSize;
   */
  stock(const stock& StockToCopy) : Array(new Type[StockToCopy.RealSize]), RealSize(StockToCopy.RealSize), MaxSize(StockToCopy.RealSize), BlockSize(0)
  {
    // Copy data
    for (INT i = 0; i < RealSize; i++)
      Array[i] = StockToCopy.Array[i];
  } // End of 'stock' constructor

  /* Stock Type destructor.
   * ARGUMENTS: None.
   */
  ~stock(VOID)
  {
    for (int i = 0; i < RealSize; i++)
      delete Array[i];

    // Free memory
    if (Array != nullptr)
      delete[] Array;

    // Set parametrs to default
    Array = nullptr;
    RealSize = 0;
    MaxSize = 0;
  } // End of 'stock' destructor

  /* Stock copying operator.
   * ARGUMENTS:
   *   - start block size:
   *       INT StartBlockSize;
   */
  stock& operator=(const stock& CopyData)
  {
    // Clear old data if exist
    if (Array != nullptr)
      delete[] Array;

    // Set new data params
    Array = new Type[CopyData.RealSize];
    RealSize = CopyData.RealSize;
    MaxSize = CopyData.RealSize;

    // Set new data
    for (int i = 0; i < RealSize; i++)
      Array[i] = CopyData.Array[i];

    return *this;
  } // End of 'operator=' function

  /* Getting current size of stock function.
   * ARGUMENTS: None.
   * RETURN:
   *   (INT) Items amount in stock.
   */
  INT Size(VOID) const
  {
    return RealSize;
  } // End of 'Size' function

  /* Adding new ellement to stock function.
   * ARGUMENTS:
   *   - New ellement data:
   *       const Type &NewData;
   * RETURNS:
   *   (stock &) current stock ref.
   */
  stock& Add(const Type& NewData)
  {
    if (RealSize >= MaxSize)
    {
      // Increase allocated memory
      if (MaxSize == 0)
        MaxSize = 1;
      else if (BlockSize != 0)
        MaxSize += BlockSize;
      else
        MaxSize *= 2;

      Type* new_bulk = new Type[MaxSize];
      if (Array != nullptr)
      {
        // Copy old data
        for (int i = 0; i < RealSize; i++)
          new_bulk[i] = Array[i];
        // Remove old data
        delete[] Array;
      }
      Array = new_bulk;
    }

    // Add new ellement
    Array[RealSize++] = NewData;

    return *this;
  } // End of 'Add' function

  /* Adding new ellement to stock operator.
   * ARGUMENTS:
   *   - New ellement data:
   *       const Type &NewData;
   * RETURNS:
   *   (stock &) current stock ref.
   */
  stock& operator<<(const Type& NewData)
  {
    return Add(NewData);
  } // End of 'operator<<' function

  /* Getting ellement by index operator.
   * ARGUMENTS:
   *   - New ellement data:
   *       const Type &NewData;
   * RETURNS:
   *   (stock &) current stock ref.
   */
  Type& operator[](int Index)
  {
    return Array[mth::Clamp(Index, 0, RealSize)];
  } // End of 'operator[]' function
  Type& operator[](int Index) const
  {
    return Array[mth::Clamp(Index, 0, RealSize)];
  } // End of 'operator[]' function

  /* Stock clear function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
  VOID Clear(VOID)
  {
    RealSize = 0;
  } // End of 'Clear' function

  /* Stock calling call back for each ellement function.
   * ARGUMENTS:
   *   - callback function to call on each ellement:
   *       cb &CallBack;
   * RETURNS: None.
   */
  template <typename cb>
  VOID ForEach(const cb& CallBack)
  {
    for (int i = 0; i < RealSize; i++)
      CallBack(Array[i]);
  } // End of ForEach'' function
};

#endif // !__stock_h_

// END OF 'stock.h' FILE