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

/*
int  solarizationEffect(thresholdValue){
	//calculate histogram data of original file
	//make solarization changes
	//calculate histogram data of new file
	
	//using map container: when b=0, loop and add to counter
	//repeat for b=0-255, then same for r=0-255 and g=0-255
	//3 maps: R, G, B for each photo (original and new)
	//<0-255, frequency>
	map::<int, int> origR;
	int origRCounter = 0;
	map::<int, int> origB;
	int origBCounter = 0;
	map::<int, int> origG;
	int origGCounter = 0;
	map::<int, int> newR;
	int newRCounter = 0;
	map::<int, int> newB;
	int newBCounter = 0;
	map::<int, int> newG;
	int newGCounter = 0;

	for (int i=0 ; i < bhd.GETbiWS(); i++){
                for (int j=0 ; j < bhd.GETbiHS(); j++) {
                        fp1.read ((char*)&r, 1);
			fp1.read ((char*)&b, 1);
                        fp1.read ((char*)&g, 1);
			origR[r]= origRCounter++;
			origB[b]= origBCounter++;
			orifG[g]= origGCounter++;
			//might need to deal with difference between orig r and new r
			//for printing purposes in here
			if(r > thresholdValue)
				r = 255 - r;
			if(b > thresholdValue)
				b = 255 - b;
			if(g > thresholdValue)
				g = 255 -g;
			fp2.write ((char*)&r, sizeof(char));
			fp2.write ((char*)&b, sizeof(char));
			fp2.write ((char*)&g, sizeof(char));
		}
	}
	return 1;

}
*/

int main(int argc, char *argv[]) {
	//TODO
	//Clean up print statements
	//try to have solarizationEffect() method work with parameter being passed in (make sure to update contents first)
	//figure out how to print output file name
	
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

	int thresholdValue;

	cout << "Threshold value for solarization effect [0-255]:";
	cin >> thresholdValue;
	cout << "Total number of pixels in " << argv[2] <<  ": " << (bhd.GETbiWS())*(bhd.GETbiHS()) << endl;

	
	bfh.WriteBmpFileHeader(fp2);
	bhd.WriteBmpInfoHeader(fp2);
	unsigned char r, g, b;

	//solarizationEffect(thresholdValue);
	map<int, int> origR;
        int origRCounter = 0;
        map<int, int> origB;
        int origBCounter = 0;
        map<int, int> origG;
        int origGCounter = 0;
        map<int, int> newR;
        int newRCounter = 0;
        map<int, int> newB;
        int newBCounter = 0;
        map<int, int> newG;
        int newGCounter = 0;

        for (int i=0 ; i < bhd.GETbiWS(); i++){
                for (int j=0 ; j < bhd.GETbiHS(); j++) {
                        fp1.read ((char*)&r, 1);
                        fp1.read ((char*)&b, 1);
                        fp1.read ((char*)&g, 1);
                        origR[r]= origRCounter++;
                        origB[b]= origBCounter++;
                        origG[g]= origGCounter++;
                        //might need to deal with difference between orig r and new r
                        //for printing purposes in here
                        if(r > thresholdValue){
                                r = 255 - r;
			}
			newR[r] = newRCounter++;
                        if(b > thresholdValue){
                                b = 255 - b;
			}
			newB[b] = newBCounter++;
                        if(g > thresholdValue){
                                g = 255 -g;
			}
			newG[g] = newGCounter++;
                        fp2.write ((char*)&r, sizeof(char));
                        fp2.write ((char*)&b, sizeof(char));
                        fp2.write ((char*)&g, sizeof(char));
                }
        }


	cout << "The histogram data of " << argv[2] <<  " is written to " << argv[2] <<  ".txt" << endl;

	fp1.close ();
	fp2.close ();
	return 0;
}
