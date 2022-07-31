/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : raytracer.h
 * PURPOSE     : Ray tracing project.
 *               Ray tracer class handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               KS6
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'kirt'
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __raytracer_h_
#define __raytracer_h_

#include "../win/win.h"

#include "frame/frame.h"
#include "scene.h"
#include "timer.h"

#include "shapes/shapes.h"
#include "lights/lights.h"

#include <string>
#include <format>
#include <thread>

/* Project namespace */
namespace kirt
{
  /* Ray tracing image rednering window class */
  class raytracer : public win, public timer
  {
  public:
    // Ray tracer render camera
    camera Camera;
    // Ray tracer scene
    scene Scene;

    /* Class constructor */
    raytracer( const std::string &WindowTitle = "Ray Tracer Window." ) :
      win(WindowTitle), ThCount(std::thread::hardware_concurrency() - 3)
    {
    } // End of 'raytracing_wondow' function

  private:
    // Painting frame to screen data
    DBL SizeRatio = 1; // Frame scaling ratio

#pragma region Render_Handle

    // Window frame
    frame Frame;

    // Threads for prallel rendering
    std::thread Threads[11];   // Treads for drawing array
    const int ThCount;         // Treads for drawing count
    HANDLE RenderThreadHandle; // Separated thread for render

    /* Frame render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      // Starting drawing threads
      for (INT i = 1; i <= ThCount; i++)
        Threads[i - 1] = std::thread([this, i]()
          {
            kirt::intersection I;
            INT
              start_y = floor(static_cast<FLT>(Frame.H) / ThCount * i),
              end_y = ceil(static_cast<FLT>(Frame.H) / ThCount * (i + 1));
            INT rec = 1;

            for (INT y = start_y; y < end_y; y += i)
              for (INT x = 0; x < Frame.W; x++)
              {
                vec3 color = Scene.Trace(Camera.GetFrameRay(x, y), Scene.Air, 1, rec);
                Frame.PutPixel(x, y, color);
                InvalidateRect(hWnd, nullptr, TRUE);
              }
          });

      // Waiting for all threads
      for (INT i = 1; i <= ThCount; i++)
        Threads[i - 1].join();
    } // End of 'Render' function

    /* Rendering thread handle function.
     * ARGUMENTS:
     *   - thread input pointer:
     *       
     * RETURNS:
     *  (DWORD) thread returns value.
     */
    static DWORD WINAPI RenderThread( __in LPVOID lpParameter )
    {
      raytracer *RT = reinterpret_cast<raytracer *>(lpParameter);
      while (TRUE)
      {
        // Frame draw routine
        RT->timer::Response();
        std::string title = std::format("FPS: {:.1f}. CamLoc: <{:.3f}, {:.3f}, {:.3f}>. CamAt: <{:.3f}, {:.3f}, {:.3f}>, CamUp: <{:.3f}, {:.3f}, {:.3f}>.",
          RT->FPS,
          RT->Camera.Loc[0], RT->Camera.Loc[1], RT->Camera.Loc[2],
          RT->Camera.At[0],  RT->Camera.At[1],  RT->Camera.At[2],
          RT->Camera.Up[0],  RT->Camera.Up[1],  RT->Camera.Up[2]);
        SetWindowText(RT->hWnd, title.c_str());
        // RT->Camera.Rotate(vec3(0, 1, 0), 3);

        // Render frame, save
        RT->Render();
        RT->Frame.SaveTGA();
      }
    } // End of 'RenderThread' function

#pragma endregion

#pragma region Virtual_Callbacks_Overriding

    /* Window initialisation message function.
     * ARGUMNTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID ) override
    {
      Frame.Resize(900, 600);
      Camera.Resize(Frame.W, Frame.H);

      DWORD ThId;
      RenderThreadHandle = CreateThread(0, 0, RenderThread, this, 0, &ThId);
    } // End of 'Init' function

    /* Window message loop Idle virtual callback function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID ) override
    {
    } // End of 'Idle function

    /* Window Resize virtual callback function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID )
    {
      // Calulating size ratio if frame is bigger then screen size
      if (Frame.W > W || Frame.H > H)
      {
        DBL rx = (DBL)W / Frame.W;
        DBL ry = (DBL)H / Frame.H;
        SizeRatio = rx < ry ? rx : ry;
      }
      else
        SizeRatio = 1;

      InvalidateRect(hWnd, nullptr, TRUE);
    } // End of 'Resize function

    /* Ray tracing image painting message function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Paint( HDC hDC ) override
    {
      vec2 start((W - Frame.W * SizeRatio) / 2, (H - Frame.H * SizeRatio) / 2);
      vec2 size(Frame.W * SizeRatio, Frame.H * SizeRatio);

      Frame.Draw(hDC, start[0], start[1], size[0], size[1]);
    } // End of 'Paint' function

    /* Window background Erase virtual callback function.
     * ARGUMENTS:
     *   - DC handler structure:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Erase( HDC hDC ) override
    {
      vec2 
        start((W - Frame.W * SizeRatio) / 2, (H - Frame.H * SizeRatio) / 2),
        size(Frame.W * SizeRatio, Frame.H * SizeRatio),
        end = start + size;
      
      SelectObject(hDC, GetStockObject(NULL_PEN));
      Rectangle(hDC, 0, 0, start[0], H);
      Rectangle(hDC, start[0], 0, end[0], start[1]);
      Rectangle(hDC, end[0], 0, W, H);
      Rectangle(hDC, start[0], end[1], end[0], H);
    } // End of 'win::Erase function

    /* Key click virtual callback function.
      * ARGUMENTS:
      *   - clicked key number:
      *       UINT Key;
      * RETURNS: None.
      */
     VOID KeyPressed( UINT Key ) override
     {
       if (Key == VK_ESCAPE)
       {
         TerminateThread(RenderThreadHandle, 30);
         DestroyWindow(hWnd);
       }

       if (Key == VK_RIGHT)
         Camera.Rotate(vec3(0, 1, 0), -DeltaTime * 30);
       if (Key == VK_LEFT)
         Camera.Rotate(vec3(0, 1, 0), DeltaTime * 30);
       if (Key == VK_DOWN)
         Camera.Rotate(Camera.Right, -DeltaTime * 30);
       if (Key == VK_UP)
         Camera.Rotate(Camera.Right, DeltaTime * 30);

       if (Key == 'W')
         Camera.Move(Camera.Dir * DeltaTime * 5);
       if (Key == 'S')
         Camera.Move(-Camera.Dir * DeltaTime * 5);
       if (Key == 'D')
         Camera.Move(Camera.Right * DeltaTime * 5);
       if (Key == 'A')
         Camera.Move(-Camera.Right * DeltaTime * 5);

       if (Key == VK_SPACE)
         Camera.Move(vec3(0, 1, 0) * DeltaTime * 5);
       if (Key == VK_CONTROL)
         Camera.Move(-vec3(0, 1, 0) * DeltaTime * 5);

       if (Key == 'P')
         Frame.SaveTGA();

       if (Key == '+')
         SizeRatio += 0.1;
       if (Key == '-')
         SizeRatio -= 0.1;
     } // End of 'win::KeyClick' function

#pragma endregion

  }; // End of 'raytracer' class
} // End of 'kirt' namespace

#endif // !__raytracer_h_

// END OF 'raytracer.h' FILE