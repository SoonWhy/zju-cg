

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);

void texload(int i, char *filename, GLuint texture[]);
void inittexture();

void drawBottomCube();
void drawBackCube();
void drawRightCube();
void drawLeftCube();
void drawFrontCube();
void drawTopCube();

void Draw_Hero();
void Control_Hero();

void Draw_NPC();
void Control_NPC();
