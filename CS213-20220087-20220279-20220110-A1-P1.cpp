// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: 				filters editor .cpp
// Last Modification Date:	10/10/2023
// Author1 and ID and Group:	Belal Mohamed Youness - 20220087 - email : belalyouness494@gmail.com
// Author2 and ID and Group:	Hossam Mohsen Hassan - 20220110 - email : fc22hossam@gmail.com
// Author3 and ID and Group:	Mohamed Ahmed Ali - 20220279 - email : Derballa2004@gmail.com
// Teaching Assistant:		xxxxxxxxxx
// Purpose:A C++ code to apply 6 filters on gray scale images, and can do it for several times on the same image.


#include <iostream>
#include <cmath>
#include <cstring>
#include "bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE];  //declaring image as a char [256][256]
unsigned char image2[SIZE][SIZE]; //declaring second image for filter # 5
char imagefilename [100]; // declaring a char size 100 to name the saved images
char process ; // integer for filter input numbers
//==========================================================================================================
void load(); //load the image to begin editing
void loadtwo(); //load a second image for merging
void save(); //saving image finished in the folder with name (imagefilename)
void bw(); // black and white filter
void inverse(); // inverse filter
void merge(); // merge 2 photos filter
void fliphz(); // flip horizontally filter
void flipvt(); //flip vertically filter
void rotate(); // rotate image filter
void darken(); // darken image by 50%
void lighten(); //lighten image by 50%
void detectedges(); // detect image edges, make them black and the rest white
void enlarge(); // choosing one of image quarters and enlarge its scale
void shrink_quarter(); // shrinking image to fourth its original scale
void shrink_half(); // shrinking image to half its original scale
void shrink_third(); // shrinking image to third its original scale
void mrrleft(); //mirrors left half of the image
void mrrright(); //mirrors right half of the image
void mrrupper(); //mirrors upper half of the image
void mrrlower(); //mirrors lower half of the image
void shuffle(); // divides image into 4 quarters and shuffle them by users order
void blur(); // make blur edit as bury version of the image
//==========================================================================

int main()
{
    cout<<"Hey user ;) \n"
        <<"Select a filter from the following : \n"
        <<"1- Black and White\n"
        <<"2- Inverse\n"
        <<"3- Merge\n"
        <<"4- Flip (Horizontal / Vertical)\n"
        <<"5- Rotate\n"
        <<"6- Darken or Lighten \n"
        <<"7- Detect Image Edges\n"
        <<"8- enlarge\n"
        <<"9- shrink\n"
        <<"a- mirror\n"
        <<"b- shuffle\n"
        <<"c- blur\n"
    load();

    start:; //respawning to the beginning menu point

    cout<<"Enter the required filter : \n";
    cin>>process;

    //=================================================================

    switch(process){ // switch for filters and functions . every case contains save function

        case '1':
            bw();
            save();
            break;
        case '2':
            inverse();
            save();
            break;
        case '3':
            merge();
            save();
            break;
        case '4':
            char x;
            cout<<"would you like to flip the image in a horizontal or vertical way (H/V) ?";
            cin>> x;
            if (x == 'V'|| x == 'v') // if condition to allow the user to choose vertical flip or horizontal flip
                flipvt();
            else
                fliphz();
            save();
            break;
        case '5':
            rotate();
            save();
            break;
        case '6':
            char y;
            cout<<"would you darken or lighten the image (D/L) ?";
            cin>>y;
            if(y == 'D'||y=='d') // if condition to allow the user to choose between the dark or light effect
                darken();
            else
                lighten();
            save();
            break;
        case '7':
            detectedges();
            save();
            break;
        case '8':
            enlarge();
            save();
            break;
        case '9':
            int s;
            cout<<"input scale of shrink (1. 1/2 , 2. 1/3 , 3. 1/4)\n";
            cin>>s;
            if(s==1)
                shrink_half();
            else if (s==2)
                shrink_third();
            else
                shrink_quarter();
            save();
            break;
        case 'a':
            int q;
            cout<<"enter the quarter you want to edit [left, right, upper or lower] half (1,2,3,4) ? : ";
            cin>>q;
            if (q==1)
                mrrleft();
            else if (q==2)
                mrrright();
            else if (q==3)
                mrrupper();
            else
                mrrlower();
            save();
            break;
        case 'b':
            shuffle();
            save();
            break;
        case 'c':
            blur();
            save();
            break;
            char w;
            cout<<"Do you want to add another filter ?(Y,N): \n";cin>>w;

            if(w == 'Y'|| w== 'y') // if condition offering the user to continue editing or exit
                goto start; // function to regenerate the menu for another filter
            else
                cout<<"sharftena ya 2amr. ";
            return 0;
    }
// temp integer = temporary images to make the algorithms easier
    void load () {

        char imagefilename[100];
        cout << "Enter the source image file name :  \n";
        cin >> imagefilename;
        strcat (imagefilename, ".bmp"); // adding .bmp to name entered to make it an image file
        readGSBMP(imagefilename, image); // reads the image from the file specified by filename in a specific folder
    }
    void loadtwo () { //same as load() for second image in merge filter

        char imagefilename[100];
        cout << "Enter the second source image file name :  \n";
        cin >> imagefilename;
        strcat(imagefilename, ".bmp");
        readGSBMP(imagefilename, image2);
    }
    void save () { //function to save the edited image

        char imagefilename[100];
        cout << "Name the file :  \n";
        cin >> imagefilename;
        strcat (imagefilename, ".bmp");// adding .bmp to name entered to make it an image file
        writeGSBMP(imagefilename, image); // saving image with the name user entered and apply it as [256][256] image
    }

    void bw() { // 127 is the midpoint between black and white , so we make a black and white with a simple code

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                if (image[i][j] > 127)
                    image[i][j] = 255;
                else
                    image[i][j] = 0;
            }
        }
    }
    void inverse () { // getting the adding inverse of gray scale

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = 255 - image[i][j];
            }
        }
    }
    void merge() { // adding two images and getting the avg between their pixels

        loadtwo();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image[i][j]= (image[i][j] + image2[i][j])/2;
            }
        }
    }
    void fliphz() {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if(i>=127 && j>=127) {  // declaring a temporary image and flipping its  2 quarters then the second ones
                    int temp = image[i][j];
                    image[i][j] = image[255-i][j];
                    image[255-i][j] = temp ;
                }
                else if(i<127 && j<127){ // if loop for the second quarters
                    int temp = image[i][j];
                    image[i][j] = image[255-i][j];
                    image[255-i][j] = temp;
                }
            }
        }
    }

    void flipvt() { // same as flip hz() but in a vertical way

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (i >= 127 && j >= 127) {
                    int temp = image[i][j];
                    image[i][j] = image[i][255 - j];
                    image[i][255 - j] = temp;
                } else if (i < 127 && j < 127) {
                    int temp = image[i][j];
                    image[i][j] = image[i][255 - j];
                    image[i][255 - j] = temp;
                }
            }
        }
    }
    void rotate (){

        int y;
        int z;
        int temp [SIZE][SIZE]; // declaring a temporary image
        cout<<"Please enter the degree of rotation (90 , 180 , 270) :  ";
        cin>>y ;
        if(y == 90) // if loop for choosing the user rotation degree
            z = 1;
        else if(y==180)
            z = 2;
        else if(y == 270)
            z = 3;
        else
            z = 4;
        while(z--){ // using simple math equation for pixels interchange to get image[255-j][i] pixels muck in with temp[i][j]
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    temp [i][j]= image [i][j];
                }}
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image [i][j]= temp[255-j][i];
                }
            }
        }
    }

    void lighten() {
// lighten image by average this way to be more accurate than adding scale bits
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image[i][j]=(255+image[i][j])/2;
            }
        }
    }
    void darken () {
// darken image by average this way to be more accurate than subtracting scale bits
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image[i][j]=(image[i][j]/2);
            }
        }
    }
    void detectedges() {
        //using an average black and white filter to get the basic image objects then highlight its edges by
        // if loop for the difference of black and white pixels

        int s = 0;
        int avg;
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                s += image[i][j];
            }
        }
        avg = (s / 256) / 255;
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                if (image[i][j] <= avg)
                    image[i][j] = 0;
                else
                    image[i][j] = 255;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if ((abs(image[i][j] - image[i][j + 1]) >= 200) || (abs(image[i][j] - image[i + 1][j]) >= 200)) {
                    image[i][j] = 0;
                } else
                    image[i][j] = 255;
            }
        }
    }

    void enlarge (){
        unsigned char temp[SIZE][SIZE];
        int s;
        cout<<"input quarter you want to enlarge (1,2,3,4) : \n";
        cin>>s;

        if (s == 1) {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE / 2; j++) {
                    temp[2 * i][2 * j] = image[i][j];
                    temp[2 * i + 1][2 * j] = image[i][j];
                    temp[2 * i][2 * j + 1] = image[i][j];
                    temp[2 * i + 1][2 * j + 1] = image[i][j];
                }
            }
        } else if (s == 2) {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 128; j < SIZE; j++) {
                    temp[2 * i][2 * (j - SIZE / 2)] = image[i][j];
                    temp[2 * i + 1][2 * (j - SIZE / 2)] = image[i][j];
                    temp[2 * i][2 * (j - SIZE / 2) + 1] = image[i][j];
                    temp[2 * i + 1][2 * (j - SIZE / 2) + 1] = image[i][j];

                }
            }
        } else if (s == 3) {
            for (int i = 128; i < SIZE; i++) {
                for (int j = 0; j < SIZE / 2; j++) {
                    temp[2 * (i - SIZE / 2)][2 * j] = image[i][j];
                    temp[2 * (i - SIZE / 2) + 1][2 * j] = image[i][j];
                    temp[2 * (i - SIZE / 2)][2 * j + 1] = image[i][j];
                    temp[2 * (i - SIZE / 2) + 1][2 * j + 1] = image[i][j];
                }
            }
        } else if (s == 4) {
            for (int i = 128; i < SIZE; i++) {
                for (int j = 128; j < SIZE; j++) {
                    temp[2 * (i - SIZE / 2)][2 * (j - SIZE / 2)] = image[i][j];
                    temp[2 * (i - SIZE / 2) + 1][2 * (j - SIZE / 2)] = image[i][j];
                    temp[2 * (i - SIZE / 2)][2 * (j - SIZE / 2) + 1] = image[i][j];
                    temp[2 * (i - SIZE / 2) + 1][2 * (j - SIZE / 2) + 1] = image[i][j];
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[i][j];
            }
        }
    }

    void shrink_half() {
// representing every 4 pixels in 1 pixel by average method

        int temp[SIZE][SIZE];
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                temp[i][j] = 255;
            }
        }
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                temp[i][j] = (image[2 * i][2 * j] + image[2 * i][2 * j + 1] + image[2 * i + 1][2 * j] +
                              image[2 * i + 1][(j * 2) + 1]) / 4;
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = temp[i][j];
            }
        }
    }

    void shrink_quarter() {
// representing every 16 pixels in 1 pixel using two half shrink

        shrink_half();
        shrink_half();
    }

    void shrink_third(){
// representing every 9 pixels in 1 pixel by average method

        int temp[SIZE][SIZE];
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                temp[i][j] = 255;
            }
        }
        for (int i = 0; i < 86; i++) {
            for (int j = 0; j < 86; j++) {
                temp[i][j] = (image[3 * i][3 * j] + image[3 * i][3 * j + 1] + image[3 * i + 1][3 * j] +
                              image[3 * i + 1][(j * 3) + 1]+ image[3 * i + 1][3 * j]+ image[3 * i][3 * j + 2]+ image[3 * i + 2][3 * j + 2]) / 7;
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = temp[i][j];
            }
        }
    }

    void mrrleft () {
// cutting image vertically into two halves and coping the left one with inverse index

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE/2; j++) {
                int temp[SIZE][SIZE];
                temp[i][j] = image[i][j];
                image [i][255 - j] = temp[i][j];
            }
        }
    }

    void mrrright () {
// cutting image vertically into two halves and coping the right one with inverse index

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE/2; j++) {
                int temp[SIZE][SIZE];
                temp[i][j] = image[i][128 + j];
                image [i][127 - j] = temp[i][j];
            }
        }
    }

    void mrrupper () {
// cutting image horizontally into two halves and coping the upper one with inverse index

        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 0; j < SIZE; j++) {
                int temp[SIZE][SIZE];
                temp[i][j] = image[i][j];
                image [255 - i][j] = temp[i][j];
            }
        }
    }

    void mrrlower() {
// cutting image horizontally into two halves and coping the lower one with inverse index

        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 0; j < SIZE; j++) {
                int temp[SIZE][SIZE];
                temp[i][j] = image[128 + i][j];
                image [127 - i][j] = temp[i][j];
            }
        }
    }

    void shuffle() { // separating 4 quarters and implement user order to shuffle them

        int temp_st[SIZE][SIZE];
        int temp_nd[SIZE][SIZE];
        int temp_rd[SIZE][SIZE];
        int temp_th[SIZE][SIZE];
        //declaring 4 temps for saving four quarters
        for (int i = 0; i < SIZE / 2; i++) { // quarter #1
            for (int j = 0; j < SIZE / 2; j++) {
                temp_st[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE / 2; i++) {// quarter #2
            for (int j = 128; j < SIZE; j++) {
                temp_nd[i][j - 128] = image[i][j];
            }
        }
        for (int i = 128; i < SIZE; i++) {// quarter #3
            for (int j = 0; j < SIZE / 2; j++) {
                temp_rd[i - 128][j] = image[i][j];
            }
        }

        for (int i = 128; i < SIZE; i++) {// quarter #4
            for (int j = 128; j < SIZE; j++) {
                temp_th[i - 128][j - 128] = image[i][j];
            }
        } // user declaring order
        int order;
        cout<< "input order : \n";
        for (int i = 0; i < 4; i++) {
            int p ,l;
            if(i==0){
                p =0;
                l = 0;
            }
            if(i==1){
                p =0;
                l = 128;
            }
            if(i==2){
                p =128;
                l = 0;
            }
            if(i==3){
                p =128;
                l = 128;
            }
            cin >> order;
            if (order == 1) { // temps getting their places according to user's order
                int n = 0 ;
                int c = 0 ;
                for (int i = p; i < p + 128; i++) {
                    c = 0 ;
                    for (int j = l; j < l + 128; j++) {
                        image[i][j] = temp_st[n][c];
                        c++;
                    }
                    n++;
                }
            }
            if (order == 2) {
                int n = 0 ;
                int c = 0 ;
                for (int i = p; i < p + 128; i++) {
                    c = 0 ;
                    for (int j = l; j < l + 128; j++) {
                        image[i][j] = temp_nd[n][c];
                        c++;
                    }
                    n++;
                }
            }
            if (order == 3) {
                int n = 0 ;
                int c = 0 ;
                for (int i = p; i < p + 128; i++) {
                    c = 0 ;
                    for (int j = l; j < l + 128; j++) {
                        image[i][j] = temp_rd[n][c];
                        c++;
                    }
                    n++;
                }
            }
            if (order == 4) {
                int n = 0 ;
                int c = 0 ;
                for (int i = p; i < p + 128; i++) {
                    c = 0 ;
                    for (int j = l; j < l + 128; j++) {
                        image[i][j] = temp_th[n][c];
                        c++;
                    }
                    n++;
                }
            }
        }
    }

    void blur() {
// declaring temporary image(temp) in white scale then adding blurred pixels to it using average method
// (taking average gray scale of 9 pixels and represent it in one pixel)  5 times

        unsigned char temp[SIZE][SIZE];
        int c=5;
        while (c--){
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    temp[i][j] = 255;
                }
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    temp[i][j] = (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1]
                                  + image[i][j] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] +
                                  image[i + 1][j + 1]) / 9;
                }
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image[i][j] = temp[i][j];
                }
            }
        }
    }