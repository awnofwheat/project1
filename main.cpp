//
//  main.cpp
//  project1
//
//  Created by 张嘉艺 on 2020/11/15.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include "cblas.h"



using namespace std;

struct matrice{
    int row;
    int column;
    double * data;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    fstream finout("data", ios::in|ios::out);
    
//    if(finout.good()){
//        finout<<"20000 10000 10000 20000"<<endl;
//        for(int i=0; i<20000; i++){
//            for(int j=0; j<10000; j++){
//                finout<<(float)(rand()%10)/10<<" ";
//            }
//            finout<<endl;
//        }
//        for(int i=0; i<10000; i++){
//            for(int j=0; j<20000; j++){
//                finout<<(float)(rand()%10)/10<<" ";
//            }
//            finout<<endl;
//        }
//    }
//    finout.close();
//
        

    matrice m1, m2, result;

    if(finout.good()){
        while(!finout.eof()){
            finout >> m1.column >> m1.row >> m2.column >> m2.row;
            if (m1.column != m2.row)
            {
                cout << "Mat1 and Mat2 can not multiplicated!" << endl;
            }
            //输入矩阵
            else
            {
                m1.data=new double  [m1.row*m1.column];
                
                m2.data=new double  [m2.row*m2.column];
                for (int i = 0; i < m1.row; i++)
                {
                    for(int j=0; j<m1.column; j++){
                        finout>>m1.data[i*m1.column+j];
                    }
                }
                for (int i = 0; i < m2.row; i++)
                {
                    for(int j=0; j<m2.column; j++){
                        finout>>m2.data[i*m2.column+j];
                    }
                }
            }
        }
        finout.close();
    }
    auto start = std::chrono::steady_clock::now();
    result.row=m1.row;
    result.column=m2.column;
    result.data=new double  [result.row*result.column];
//    double s;
//    for(int i=0; i<result.row; i++){
//        for(int k=0; k<result.column; k++){
//            s=m1.data[i*m1.column+k];
//            for(int j=0; j<result.column; j++){
//                result.data[i*result.column+j]+=s*m2.data[k*m2.column+j];
//            }
//        }
//    }
    cblas_sgemm(CblasRowMajor, CblasTrans, CblasTrans, m1.row, m2.column, m1.column, 1, m1.data, m1.row, m2.data, m2.column, 0, result.data, m1.column);
    auto end = std::chrono::steady_clock::now();
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<endl;
    ofstream outClientFile;
    outClientFile.open("result", ios::out);
    for(int i=0; i<result.row*result.column; i++){
        outClientFile<<result.data[i][j]<<" ";
        outClientFile<<endl;
    }
    outClientFile.close();
    
    delete [] m1.data;
    
    delete [] m2.data;
    
    delete [] result.data;


    return 0;
}
