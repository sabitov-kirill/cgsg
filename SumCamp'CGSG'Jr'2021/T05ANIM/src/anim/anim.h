/* FILE NAME  : anim.h
 * PROGRAMMER : KS6
 * LAST UPDATE: 22.07.2021
 * PURPOSE    : Animation system handle module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "../utilities/stock.h"
#include "win/win.h"

#include "input.h"
#include "timer.h"
#include "scene.h"

#include "render/render.h"

namespace kigl
{
  // Animation system type
  class anim : public win, public render, public input, public timer
  {
  private:
    scene Scene;

    /* Animation render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      timer::Response();
      input::Response();

      Scene.Response(this);

      render::Start();
      Scene.Render(this);
      render::End();

      render::CopyFrame();
    } // End of 'Render' function

    /*
     * Virtual callbacks override
     */

    /* Window Initialisation callback function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID ) override
    {
      render::Init();
    } // End of 'Init function

    /* Window Closing callback function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID ) override
    {
      render::Close();
    } // End of 'Close function

    /* Window Resize callback function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID ) override
    {
      render::Resize();

      Render();
    } // End of 'Resize function

    /* Window Timer tick callback function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Timer( VOID ) override
    {
      Render();
    } // End of 'Timer function

    /* Window message loop Idle callback function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID ) override
    {
      Render();
    } // End of 'Idle function

  private:
    // Single class instance
    static anim Instance;

    /* Animation system Type constructor.
     * ARGUMENTS: None.
     */
    anim( HINSTANCE hInstance, const char *Title = "Window With Animation System Included" ) :
      win(hInstance, Title), input(win::hWnd, MouseWheel), timer(), Scene(this), render(win::hWnd, W, H)
    {
    } // End of 'anim' constructor

    /* Animation system Type constructor.
     * ARGUMENTS: None.
     */
    anim( const char *Title = "Window With Animation System Included" ) :
      win(GetModuleHandle(nullptr), Title), input(win::hWnd, MouseWheel), timer(), Scene(this), render(win::hWnd, W, H)
    {
    } // End of 'anim' constructor

    /* Animation system Type destructor.
     * ARGUMENTS: None.
     */
    ~anim( VOID )
    {
    } // End of 'anim' destructor

  public:
    /* Getting single class instance.
     * ARGUMENTS: None.
     *   (anim) single class instance.
     */
    static anim & Get( VOID )
    {
      return Instance;
    }

    /* Getting pointer single class instance.
     * ARGUMENTS: None.
     *   (anim) single class instance.
     */
    static anim * GetPtr( VOID )
    {
      return &Instance;
    }

    /* Adding new unit to animation system scene operator.
     * ARGUMENTS:
     *   - New unit pointer:
     *       unit *Uni;
     * RETURNS:
     *   (scene &) current scene ref.
     */
    anim & operator<< ( unit *Uni )
    {
      Scene << Uni;

      return *this;
    } // End of 'operator<<' function
  };
}

#endif // !__anim_h_

// END OF 'anim.h' FILE