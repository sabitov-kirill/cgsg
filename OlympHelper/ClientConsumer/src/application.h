#include <vector>
#include <string>
#include <algorithm>
#include <json/json.h>
#include <HTTPRequest.hpp>

#include <COMMONDF.H>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#include "win/win.h"

#ifndef __application_h_
#define __application_h_

class olymp_helper : public win {
private:
  //
  // Network data
  //
#ifdef    _DEBUG
  const std::string ServerURL = "http://localhost:5000/api";
#else  // _DEBUG
  const std::string ServerURL = "http://a0644367.xsph.ru/api";
#endif // RELEASE
  const std::string RequestCodeURL = ServerURL + "/task/request";
  const std::string PostScreenshotsURL = ServerURL + "/task/screenshot";
  std::string UserName;
  Json::Value Result;
  Json::Reader Reader;

  //
  // Fake input handle
  //
  HHOOK SimulateingFakeInputHook;
  std::string FakeInputBuffer;
  INT FakeInputCharIndex = 0;
  BOOL IsFakeInput = false;

  VOID RequestFakeInputBuffer();
  VOID ResetFakeInputBufferCharIndex();
  VOID SetTask(INT TaskNumber);
  VOID SimulateFakeInput();
  static LRESULT __stdcall SimulateFakeInputProc(int code, WPARAM wParam, LPARAM lParam);

  //
  // Screenshots handle
  //
  std::vector<unsigned char> ScreenshotBuffer;

  BOOL GetScreenShot(std::vector<unsigned char> &Buffer);
  VOID SendScreenshot(std::vector<unsigned char> &Buffer);

  //
  // Hotkeys rections
  //
  enum hotkey_ids{
    screenshot,
    change_input,
    restart_fake_input,
    request_fake_input_buffer,
    set_task_code_1,
    set_task_code_2,
    set_task_code_3,
    set_task_code_4,
    set_task_code_5,
  };

  VOID Hotkey(INT HotkeyID) override;

public:
  olymp_helper();

  VOID SetUserName(const std::string &NewUserName);
};

extern olymp_helper MainWindow;

#endif // __application_h_