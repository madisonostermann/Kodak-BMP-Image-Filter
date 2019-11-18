#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;


class BITMAPFILEHEADER               /**** BMP file header structure ****/
{
private:
	unsigned short bfType;           /* Magic number for file */
	unsigned int   bfSize;           /* Size of file */
	unsigned short bfReserved1;      /* Reserved */
	unsigned short bfReserved2;      /* ... */
	unsigned int   bfOffBits;        /* Offset to bitmap data */
public:
	unsigned short GETbfType();
	unsigned long int   GETbfSize();
	int  ReadBmpFileHeader (ifstream &);
	int  WriteBmpFileHeader (ofstream &);
};

#  define BF_TYPE 0x4D42                   /* "MB" */

class  BITMAPINFOHEADER      /**** BMP file info structure ****/
{
private:
	unsigned int   biSize;            /* Size of info header */
	int            biWS;              /* Width of image */
	int            biHS;              /* Height of image */
	unsigned short int biPlanes;      /* Number of color planes */
	unsigned short int biBitCount;    /* Number of bits per pixel */
	unsigned int   biCompression;     /* Type of compression to use */
	unsigned int   biSZ;              /* Size of image data */
	int            biXPelsPerMeter;   /* X pixels per meter */
	int            biYPelsPerMeter;   /* Y pixels per meter */
	unsigned int   biClrUsed;         /* Number of colors used */
	unsigned int   biClrImportant;    /* Number of important colors */
public:
	int            GETbiWS();
	int            GETbiHS();
	unsigned short int GETbiBitCount();
	int  ReadBmpInfoHeader (ifstream &);
	int  WriteBmpInfoHeader (ofstream &);
};

unsigned short BITMAPFILEHEADER::GETbfType(){
	return bfType;
}

unsigned long int   BITMAPFILEHEADER::GETbfSize(){
	return bfSize;
}

int  BITMAPFILEHEADER::ReadBmpFileHeader (ifstream &fp){
	fp.read ((char*)&bfType, sizeof(bfType));
	fp.read ((char*)&bfSize, sizeof(bfSize));
	fp.read ((char*)&bfReserved1, sizeof(bfReserved1));
	fp.read ((char*)&bfReserved2, sizeof(bfReserved2));
	fp.read ((char*)&bfOffBits, sizeof(bfOffBits));
	return 1;
}

int  BITMAPFILEHEADER::WriteBmpFileHeader (ofstream &fp){
	fp.write ((char*)&bfType, sizeof(bfType));
	fp.write ((char*)&bfSize, sizeof(bfSize));
	fp.write ((char*)&bfReserved1, sizeof(bfReserved1));
	fp.write ((char*)&bfReserved2, sizeof(bfReserved2));
	fp.write ((char*)&bfOffBits, sizeof(bfOffBits));
	return 1;
}
int  BITMAPINFOHEADER::GETbiWS(){
	return biWS;
}
int  BITMAPINFOHEADER::GETbiHS(){
	return biHS;
}
unsigned short int BITMAPINFOHEADER::GETbiBitCount(){
	return biBitCount;
}
int  BITMAPINFOHEADER::ReadBmpInfoHeader (ifstream &fp) {
	fp.read ((char*)&biSize, sizeof(biSize));
	fp.read ((char*)&biWS, sizeof(biWS));
	fp.read ((char*)&biHS, sizeof(biHS));
	fp.read ((char*)&biPlanes, sizeof(biPlanes));
	fp.read ((char*)&biBitCount, sizeof(biBitCount));
	fp.read ((char*)&biCompression, sizeof(biCompression));
	fp.read ((char*)&biSZ, sizeof(biSZ));
	fp.read ((char*)&biXPelsPerMeter, sizeof(biXPelsPerMeter));
	fp.read ((char*)&biYPelsPerMeter, sizeof(biYPelsPerMeter));
	fp.read ((char*)&biClrUsed, sizeof(biClrUsed));
	fp.read ((char*)&biClrImportant,  sizeof(biClrImportant));
	return 1;
}
int  BITMAPINFOHEADER::WriteBmpInfoHeader (ofstream &fp){
	fp.write ((char*)&biSize, sizeof(biSize));
	fp.write ((char*)&biWS, sizeof(biWS));
	fp.write ((char*)&biHS, sizeof(biHS));
	fp.write ((char*)&biPlanes, sizeof(biPlanes));
	fp.write ((char*)&biBitCount, sizeof(biBitCount));
	fp.write ((char*)&biCompression, sizeof(biCompression));
	fp.write ((char*)&biSZ, sizeof(biSZ));
	fp.write ((char*)&biXPelsPerMeter, sizeof(biXPelsPerMeter));
	fp.write ((char*)&biYPelsPerMeter, sizeof(biYPelsPerMeter));
	fp.write ((char*)&biClrUsed, sizeof(biClrUsed));
	fp.write ((char*)&biClrImportant,  sizeof(biClrImportant));
	return 1;
}

int main(int argc, char *argv[]) {
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bhd;

	ifstream fp1 (argv[1], ios::in|ios::binary);
	if (!fp1.is_open()){
		cout << "Usage: " << argv[0] << " <input_filename> <output_filename>"<< endl;
		return 1;
	}

	ofstream fp2 (argv[2], ios::out|ios::binary);
	if (!fp2.is_open()){
		cout << "Usage: " << argv[0] << " <input_filename> <output_filename>"<< endl;
		return 1;
	}
	string outputFilename = argv[2];

	int  success = 0;
	success = bfh.ReadBmpFileHeader(fp1) ;
	if (!success)
	{
		/* Couldn't read the file header - return NULL... */
		fp1.close();
		return -1;
	}

	if (bfh.GETbfType() != BF_TYPE)  /* Check for BM reversed, ie MB... */
	{
		cout << "ID is: " <<  bfh.GETbfType() << " Should have been" << 'M'*256+'B';
		cout <<  bfh.GETbfType()/256 << " " <<  bfh.GETbfType()%256 << endl;
		/* Not a bitmap file - return NULL... */
		fp1.close();
		return 1;
	}

	success = 0;
	success = bhd.ReadBmpInfoHeader(fp1);
	if (!success)
	{
		/* Couldn't read the file header - return NULL... */
		fp2.close();
		return -1;
	}

	//take in threshold value from user and return total number of pixels in the file you're writing to
	int thresholdValue;
	cout << "Threshold value for solarization effect [0-255]: ";
	cin >> thresholdValue;
	cout << "Total number of pixels in " << outputFilename <<  ": " << (bhd.GETbiWS())*(bhd.GETbiHS()) << endl;
	
	//write to output file
	bfh.WriteBmpFileHeader(fp2);
	bhd.WriteBmpInfoHeader(fp2);

	//values for red, green and blue
	unsigned char r, g, b;

	//maps to store <0-255, frequency> values for R, G and B of both original and new files
	map<int, int> origR;
        map<int, int> origB;
        map<int, int> origG;
        map<int, int> newR;
        map<int, int> newB;
        map<int, int> newG;

        for (int i=0 ; i < bhd.GETbiWS(); i++){
                for (int j=0 ; j < bhd.GETbiHS(); j++) {
			//read rgb values for each pixel
                        fp1.read ((char*)&r, 1);
                        fp1.read ((char*)&b, 1);
                        fp1.read ((char*)&g, 1);
			//for each value of rgb, increment frequency that value has occured (second value in map pair)
			origR[r]++;
			origB[b]++;
			origG[g]++;
			//calculate solarization effect- can change depending on effect you want to have
                        if(r > thresholdValue){
                               r = 255 - r;
			}
			newR[r]++; //make sure to increment frequency in new file's map as well
                        if(b > thresholdValue){
                               b = 255 - b;
			}
			newB[b]++;
                        if(g > thresholdValue){
                               g = 255 -g;
			}
			newG[g]++;
			//write all of the changed color values to each pixel of the new file
                        fp2.write ((char*)&r, sizeof(char));
                        fp2.write ((char*)&b, sizeof(char));
                        fp2.write ((char*)&g, sizeof(char));
                }
        }

	//write histogram data to a separate file (super long)
	ofstream histogramData;
	outputFilename.append(".txt");
	histogramData.open(outputFilename);
	cout << "Threshold value for solarization effect [0-255]: " << thresholdValue << endl;
        cout << "Total number of pixels in " << outputFilename <<  ": " << (bhd.GETbiWS())*(bhd.GETbiHS()) << endl;
	histogramData << "Histogram data for B:" << endl;
	for(int i=0; i< 256; i++){
		histogramData << i << ": " << origB[i] << " -> " << newB[i] << endl;
	}
	histogramData << "Histogram data for G:" << endl;
        for(int i=0; i< 256; i++){
                histogramData << i << ": " << origG[i] << " -> " << newG[i] << endl;
        }
	histogramData << "Histogram data for R:" << endl;
        for(int i=0; i< 256; i++){
                histogramData << i << ": " << origR[i] << " -> " << newR[i] << endl;
        }
	histogramData.close();

	cout << "The histogram data of " << argv[2] <<  " is written to " << outputFilename << endl;
	fp1.close ();
	fp2.close ();
	return 0;
}
