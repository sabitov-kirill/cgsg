/* Element Size */
#define ELEMENT_H 12
#define ELEMENT_W 12

/* Graphics funktions */
void PutPixel(int x, int y, int r, int g, int b);
void PutElement(int x, int y, int r, int g, int b);

/* Text functions */
void LoadFont(void);
void DrawStr(char* str, int x0, int y0, int r, int g, int b);
void DrawNum(int num, int num_len, int x0, int y0, int r, int g, int b);
void ClearChars(int x0, int y0, int Amount);

/* Game functions */
void GameStart(void);
void FieldInit(void);
void WarmKeyboard(unsigned char Key);