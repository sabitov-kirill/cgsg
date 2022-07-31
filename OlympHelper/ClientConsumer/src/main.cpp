#include "application.h"
#include "cmd/arguments_parser.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShouldShow) {
  cmd_arguments_parser Args;
  std::string UserName;
  if ((UserName = Args.GetCmdOption("-u")) != "")
    MainWindow.SetUserName(UserName);

  MainWindow.Run();
  return 0;
}