
// FCAI – OOP Programming – 2023 - Assignment 1 Bonus
// Program Name: 				filters RGB editor .cpp
// Last Modification Date:	19/10/2023
// Teaching Assistant:		xxxxxxxxxx
// Purpose:A C++ code to apply 15 RGB filters and user can do it for several times on the same image.
// Comments same as gray scale but with declaration of [RGB] for loops .


#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include "bmplib.cpp"
#include "bmplib.h"
using namespace std;

unsigned char image[SIZE][SIZE][RGB];  //declaring image as a char [256][256][RGB]
unsigned char image2[SIZE][SIZE][RGB]; //declaring second image for filter # 3
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
void crop();// user chooses point coordinates , vertical and horizontal length to crop it from the image
void skewhz(); // rotate the image horizontally  to make it like a parallelogram inside image brain
void skewvt();// rotate the image vertically to make it like a parallelogram inside image brain
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
  <<"d- crop\n"
  <<"e- skew horizontal\n"
  <<"f- skew vertical\n";
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
      case 'd':
          crop();
          save();
          break;
      case 'e':
          skewhz();
          save();
          break;
      case 'f':
          skewvt();
          save();
          break;
       }
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
    readRGBBMP(imagefilename, image); // reads the image from the file specified by filename in a specific folder
}
void loadtwo () { //same as load() for second image in merge filter

    char imagefilename[100];
    cout << "Enter the second source image file name :  \n";
    cin >> imagefilename;
    strcat(imagefilename, ".bmp");
    readRGBBMP(imagefilename, image2);
}
void save () { //function to save the edited image

    char imagefilename[100];
    cout << "Name the file :  \n";
    cin >> imagefilename;
    strcat (imagefilename, ".bmp");// adding .bmp to name entered to make it an image file
    writeRGBBMP(imagefilename, image); // saving image with the name user entered and apply it as [256][256][RGB] image
}

void bw() { // 127 is the midpoint between black and white , so we make a black and white with avg code between the
    // three colors so the pixel doesn't depend on one color

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if ((image[i][j][RGB-1] + image[i][j][RGB-2] + image[i][j][RGB-3]) /3> 127)
                image[i][j][RGB-1] = 255;
            else
                image[i][j][RGB-1] = 0;
            image[i][j][RGB-3] = image[i][j][RGB-1];
            image[i][j][RGB-2] = image[i][j][RGB-1];
        }
    }

}

void inverse () { // getting the adding inverse of (255) for every color matrix

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int ch = 0; ch < RGB; ch++)
                image[i][j][RGB-2] = 255 - image[i][j][RGB-2];
                image[i][j][RGB-3] = 255 - image[i][j][RGB-3];
                image[i][j][RGB-1] = 255 - image[i][j][RGB-1];
        }
    }
}
void merge() { // adding two images and getting the avg between their RGB pixels

    loadtwo();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                image[i][j][RGB] = (image[i][j][RGB] + image2[i][j][RGB]) / 2;
            }
        }
    }
}
void fliphz() {

    for (int i = 0; i < (SIZE / 2); i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                // swapping pixels by temp char in a horizontal way
                unsigned char temp = image[i][j][ch];
                image[i][j][ch] = image[255 - i][j][ch];
                image[255 - i][j][ch] = temp;
            }
        }
    }
}

void flipvt() { // same as flip hz() but in a vertical way

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < (256 / 2); j++) {
            for (int z = 0; z < 3; z++) {
                // Horizontally flips the image by swapping pixels.
                unsigned char temp = image[i][j][z];
                image[i][j][z] = image[i][255 - j][z];
                image[i][255 - j][z] = temp;
            }
        }
    }
}

void rotate (){

    int y;
    int z;
    unsigned char  temp [SIZE][SIZE][RGB]; // declaring a temporary image
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
    while(z--){ // using simple math equation for pixels interchange to get image[255-j][i][RGB] pixels muck in with temp[i][j][RGB]
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int ch = 0; ch < 3; ch++){
                    temp [i][j][ch]= image [i][j][ch];
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int ch = 0; ch < 3; ch++){
                    image [i][j][ch]= temp[255-j][i][ch];
                }
            }
        }
    }
}

void lighten() {
// lighten image by average this way to be more accurate than adding scale bits
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int ch = 0; ch < 3; ch++){
                image[i][j][ch]=(255+image[i][j][ch])/2;
            }
        }
    }
}
void darken () {
// darken image by average this way to be more accurate than subtracting scale bits
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int ch = 0; ch < 3; ch++){
                image[i][j][ch]=(image[i][j][ch]/2);
            }
        }
    }
}
void detectedges() {

 for (int i = 0; i < SIZE; i++) {
     for (int j = 0; j < SIZE; j++) {
         for (int ch = 0; ch < 3; ch++){
             if ((abs(image[i][j][ch] - image[i][j + 1][ch]) >= 30) || (abs(image[i][j][ch] - image[i + 1][j][ch]) >= 30)) {
                 image[i][j][ch] = 0;
             } else
                 image[i][j][ch] = 255;
         }
     }
 }
}

void enlarge (){
    unsigned char temp[SIZE][SIZE][RGB];
    int s; // declaring temp image ,dividing image into four quarters and representing every 1 pixel in four pixels
    cout<<"input quarter you want to enlarge (1,2,3,4) : \n";
    cin>>s;

    if (s == 1) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) { //enlarge quarter#1
                for (int ch = 0; ch < 3; ch++){
                    temp[2 * i][2 * j][ch] = image[i][j][ch];
                    temp[2 * i + 1][2 * j][ch] = image[i][j][ch];
                    temp[2 * i][2 * j + 1][ch] = image[i][j][ch];
                    temp[2 * i + 1][2 * j + 1][ch] = image[i][j][ch];
                }
            }
        }
    } else if (s == 2) {
        for (int i = 0; i < SIZE / 2; i++) {//enlarge quarter#2
            for (int j = 128; j < SIZE; j++) {
                for (int ch = 0; ch < 3; ch++){
                    temp[2 * i][2 * (j - SIZE / 2)][ch] = image[i][j][ch];
                    temp[2 * i + 1][2 * (j - SIZE / 2)][ch] = image[i][j][ch];
                    temp[2 * i][2 * (j - SIZE / 2) + 1][ch] = image[i][j][ch];
                    temp[2 * i + 1][2 * (j - SIZE / 2) + 1][ch] = image[i][j][ch];
                }
            }
        }
    }
    else if (s == 3) {
        for (int i = 128; i < SIZE; i++) {//enlarge quarter#3
            for (int j = 0; j < SIZE / 2; j++) {
                for (int ch = 0; ch < 3; ch++) {
                    temp[2 * (i - SIZE / 2)][2 * j][ch] = image[i][j][ch];
                    temp[2 * (i - SIZE / 2) + 1][2 * j][ch] = image[i][j][ch];
                    temp[2 * (i - SIZE / 2)][2 * j + 1][ch] = image[i][j][ch];
                    temp[2 * (i - SIZE / 2) + 1][2 * j + 1][ch] = image[i][j][ch];
                }
            }
        }
    } else if (s == 4) {
        for (int i = 128; i < SIZE; i++) {//enlarge quarter#4
            for (int j = 128; j < SIZE; j++) {
                for (int ch = 0; ch < 3; ch++){
                    temp[2 * (i - SIZE / 2)][2 * (j - SIZE / 2)][ch] = image[i][j][ch];
                    temp[2 * (i - SIZE / 2) + 1][2 * (j - SIZE / 2)][ch] = image[i][j][ch];
                    temp[2 * (i - SIZE / 2)][2 * (j - SIZE / 2) + 1][ch] = image[i][j][ch];
                    temp[2 * (i - SIZE / 2) + 1][2 * (j - SIZE / 2) + 1][ch]= image[i][j][ch];
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {// paste temp in image [i][j] to output image in void save()
            for (int ch = 0; ch < 3; ch++){
                image[i][j][ch] = temp[i][j][ch];
            }
        }
    }
}

void shrink_half() {
// representing every 4 pixels in 1 pixel by average method

    unsigned char temp[SIZE][SIZE][RGB];
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int ch = 0; ch < 3; ch++) {
                temp[i][j][ch] = 255;
            }
        }
    }
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            for (int ch = 0; ch < 3; ch++) {
                temp[i][j][ch] = (image[2 * i][2 * j][ch] + image[2 * i][2 * j + 1][ch] + image[2 * i + 1][2 * j][ch] +
                              image[2 * i + 1][(j * 2) + 1][ch]) / 4;
            }
        }
    }
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int ch = 0; ch < 3; ch++) {
                image[i][j][ch] = temp[i][j][ch];
            }
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

    unsigned char temp[SIZE][SIZE][RGB];
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int ch = 0; ch < 3; ch++) {
                temp[i][j][ch] = 255;
            }
        }
    }
    for (int i = 0; i < 86; i++) {
        for (int j = 0; j < 86; j++) {
            for (int ch = 0; ch < 3; ch++) {
                temp[i][j][ch] = (image[3 * i][3 * j][ch] + image[3 * i][3 * j + 1][ch] + image[3 * i + 1][3 * j][ch] +
                              image[3 * i + 1][(j * 3) + 1][ch] + image[3 * i + 1][3 * j][ch] + image[3 * i][3 * j + 2][ch] +
                              image[3 * i + 2][3 * j + 2][ch]) / 7;
            }
        }
    }
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int ch = 0; ch < 3; ch++) {
                image[i][j][ch] = temp[i][j][ch];
            }
        }
    }
}

void mrrleft () {
// cutting image vertically into two halves and coping the left one with inverse index

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE/2; j++) {
            for (int ch = 0; ch < 3; ch++) {
                unsigned char temp[SIZE][SIZE][RGB];
                temp[i][j][ch] = image[i][j][ch];
                image [i][255 - j][ch] = temp[i][j][ch];
            }
        }
    }
}

void mrrright () {
// cutting image vertically into two halves and coping the right one with inverse index

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE/2; j++) {
            for (int ch = 0; ch < 3; ch++) {
                unsigned char temp[SIZE][SIZE][RGB];
                temp[i][j][ch] = image[i][128 + j][ch];
                image[i][127 - j][ch] = temp[i][j][ch];
            }
        }
    }
}

void mrrupper () {
// cutting image horizontally into two halves and coping the upper one with inverse index

    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int ch = 0; ch < 3; ch++) {
                unsigned char temp[SIZE][SIZE][RGB];
                temp[i][j][ch] = image[i][j][ch];
                image[255 - i][j][ch] = temp[i][j][ch];
            }
        }
    }
}

void mrrlower() {
// cutting image horizontally into two halves and coping the lower one with inverse index

    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int ch = 0; ch < 3; ch++) {
                unsigned char temp[SIZE][SIZE][RGB];
                temp[i][j][ch] = image[128 + i][j][ch];
                image[127 - i][j][ch] = temp[i][j][ch];
            }
        }
    }
}

void shuffle() { // separating 4 quarters and implement user order to shuffle them

    unsigned char temp_st[SIZE][SIZE][RGB];
    unsigned char temp_nd[SIZE][SIZE][RGB];
    unsigned char temp_rd[SIZE][SIZE][RGB];
    unsigned char temp_th[SIZE][SIZE][RGB];
    //declaring 4 temps for saving four quarters
    for (int i = 0; i < SIZE / 2; i++) { // quarter #1
        for (int j = 0; j < SIZE / 2; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                temp_st[i][j][ch] = image[i][j][ch];
            }
        }
    }
    for (int i = 0; i < SIZE / 2; i++) {// quarter #2
        for (int j = 128; j < SIZE; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                temp_nd[i][j - 128][ch] = image[i][j][ch];
            }
        }
    }
    for (int i = 128; i < SIZE; i++) {// quarter #3
        for (int j = 0; j < SIZE / 2; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                temp_rd[i - 128][j][ch] = image[i][j][ch];
            }
        }
    }

    for (int i = 128; i < SIZE; i++) {// quarter #4
        for (int j = 128; j < SIZE; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                temp_th[i - 128][j - 128][ch] = image[i][j][ch];
            }
        }
    } // user declaring order
    int order;
    cout<< "input order : \n";
    for (int x = 0; x < 4; x++) {

        int p ,l;
        if(x==0){
            p =0;
            l = 0;
        }
        if(x==1){
            p =0;
            l = 128;
        }
        if(x==2){
            p =128;
            l = 0;
        }
        if(x==3){
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
                    for (int ch = 0; ch < 3; ch++) {
                        image[i][j][ch] = temp_st[n][c][ch];
                    }
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
                    for (int ch = 0; ch < 3; ch++) {
                        image[i][j][ch] = temp_nd[n][c][ch];
                    }
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
                    for (int ch = 0; ch < 3; ch++) {
                        image[i][j][ch] = temp_rd[n][c][ch];
                    }
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
                    for (int ch = 0; ch < 3; ch++) {
                        image[i][j][ch] = temp_th[n][c][ch];
                    }
                    c++;
                }
                n++;
            }
        }
    }
}

void blur() {
// declaring temporary white image(temp) then adding blurred pixels to it using average method
// (taking average RGB of 9 pixels and represent it in one pixel)  8 times

    unsigned char temp[SIZE][SIZE][RGB];
    int c = 8;

    while (c--) {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int ch = 0; ch < RGB; ch++) {
                    temp[i][j][ch] = 255;
                }
            }
        }
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - 1; j++) {
                for (int ch = 0; ch < RGB; ch++) {
                    temp[i][j][ch] = (image[i - 1][j - 1][ch] + image[i - 1][j][ch] + image[i - 1][j + 1][ch] +
                                       image[i][j - 1][ch]+ image[i][j][ch] + image[i][j + 1][ch] +
                                       image[i + 1][j - 1][ch] +image[i + 1][j][ch] +image[i + 1][j + 1][ch]) / 9;
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int ch = 0; ch < RGB; ch++) {
                    image[i][j][ch] = temp[i][j][ch];
                }
            }
        }
    }
}
void crop () {
    // using user point coordinates and length to set the new image limits and crop it from the original one

    int x; int y; int length; int width; unsigned char temp[SIZE][SIZE][RGB];
    cout <<"x coordinate: ";cin>>x;
    cout <<"y coordinates: ";cin>>y;
    cout <<"lenght: ";cin>>length;
    cout <<"width: ";cin>>width;
    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                temp[i][j][ch] = 255;
            }
        }
    }
    //setting the coordinates point as a starting point and initializing 2 lines with the
    // length of length and width input to crop the image
    for (int i = y; i < length; i++) {
        for (int j = x; j < width; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                temp[i + x][j + y][ch] = image[i + x][j + y][ch];
            }
        }
    }
    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                image[i][j][ch] = temp[i][j][ch];
            }
        }
    }
}

void skewhz() {

    int angle;
    double unit,step,rad,x;
    cout<<"Input the required angle : \n";cin>>angle;
    angle = 90-angle;
    rad = (tan((angle*M_PI)/180));
    x= 256/(1+1/rad); // to get the shrink base length
    step=SIZE-x; // beginning point
    unit =step/SIZE;
    unsigned char temp[SIZE][SIZE][RGB];
    float y= SIZE/x,count; // shrink variables for base editing
    for (int i = 0; i < SIZE; i++) {
        count=0;
        for (int j = 0; j < x; j++) {
            count += y; // adding pixels count
            for (int ch = 0; ch < RGB; ch++) {

                temp[i][j][ch] = image[i][int(count)][ch];
            }
        }
    }
    for (int i = SIZE-1; i >= 0; i--) {
        for (int j = SIZE-1; j >= 0; j--) {
            for (int ch = 0; ch < RGB; ch++) {
                image[i][j][ch] = 255; //declaring white image in background
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        int length=step +x,n=0;
        for (int j = step; j < length; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                image[i][j][ch] = temp[i][n][ch];

            }
            n++;
        }
        step-=unit;// diagonal shaping by horizontal pixels line
    }
}

void skewvt() {

    int angle;
    double unit,step,rad,x;
    cout<<"Input the required angle : \n";cin>>angle;
    angle = 90-angle;
    rad = (tan((angle*M_PI)/180));
    x= 256/(1+1/rad); // to get the shrink height length
    step=SIZE-x; // beginning point
    unit =step/SIZE;
    unsigned char temp[SIZE][SIZE][RGB];
    float y= SIZE/x,count; // shrink variables for height editing
    for (int i = 0; i < SIZE; i++) {
        count=0;
        for (int j = 0; j < x; j++) {
            count+=y; // adding pixels count
            for (int ch = 0; ch < RGB; ch++) {
                temp[j][i][ch] = image[int(count)][i][ch];
            }
        }
    }
        for (int i = SIZE-1; i >= 0; i--) {
            for (int j = SIZE-1; j >= 0; j--) {
                for (int ch = 0; ch < RGB; ch++) {
                    image[i][j][ch] = 255; //declaring white image in background
                }
            }
        }
    for (int i = 0; i < SIZE; i++) {
        int length=step +x,n=0;
        for (int j = step; j < length; j++) {
            for (int ch = 0; ch < RGB; ch++) {
                image[j][i][ch] = temp[n][i][ch];
            }
            n++;
        }
        step-=unit;// diagonal shaping by vertical pixels line
    }
}
