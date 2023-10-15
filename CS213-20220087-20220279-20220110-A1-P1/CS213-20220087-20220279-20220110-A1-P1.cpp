// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: 				filters editor .cpp
// Last Modification Date:	10/10/2023
// Author1 and ID and Group:	Belal Mohamed Youness - 20220087 Group B email : belalyouness494@gmail.com
// Author2 and ID and Group:	Hossam Mohsen Hassan - 20220110 - fc22hossam@gmail.com
// Author3 and ID and Group:	Mohamed Ahmed Ali - 20220279 - Derballa2004@gmail.com
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
int process ; // integer for filter input numbers
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

int main()
{
  cout<<"Hey user ;) \n"
  <<"Select a filter from the following : \n"
  <<"1- Black and White\n"
  <<"2- Inverse\n"
  <<"3- Merge\n"
  <<"4- Flip (Horizontal / Vertical)\n"
  <<"5- Rotate\n"
  <<"6- Darken or Lighten \n";
  load();

  start:; //regenerating menu point

  cout<<"Enter the required filter : ";
  cin>>process;


  switch(process){ // switch for filters and functions . every case contains save function
      case 1:
          bw();
          save();
          break;
      case 2:
          inverse();
          save();
          break;
      case 3:
          merge();
          save();
          break;
      case 4:
          char x;
          cout<<"would you like to flip the image in a horizontal or vertical way (H/V) ?";
          cin>> x;
          if (x == 'V'|| x == 'v') // if condition to allow the user to choose vertical flip or horizontal flip
              flipvt();
          else
              fliphz();
          save();
          break;
      case 5:
          rotate();
          save();
          break;
      case 6:
          char y;
          cout<<"would you darken or lighten the image (D/L) ?";
          cin>>y;
          if(y == 'D'||y=='d') // if condition to allow the user to choose between the dark or light effect
              darken();
          else
              lighten();

          save();
          break;

  }
  cout<<"Do you want to add another filter ?(Y,N):";
  char w;
  cin>>w;
  if(w == 'Y'|| w== 'y') // if condition offering the user to continue editing or exit
      goto start; // function to regenerate the menu for another filter
  else
      cout<<"sharftena ya 2amr. ";
  return 0;
}
// temp integer = temporary images to make the algorithms easier
void load () {

    char imagefilename[100];
    cout << "Enter the source image file name : ";
    cin >> imagefilename;
    strcat (imagefilename, ".bmp"); // adding .bmp to name entered to make it an image file
    readGSBMP(imagefilename, image); // reads the image from the file specified by filename in a specific folder
}
void loadtwo () { //same as load() for second image in merge filter

    char imagefilename[100];
    cout << "Enter the second source image file name : ";
    cin >> imagefilename;
    strcat(imagefilename, ".bmp");
    readGSBMP(imagefilename, image2);
}
void save () {

    char imagefilename[100];
    cout << "Name the file :  ";
    cin >> imagefilename;
    strcat (imagefilename, ".bmp");// adding .bmp to name entered to make it an image file
    writeGSBMP(imagefilename, image); // saving image with the name user entered and apply it as [256][256] image
}

void bw() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
void inverse () {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255 - image[i][j];
        }
    }
}
void merge() {

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
            if(i>=127 && j>=127) {
                int temp = image[i][j];
                image[i][j] = image[255-i][j];
                image[255-i][j] = temp ;
            }
            else if(i<127 && j<127){
                int temp = image[i][j];
                image[i][j] = image[255-i][j];
                image[255-i][j] = temp;
            }
        }
    }
}

void flipvt() {

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
    int temp [SIZE][SIZE];
    cout<<"Please enter the degree of rotation (90 , 180 , 270) : ";
    cin>>y ;
    if(y == 90)
        z = 1;
    else if(y==180)
        z = 2;
    else if(y == 270)
        z = 3;
    else
        z = 4;
    while(z--){
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

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j]=(255+image[i][j])/2;
        }
    }
}
void darken () {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j]=(image[i][j]/2);
        }
    }
}
