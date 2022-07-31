#include "application.h"

VOID olymp_helper::RequestFakeInputBuffer() {
  http::Request Request{ RequestCodeURL };
  const auto Response = Request.send("GET");
  Reader.parse({ Response.body.begin(), Response.body.end() }, Result);
}

VOID olymp_helper::ResetFakeInputBufferCharIndex() {
  FakeInputCharIndex = 0;
}

VOID olymp_helper::SetTask(INT TaskNumber) {
  ResetFakeInputBufferCharIndex();
  FakeInputBuffer = Result["submitedTasks"][TaskNumber].asString();
}

VOID olymp_helper::SimulateFakeInput() {
  // Check if all ScreenshotBuffer isnt printed already
  if (FakeInputCharIndex >= FakeInputBuffer.size())
    return;

  // Seding fake input
  INPUT input;
  memset(&input, 0, sizeof(input));

  input.type = INPUT_KEYBOARD;
  if (FakeInputBuffer[FakeInputCharIndex] == '\n')
    input.ki.wVk = VK_RETURN;
  else
    input.ki.wScan = FakeInputBuffer[FakeInputCharIndex], input.ki.dwFlags = KEYEVENTF_UNICODE;
  FakeInputCharIndex++;
  SendInput(1, &input, sizeof(INPUT));

  input.ki.dwFlags |= KEYEVENTF_KEYUP;
  SendInput(1, &input, sizeof(INPUT));
}

LRESULT __stdcall olymp_helper::SimulateFakeInputProc(int code, WPARAM wParam, LPARAM lParam) {
  if (code >= 0 && wParam == WM_KEYDOWN) {
    KBDLLHOOKSTRUCT kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

    if (kbdStruct.vkCode == VK_LCONTROL || kbdStruct.vkCode == VK_LSHIFT || kbdStruct.vkCode == VK_OEM_3)
      return CallNextHookEx(MainWindow.SimulateingFakeInputHook, code, wParam, lParam);

    if (!(kbdStruct.flags & LLKHF_INJECTED))
    {
      MainWindow.SimulateFakeInput();
      return 1;
    }
  }

  return CallNextHookEx(MainWindow.SimulateingFakeInputHook, code, wParam, lParam);
}