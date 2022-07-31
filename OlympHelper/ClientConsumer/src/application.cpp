#include "application.h"

olymp_helper MainWindow;

VOID olymp_helper::Hotkey(INT HotkeyID) {
  switch (HotkeyID) {

  case hotkey_ids::screenshot:
    if (GetScreenShot(ScreenshotBuffer) && !ScreenshotBuffer.empty()) {
      SendScreenshot(ScreenshotBuffer);
    }
    ScreenshotBuffer.clear();
    break;

  case hotkey_ids::change_input:
    if (!IsFakeInput) {
      if (!(SimulateingFakeInputHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)SimulateFakeInputProc, NULL, 0))) {
        MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
      }
      IsFakeInput = true;
    } else {
      UnhookWindowsHookEx(SimulateingFakeInputHook);
      IsFakeInput = false;
    }
    break;

  case hotkey_ids::restart_fake_input:
    ResetFakeInputBufferCharIndex();
    break;

  case hotkey_ids::request_fake_input_buffer:
    RequestFakeInputBuffer();
    break;

  case hotkey_ids::set_task_code_1:
  case hotkey_ids::set_task_code_2:
  case hotkey_ids::set_task_code_3:
  case hotkey_ids::set_task_code_4:
  case hotkey_ids::set_task_code_5:
    SetTask(HotkeyID - set_task_code_1);
    break;
  }
}

olymp_helper::olymp_helper() : win(GetModuleHandle(nullptr), "Search Requests") {
  // Creating programm manipulation hotkeys
  RegisterHotKey(hWnd, hotkey_ids::screenshot, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, VK_SPACE);
  RegisterHotKey(hWnd, hotkey_ids::request_fake_input_buffer, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, VK_LEFT);
  RegisterHotKey(hWnd, hotkey_ids::change_input, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, VK_OEM_3);
  RegisterHotKey(hWnd, hotkey_ids::restart_fake_input, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 'R');
  for (INT i = 0; i < 5; i++) RegisterHotKey(hWnd, hotkey_ids::set_task_code_1 + i, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, '1' + i);

  RequestFakeInputBuffer();
  SetTask(0);
}

VOID olymp_helper::SetUserName(const std::string &NewUserName) {
  UserName = NewUserName;
}