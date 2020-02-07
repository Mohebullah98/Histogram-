#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
class image{
public:
int numRows;
int numCols;
int minVal;
int maxVal;
int * histArray;
int thresholdValue;

void ComputeHist(ifstream& inFile , int histArray[]){
    int val;
    while(inFile>>val){
      histArray[val]+=1;
    }
}
void printHist(int histArray[], ofstream& outFile1){
  for(int i=0;i<maxVal+1;i++){
    outFile1<<i<<" "<< "("<< histArray[i] << ") :";
    for(int j=0;j<histArray[i];j++){
      outFile1<<"+";
    }
    outFile1<<endl;
  }
}
void thresholdOp(ifstream& inFile, int ThresholdValue, fstream& outFile2){
  
 int pixel_val;
 for(int i=0;i<numRows;i++){
   for (int j=0;j<numCols;j++){
     inFile>> pixel_val;
     if (pixel_val>=ThresholdValue){
       outFile2<<1<<" ";
     }
     else{outFile2<<0<<" ";
     }
   }
   outFile2<<endl;
 }
}

void prettyPrint(fstream& outFile2,ofstream& outFile3){
   int pixel_val;
   outFile2>>pixel_val>>pixel_val>>pixel_val>>pixel_val;
 for(int i=0;i<numRows;i++){
   for (int j=0;j<numCols;j++){
     outFile2>> pixel_val;
     if (pixel_val>0){
       outFile3<<1<<" ";
     }
     else{outFile3<<"  ";
     }
   }
   outFile3<<endl;
 }
}

};

int main(int argc, char* argv[]){

  ifstream inFile;
  inFile.open(argv[1]);
  ofstream outFile1;
  fstream outFile2;
  ofstream outFile3;
  outFile1.open(argv[2]);
  outFile2.open(argv[3]);
  outFile3.open(argv[4]);
  ifstream thresh;
  thresh.open(argv[5]);
  int thresholdValue = atoi(argv[5]);
  image image1;
  
  inFile>>image1.numRows>>image1.numCols>>image1.minVal>>image1.maxVal;
  outFile1<<image1.numRows<<" "<<image1.numCols<<" "<<image1.minVal<<" "<<image1.maxVal<<endl;
  outFile2<<image1.numRows<<" "<<image1.numCols<<" "<<0<<" "<<1<<endl;
  
  
  image1.histArray = new int[image1.maxVal+1];
  for(int i=0;i<image1.maxVal+1;i++){
    image1.histArray[i]=0;
  }
  image1.ComputeHist(inFile, image1.histArray);
  image1.printHist(image1.histArray, outFile1);
  inFile.close();
  inFile.open(argv[1]);
  inFile>>image1.numRows>>image1.numCols>>image1.minVal>>image1.maxVal;
  image1.thresholdOp(inFile,thresholdValue,outFile2);
  outFile2.close();
  outFile2.open(argv[3]);
  image1.prettyPrint(outFile2,outFile3);
  inFile.close();
  outFile1.close();
  outFile2.close();
  outFile3.close();
  
  

}
