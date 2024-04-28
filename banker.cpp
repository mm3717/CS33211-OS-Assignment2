//CS33211 
//Instructor: Dr. Qiang Guan
//Author: Maxim Mamotlivi
//Date: 4/25/2024

#include <stdlib.h>   //standard lib
#include <iostream>   //in-out stream
#include <fstream>    //file stream

int main(){
    std::ifstream file("tables.txt");
    if(!file.is_open()) return -1;
    
    int r = 5, c = 3; //rows and columns
    int alloc[r][c], max[r][c], need[r][c], avail[c], seq[r];

    //populate alloc, max, avail
    for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) file >> alloc[i][j];
    for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) file >> max[i][j];
    for(int i = 0; i < c; i++)                            file >> avail[i];
    file.close();
    
    //populate need
    for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) need[i][j] = max[i][j] - alloc[i][j];

    //calculate availability states, recheck availability
    bool doom = false; int adv = 0;
    for(int x = 1; x <= r; x++){
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if(need[i][j] > avail[j]){
                    seq[i] = -1 * x;       //flags insufficent round
                    if(x > 1) doom = true; //flags unsafe
                    break;
                }
            }
            if((seq[i] != -1 && x == 1) || (x > 1 && seq[i] == -1 * (x-1))){
                for(int k = 0; k < c; k++){
                    avail[k] += alloc[i][k]; 
                }
                seq[i] = adv; //marks position in safe sequence (process denoted by index) 
                adv++;
                doom = false;
            }
            //std::cout << "P" << i << ": " << seq[i] << " " << doom << std::endl; //used for debugging
        }
        std::cout << std::endl; //used for debugging
    }

    //report sequence or if unsafe
    if(doom) std::cout << "SYSTEM UNSAFE" << std::endl;
    else{ 
        std::cout << "Execution order of each process:" << std::endl;
        for(int i = 0; i < r; i++) std::cout << "P" << i << ": " << seq[i] << std::endl;
    }
    
    /*//print alloc, max, need, avail; for debugging
    std::cout << "print tables: alloc, max, need, avail\n";
    for(int x = 0; x < 4; x++){
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                     if(x == 0) std::cout << alloc[i][j] << " ";
                else if(x == 1) std::cout << max[i][j] << " ";
                else if(x == 2) std::cout << need[i][j] << " ";
                else if(i == 0) std::cout << avail[j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }*/
}