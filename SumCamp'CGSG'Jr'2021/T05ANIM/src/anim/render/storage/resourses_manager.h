/* FILE NAME  : resourses_manager.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 22.07.2021
 * PURPOSE    : Resourses type declaration module.
 */

#ifndef __resourses_manager_h_
#define __resourses_manager_h_

#include "../../../kigl.h"
#include <map>
#include <string>

namespace kigl
{
  // Resours storage manager class template
  template<typename resours_type, typename index_type = INT>
  class resourses_manager
  {
  protected:
    // Resours with indexator type
    struct resours_type_indexated : resours_type
    {
    public:
      // Resours reference index
      index_type ResoursIndex;

      /* Class default constructor */
      resours_type_indexated(void) : ResoursIndex{}
      {
      } /* End of 'entry_ref' function */

      /* Class constructor.
        * ARGUMENTS:
        *   - entry reference to be attached:
        *       const entry_ref &Entry;
        *   - entry reference index value:
        *       const index_type &RefVal;
        */
      resours_type_indexated(const resours_type& Entry, const index_type& ResoursIndex = {}) :
        resours_type(Entry), ResoursIndex(ResoursIndex)
      {
      } /* End of 'entry_ref' function */
    };

    // Reourses storage
    std::map<index_type, resours_type_indexated> Storage;
    // Total resourses references count in storage for indexsation
    INT ResoursesReferencesCnt;

    /* Resourses manager constructor */
    resourses_manager(VOID) : ResoursesReferencesCnt(0)
    {
    } // End of 'resorses_manager' function

    /* Resourses manager destructor */
    ~resourses_manager(VOID)
    {
    } // End of 'resorses_manager' function

    /* Adding resours to storage function.
     * ARGUMENTS:
     *   - resours to add:
     *       const resours_type &Res;
     * RETURNS:
     *   (resours_type *) pointer to resours from storage.
     */
    resours_type* Add(const resours_type& Res)
    {
      if constexpr (std::is_convertible_v<index_type, INT>)
      {
        // Creating reourse with indexator jacket
        resours_type_indexated res_ref(Res, ResoursesReferencesCnt++);

        // Placing resours with indexator jacket (reference) to storage to get index to delete in future
        return &(Storage[res_ref.ResoursIndex] = res_ref);
      }
      else
      {
        // Creating reourse with indexator jacket
        resours_type_indexated res_ref(Res, Res.Name);

        // Placing resours with indexator jacket (reference) to storage to get index to delete in future
        return &(Storage[res_ref.ResoursIndex] = res_ref);
      }
    } // End of 'Add' function

    /* Entry delete function.
     * ARGUMENTS:
     *   - resours to delete pointer:
     *       resours *Res;
     * RETURNS:
     *   (resource_manager &) self reference.
     */
    resourses_manager& Delete(resours_type* Res)
    {
      // Check if incoming resours isnt empty, calling its free method
      if (Res == nullptr)
        return *this;
      Res->Free();

      // Try to find resours in storage to check if its exist
      auto res = Storage.find(reinterpret_cast<resours_type_indexated*>(Res)->ResoursIndex);
      if (res == Storage.end())
        return *this;

      // Deliting resours from storage
      Storage.erase(res);
      return *this;
    } // End of 'Delete' function

    /* Manager close method to use instead of destructor
     * ARGUMENTS: None
     * RETURNS: None.
     */
    VOID Close(VOID)
    {
      // Calling free method of each resourse
      for (auto& res : Storage)
        res.second.Free();
    } // End of 'Close' function

  public:
    /* Find resource at stock function.
     * ARGUMENTS:
     *   - resource index (name or count) to find:
     *       const std::string &Name;
     * RETURNS:
     *   (type *) reference to found elememt.
     */
    resours_type* Find(const index_type& IndexToFind)
    {
      if (Storage.find(IndexToFind) == Storage.end())
        return nullptr;
      return &Storage[IndexToFind];
    } // End of 'Find' function
  };
}

#endif // !__resourses_manager_h_

// END OF 'resourses_manager.h' FILE