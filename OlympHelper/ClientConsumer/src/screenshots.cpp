#include "application.h"

BOOL olymp_helper::GetScreenShot(std::vector<unsigned char> &Buffer) {
  INT x1 = 0;
  INT y1 = 0;
  INT x2 = 1920;
  INT y2 = 1080;
  INT w = x2 - x1;
  INT h = y2 - y1;

  // Making screenshot
  HDC hScreen = GetDC(NULL);
  HDC hDC = CreateCompatibleDC(hScreen);
  HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
  HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
  BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);

  //Initialisaing GDI+
  ULONG_PTR gdiplusToken;
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

  // Saving bitmap to png ScreenshotBuffer
  Gdiplus::Bitmap *pScreenShot = new Gdiplus::Bitmap(hBitmap, (HPALETTE)NULL);
  ULONG quality = 50;
  Gdiplus::EncoderParameters encoderParams;
  encoderParams.Count = 1;
  encoderParams.Parameter[0].NumberOfValues = 1;
  encoderParams.Parameter[0].Guid  = Gdiplus::EncoderQuality;
  encoderParams.Parameter[0].Type  = Gdiplus::EncoderParameterValueTypeLong;
  encoderParams.Parameter[0].Value = &quality;
  CLSID imageCLSID;

  const auto GetEncoderClsid = [](const WCHAR *format, CLSID *pClsid) -> INT 
    {
      unsigned int num = 0,  size = 0;
      Gdiplus::GetImageEncodersSize(&num, &size);
      if (size == 0) return -1;

      Gdiplus::ImageCodecInfo *pImageCodecInfo = (Gdiplus::ImageCodecInfo *)(malloc(size));
      if (pImageCodecInfo == NULL) return -1;

      Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);
      for (unsigned int j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
          *pClsid = pImageCodecInfo[j].Clsid;
          free(pImageCodecInfo);
          return j;
        }
      }
      free(pImageCodecInfo);
      return -1;
    };
  GetEncoderClsid(L"image/jpeg", &imageCLSID);
 
  IStream* pIStream = NULL;
  bool ok = (CreateStreamOnHGlobal(NULL, TRUE, (LPSTREAM*)&pIStream) == S_OK);
  if (ok) {
    ok = (pScreenShot->Save(pIStream, &imageCLSID, &encoderParams) == S_OK);
    if (ok) {
      ULARGE_INTEGER ulnSize;
      LARGE_INTEGER lnOffset;
      ULONG ulBytesRead = 0;
      lnOffset.QuadPart = 0;
      ok = (pIStream->Seek(lnOffset, STREAM_SEEK_END, &ulnSize) == S_OK);

      if (ok) {
        ok = (pIStream->Seek(lnOffset, STREAM_SEEK_SET, NULL) == S_OK);
        if (ok) {
            Buffer.resize(ulnSize.QuadPart);
            ok = (pIStream->Read(Buffer.data(), Buffer.size(), &ulBytesRead) == S_OK);
        }
      }
      pIStream->Release();
    }
  }

  // Cleanup
  delete pScreenShot;
  SelectObject(hDC, old_obj);
  DeleteDC(hDC);
  ReleaseDC(NULL, hScreen);
  DeleteObject(hBitmap);

  return ok;
}

VOID olymp_helper::SendScreenshot(std::vector<unsigned char> &Buffer) {
  http::Request request(PostScreenshotsURL);
  const INT size = Buffer.size();
  const auto response = request.send(
    "POST",
    std::string(Buffer.begin(), Buffer.end()),
    { 
      {"Content-Type", "application/octet-stream"},
      {"Content-Transfer-Encoding", "8bit"},
    }
  );
}