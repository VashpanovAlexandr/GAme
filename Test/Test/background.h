#define _CRT_SECURE_NO_WARNINGS



#include <glut.h>
#include <string>
#include <fstream>



using namespace std;

typedef unsigned __int16 WORD;

typedef struct {
    WORD   bfType;         // 0x4d42 | 0x4349 | 0x5450
    int    bfSize;         // ������ �����
    int    bfReserved;     // 0
    int    bfOffBits;      // �������� �� ���� ������,
    // ������ 54 = 16 + biSize
    int    biSize;         // ������ �������� � ������:
    // 40(BITMAPINFOHEADER) ��� 108(BITMAPV4HEADER)
    // ��� 124(BITMAPV5HEADER)
    int    biWidth;        // ������ � ������
    int    biHeight;       // ������ � ������
    WORD   biPlanes;       // ������ ������ ���� 1
    WORD   biBitCount;     // 0 | 1 | 4 | 8 | 16 | 24 | 32
    int    biCompression;  // BI_RGB | BI_RLE8 | BI_RLE4 |
    // BI_BITFIELDS | BI_JPEG | BI_PNG
    // ������� ������������ ���� BI_RGB
    int    biSizeImage;    // ���������� ���� � ���� ������
    // ������ ��������������� � 0
    int    biXPelsPerMeter;// �������������� ����������, ����� �� ����
    int    biYPelsPerMeter;// ������������ ����������, ����� �� ����
    int    biClrUsed;      // ���������� ������������ ������
    // (���� ���� ������� ������)
    int    biClrImportant; // ���������� ������������ ������.
    // ����� �������, ������ 0
} BMPheader;

class background {
private :

	

    int* loadBMP(const char* fname, int& mx, int& my, int *v)
    {
        mx = my = -1;
        FILE* f;
        fopen_s(&f, fname, "rb");
        if (!f) return NULL;
        BMPheader bh;    // File header sizeof(BMPheader) = 56
        size_t res;

        // ������ ���������
        res = fread(&bh, 1, sizeof(BMPheader), f);
        if (res != sizeof(BMPheader)) { fclose(f); return NULL; }

        // ��������� ���������
        if (bh.bfType != 0x4d42 && bh.bfType != 0x4349 && bh.bfType != 0x5450) { fclose(f); return NULL; }

        // �������� ������� �����
        fseek(f, 0, SEEK_END);
        int filesize = ftell(f);
        // ����������� ��������� � �����:
        fseek(f, sizeof(BMPheader), SEEK_SET);
        // �������� �������
        if (bh.bfSize != filesize ||
            bh.bfReserved != 0 ||
            bh.biPlanes != 1 ||
            (bh.biSize != 40 && bh.biSize != 108 && bh.biSize != 124) ||
            bh.bfOffBits != 14 + bh.biSize ||

            bh.biWidth < 1 || bh.biWidth >10000 ||
            bh.biHeight < 1 || bh.biHeight>10000 ||
            bh.biBitCount != 24 ||             // ���� ������������� ������ ������������ �����������
            bh.biCompression != 0                // ���� ������������� ������ �������� �����������
            )
        {
            fclose(f);
            return NULL;
        }
        // ��������� �������� � ��������, ��� - ������ (BGR-24), ������� (mx,my) �������
        mx = bh.biWidth;
        my = bh.biHeight;
        int mx3 = (3 * mx + 3) & (-4);    // Compute row width in file, including padding to 4-byte boundary
        unsigned char* tmp_buf = new unsigned  char[mx3 * my];    // ������ ������
        res = fread(tmp_buf, 1, mx3 * my, f);
        if ((int)res != mx3 * my) { delete[]tmp_buf; fclose(f); return NULL; }
        // ������ ���������
        fclose(f);

        // ������� ������ ��� ����������
        v = new int[mx * my];

        // ������� ������ (�� ������� ��� BGR->RGB)
        unsigned char* ptr = (unsigned char*)v;
        for (int y = my - 1; y >= 0; y--) {
            unsigned char* pRow = tmp_buf + mx3 * y;
            for (int x = 0; x < mx; x++) {
                *ptr++ = *(pRow + 2);
                *ptr++ = *(pRow + 1);
                *ptr++ = *pRow;
                pRow += 3;
                ptr++;
            }
        }
        delete[]tmp_buf;
        return v;    // OK
    }
public:
    int coft = 0;

	void load_texture(string filename)
	{
        int mx, my;                              // ��� �������� �����������
        
        int* v = nullptr;
        loadBMP(filename.c_str(), mx, my, v); // �������� ������ � ������ ���� ����

        glBindTexture(GL_TEXTURE_2D, ++coft);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			mx, my,     // ������ ��������
			0, GL_RGB, GL_UNSIGNED_BYTE, v);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        delete[] v;
	}

    void draw(int num)
    {
        glBindTexture(GL_TEXTURE_2D, num); // Set as the current texture
        glBegin(GL_QUADS);
        glTexCoord2d(0.0, 1.0);   glVertex2d(-1.0, -1.0);
        glTexCoord2d(0.0, 0.0);   glVertex2d(-1.0, 1.0);
        glTexCoord2d(1.0, 0.0);   glVertex2d(1.0, 1.0);
        glTexCoord2d(1.0, 1.0);   glVertex2d(1.0, -1.0);
        glEnd();
    }

};
