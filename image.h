#include <fstream> //áèáëèîòåêà äëÿ ðàáîòû ñ ôàéëàìè
#include <iostream> 
using namespace std;
//k
struct Color { //îòâå÷àåò çà ïèêñåëè
    unsigned char red, green, blue; //áåççíàêîâûå ñèìâîëû
    bool operator == (Color& color) { //ñðàâíåíèå äâóõ ïèêñåëåé
        return red == color.red &&
            blue == color.blue && green == color.green;
    }
    void grey() {
        red = 0.2126 * red + 0.0722 * blue + 0.7152 * green;
        blue = green = red;
    }
    void aver() {
        red = (red + blue + green) / 3;
        green = red;
        blue = red;
    }
    int averValue() {
        return (red + blue + green) / 3;
    }
    void sepia() {
        red = averValue();
        if (red < 216) {
            green = red + 20;
            blue = red + 40;
        }
        else {
            blue = 255;
            green = red + (blue - red) / 2;
        }
    }
    void invert() {
        red = 255 - red;
        green = 255 - green;
        blue = 255 - blue;
    }
};
const short INT = 4;
const short WORD = 2;

typedef unsigned __int16 word;

struct BMPheader { //ñòðêóòóðà çàãîëîâêà ôîòî
    word signature; //2 0x4d42 | 0x4349 | 0x5450
    int fileSize;   //4 
    int reserved;   //4 
    int dataOffset; //4 54 = 16 + fileSize
    int size;       //4 size in bytes
    int width;          //4 !!
    int height;         //4 !!
    word planes;        //2 ==1
    word bitsPerPixel;  //2 ==24
    int compression;    //4
    int imageSize;      //4 image size in bytes
    int XpixelsPerM;    //4 horizontal resolution, dots in inch
    int YpixelsPerM;    //4 vertical resolution, dots in inch
    int ColorUsed;      //4 
    int ColorImportant; //4 
    void Print(ostream& fout) { //ñîçäàíèå çàãîëîâêà íîâîé ôîòîãðàôèè
        fout.write((char*)&signature, WORD); //2
        fout.write((char*)&fileSize, INT); //4
        fout.write((char*)&reserved, INT);
        fout.write((char*)&dataOffset, INT);
        fout.write((char*)&size, INT);
        fout.write((char*)&width, INT);
        fout.write((char*)&height, INT);
        fout.write((char*)&planes, WORD);
        fout.write((char*)&bitsPerPixel, WORD);
        fout.write((char*)&compression, INT);
        fout.write((char*)&imageSize, INT);
        fout.write((char*)&XpixelsPerM, INT);
        fout.write((char*)&YpixelsPerM, INT);
        fout.write((char*)&ColorUsed, INT);
        fout.write((char*)&ColorImportant, INT);
    }
};

class Image {
    BMPheader h; //çàãîëîâîê ôîòî
    Color** pixels; //ìàòðèöà ïèêñåëåé
public:
    Image(string fileName) { //êîíñòðóêòîð ïî ôàéëó (ñ÷èòûâàåò ñ ôàéëà)
        ifstream fin(fileName, ios::binary);
        fin.seekg(0);
        fin.read((char*)&h.signature, WORD);
        fin.read((char*)&h.fileSize, INT);
        fin.read((char*)&h.reserved, INT);
        fin.read((char*)&h.dataOffset, INT);
        fin.read((char*)&h.size, INT);
        fin.read((char*)&h.width, INT);
        fin.read((char*)&h.height, INT);
        fin.read((char*)&h.planes, WORD);
        fin.read((char*)&h.bitsPerPixel, WORD);
        fin.read((char*)&h.compression, INT);
        fin.read((char*)&h.imageSize, INT);
        fin.read((char*)&h.XpixelsPerM, INT);
        fin.read((char*)&h.YpixelsPerM, INT);
        fin.read((char*)&h.ColorUsed, INT);
        fin.read((char*)&h.ColorImportant, INT);


        pixels = new Color * [h.height]; //äèíàìè÷åñêàÿ ïàìÿòü ïîä ìàòðèöó ïèêñèëåé
        int r = (h.width * sizeof(Color)) % 4; //ñêîëüêî 0 â êîíöå ñòðîêè
        int nBytes = r ? 4 - r : 0; //if r == 0
        //pixel reading
        for (int i = 0; i < h.height; i++) {
            pixels[i] = new Color[h.width];
            fin.read((char*)pixels[i], sizeof(Color) * h.width);
            fin.seekg(nBytes, ios::cur); //ïðîïóñòèòü íåíóæíûå áèòû
        }
    }

    void Print() { //âûâîä èíôîðìàöèè î ôîòî
        cout << "Signature: " << h.signature << endl;
        cout << "File size: " << h.fileSize << endl;
        cout << "Offset: " << h.dataOffset << endl;
        cout << "Width: " << h.width << endl;
        cout << "Height: " << h.height << endl;
        cout << "Planes: " << h.planes << endl;
        cout << "BitsPerPixel: " << h.bitsPerPixel << endl;
        cout << "Compression: " << h.compression << endl;
        cout << "biSize or size: " << h.size << endl;
        cout << "size image: " << h.imageSize << endl;
        cout << sizeof(Color) << endl;
    }
    int getWidth() { //ãåòòåðû êëàññîâ
        return h.width;
    }
    int getHeight() {
        return h.height;
    }
    void Save(string& fileName) { //ñîõðàíåíèå íîâîãî ôàéëà
        ofstream fout(fileName, ios::binary); //îòêðûòü ôàéë äëÿ çàïèñè
        // print BMP file header
        h.Print(fout); //ñîõðàíèòü â ôàéë

        // creating '0' to append to the end of BMP file lines
        int r = (h.width * sizeof(Color)) % 4;
        int nBytes = r ? 4 - r : 0;
        char* temp = new char[nBytes];
        for (int i = 0; i < nBytes; i++) temp[i] = 0;

        // pixel printing
        for (int i = 0; i < h.height; i++) {
            for (int j = 0; j < h.width; j++) {
                fout.write((char*)&pixels[i][j], sizeof(Color));
            }
            // add nBytes '0' to the end
            fout.write(temp, nBytes);
        }
    }
    void SaveHorisontalSelect(int h1, string fileName1, string fileName2) {
        ofstream fout1(fileName1, ios::binary);
        ofstream fout2(fileName2, ios::binary);

        // creating '0' to append to the end of BMP file lines
        int r = (h.width * sizeof(Color)) % 4;
        int nBytes = r ? 4 - r : 0;
        char* temp = new char[nBytes];
        for (int i = 0; i < nBytes; i++) temp[i] = 0;
        int h2 = h.height - h1;
        //change in BMP file header for first photo
        h.fileSize = ((h.width * 3) + r) * h1 + h.dataOffset;
        h.imageSize = ((h.width * 3) + r) * h1;
        h.height = h1;
        // print BMP file header
        h.Print(fout1);

        //change in BMP file header for second photo
        h.fileSize = ((h.width * 3) + r) * h2 + h.dataOffset;
        h.imageSize = ((h.width * 3) + r) * h2;
        h.height = h2;
        // print BMP file header
        h.Print(fout2);

        // pixel printing for first photo
        for (int i = 0; i < h1; i++) {
            for (int j = 0; j < h.width; j++) {
                fout1.write((char*)&pixels[i][j], sizeof(Color));
            }
            // add nBytes '0' to the end
            fout1.write(temp, nBytes);
        }

        // pixel printing for second photo
        for (int i = h1; i < h1 + h2; i++) {
            for (int j = 0; j < h.width; j++) {
                fout2.write((char*)&pixels[i][j], sizeof(Color));
            }
            // add nBytes '0' to the end
            fout2.write(temp, nBytes);
        }
    }
    void SaveVerticalSelect(int w1, string fileName1, string fileName2) {
        ofstream fout1(fileName1, ios::binary);
        ofstream fout2(fileName2, ios::binary);

        int w2 = h.width - w1;

        // for first photo

        // creating '0' to append to the end of BMP file lines
        int r = (w1 * sizeof(Color)) % 4;
        int nBytes = r ? 4 - r : 0;
        char* temp = new char[4];
        for (int i = 0; i < nBytes; i++) temp[i] = 0;

        //change in BMP file header
        h.fileSize = ((w1 * 3) + r) * h.height + h.dataOffset;
        h.imageSize = ((w1 * 3) + r) * h.height;
        h.width = w1;
        // print BMP file header
        h.Print(fout1);

        // pixel printing 
        for (int i = 0; i < h.height; i++) {
            for (int j = 0; j < w1; j++) {
                fout1.write((char*)&pixels[i][j], sizeof(Color));
            }
            // add nBytes '0' to the end
            fout1.write(temp, nBytes);
        }

        // for second photo

        // creating '0' to append to the end of BMP file lines
        r = (w2 * sizeof(Color)) % 4;
        nBytes = r ? 4 - r : 0;

        //change in BMP file header
        h.fileSize = ((w2 * 3) + r) * h.height + h.dataOffset;
        h.imageSize = ((w2 * 3) + r) * h.height;
        h.width = w2;
        // print BMP file header
        h.Print(fout2);

        // pixel printing 
        for (int i = 0; i < h.height; i++) {
            for (int j = w1; j < w1 + w2; j++) {
                fout2.write((char*)&pixels[i][j], sizeof(Color));
            }
            // add nBytes '0' to the end
            fout2.write(temp, nBytes);
        }
    }
    void blur(int blurSize) { // "Ðàçìûòèå" ñ èçìåíÿåìîé îáëàñòüþ(ñèëîé)
        int avgR, avgB, avgG, n;
        for (int xx = 0; xx < h.width; xx++) {
            for (int yy = 0; yy < h.height; yy++) {
                avgB = avgG = avgR = 0;
                n = 0;
                for (int x = xx; (x < h.width) && (x < (xx + blurSize)); x++) {
                    for (int y = yy; (y < h.height) && (y < (yy + blurSize)); y++) {
                        avgB += pixels[y][x].blue;
                        avgG += pixels[y][x].green;
                        avgR += pixels[y][x].red;
                        n++;
                    }
                }
                avgB = avgB / n;
                avgG = avgG / n;
                avgR = avgR / n;
                pixels[yy][xx].blue = avgB;
                pixels[yy][xx].green = avgG;
                pixels[yy][xx].red = avgR;
            }
        }
        for (int xx = h.width - 1; xx >= 0; xx--) {
            for (int yy = h.height - 1; yy >= 0; yy--) {
                avgB = avgG = avgR = 0;
                n = 0;
                for (int x = xx; (x >= 0) && (x > (xx - blurSize)); x--) {
                    for (int y = yy; (y >= 0) && (y > (yy - blurSize)); y--)
                    {
                        avgB += pixels[y][x].blue;
                        avgG += pixels[y][x].green;
                        avgR += pixels[y][x].red;
                        n++;
                    }
                }
                avgB = avgB / n;
                avgG = avgG / n;
                avgR = avgR / n;
                pixels[yy][xx].blue = avgB;
                pixels[yy][xx].green = avgG;
                pixels[yy][xx].red = avgR;
            }
        }
    }

    void Grey(string& fileName) {
        ofstream fout(fileName, ios::binary);
        // print BMP file header
        h.Print(fout);

        // creating '0' to append to the end of BMP file lines
        int r = (h.width * sizeof(Color)) % 4;
        int nBytes = r ? 4 - r : 0;
        char* temp = new char[nBytes];
        for (int i = 0; i < nBytes; i++) temp[i] = 0;

        // pixel printing
        for (int i = 0; i < h.height; i++) {
            for (int j = 0; j < h.width; j++) {
                pixels[i][j].grey();
                fout.write((char*)&pixels[i][j], sizeof(Color));
            }
            // add nBytes '0' to the end
            fout.write(temp, nBytes);
        }
    }

    void turn_left(string& fileName) {
        int height = h.height;
        int width = h.width;
        h.width = height;
        h.height = width;
        ofstream fout(fileName, ios::binary);
        // print BMP file header
        h.Print(fout);

        // creating '0' to append to the end of BMP file lines
        int r = (h.width * sizeof(Color)) % 4;
        int nBytes = r ? 4 - r : 0;
        char* temp = new char[nBytes];
        for (int i = 0; i < nBytes; i++) temp[i] = 0;

        for (int i = 0; i < width; i++) {
            for (int j = height - 1; j >= 0; j--) {
                fout.write((char*)&pixels[j][i], sizeof(Color));
            }
            fout.write(temp, nBytes);
        }
    }

    void turn_right(string& fileName) {
        int height = h.height;
        int width = h.width;
        h.width = height;
        h.height = width;
        ofstream fout(fileName, ios::binary);
        // print BMP file header
        h.Print(fout);

        // creating '0' to append to the end of BMP file lines
        int r = (h.width * sizeof(Color)) % 4;
        int nBytes = r ? 4 - r : 0;
        char* temp = new char[nBytes];
        for (int i = 0; i < nBytes; i++) temp[i] = 0;

        for (int i = width - 1; i >= 0; i--) {
            for (int j = 0; j < height; j++) {
                fout.write((char*)&pixels[j][i], sizeof(Color));
            }
            fout.write(temp, nBytes);
        }
    }

    void Invert(string& fileName) {
        ofstream fout(fileName, ios::binary);
        // print BMP file header
        h.Print(fout);

        // creating '0' to append to the end of BMP file lines
        int r = (h.width * sizeof(Color)) % 4;
        int nBytes = r ? 4 - r : 0;
        char* temp = new char[nBytes];
        for (int i = 0; i < nBytes; i++) temp[i] = 0;

        // pixel printing
        for (int i = 0; i < h.height; i++) {
            for (int j = 0; j < h.width; j++) {
                pixels[i][j].invert();
                fout.write((char*)&pixels[i][j], sizeof(Color));
            }
            // add nBytes '0' to the end
            fout.write(temp, nBytes);
        }
    }
    void Flip(string& filename) {
        ofstream fout(filename, ios::binary);
        // print BMP file header
        h.Print(fout);

        // creating '0' to append to the end of BMP file lines
        int r = (h.width * sizeof(Color)) % 4;
        int nBytes = r ? 4 - r : 0;
        char* temp = new char[nBytes];
        for (int i = 0; i < nBytes; i++) temp[i] = 0;

        // pixel printing
        for (int i = h.height - 1; i >= 0; i--) {
            for (int j = h.width - 1; j >= 0; j--) {
                fout.write((char*)&pixels[i][j], sizeof(Color));
            }
            // add nBytes '0' to the end
            fout.write(temp, nBytes);
        }
    }
    void Mirror(string& filename) {
        ofstream fout(filename, ios::binary);
        // print BMP file header
        h.Print(fout);

        // creating '0' to append to the end of BMP file lines
        int r = (h.width * sizeof(Color)) % 4;
        int nBytes = r ? 4 - r : 0;
        char* temp = new char[nBytes];
        for (int i = 0; i < nBytes; i++) temp[i] = 0;

        // pixel printing
        for (int i = 0; i < h.height; i++) {
            for (int j = h.width - 1; j >= 0; j--) {
                fout.write((char*)&pixels[i][j], sizeof(Color));
            }
            // add nBytes '0' to the end
            fout.write(temp, nBytes);
        }
    }
    void Sepia(string& fileName) {
        ofstream fout(fileName, ios::binary);
        // print BMP file header
        h.Print(fout);

        // creating '0' to append to the end of BMP file lines
        int r = (h.width * sizeof(Color)) % 4;
        int nBytes = r ? 4 - r : 0;
        char* temp = new char[nBytes];
        for (int i = 0; i < nBytes; i++) temp[i] = 0;

        // pixel printing
        for (int i = 0; i < h.height; i++) {
            for (int j = 0; j < h.width; j++) {
                pixels[i][j].sepia();
                fout.write((char*)&pixels[i][j], sizeof(Color));
            }
            // add nBytes '0' to the end
            fout.write(temp, nBytes);
        }
    }
};
