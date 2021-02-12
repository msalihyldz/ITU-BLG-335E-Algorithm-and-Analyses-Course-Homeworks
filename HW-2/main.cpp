// Muhammed Salih YILDIZ
// 150180012

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <cmath>

using namespace std;

vector<double> taxis;

//Returns the index of the parent node of the given node.
int parent(int i){
    return ((i - 1) / 2);
}

//Returns the left children node of the given node
int leftChild(int i){
    return ((2 * i) + 1);
}

//Returns the right children node of the given node
int rightChild(int i){
    return (2 * (i + 1));
}

//Updates the given nodes position to the upper direction
void goUp(int i){
    while( i > 0 && taxis[parent(i)] > taxis[i]){//Compares child node and parent node
        swap(taxis[parent(i)], taxis[i]);//Swaps parent and child nodes
        i = parent(i);//Continues the same operation with new parent node
    }
}

//Adds a new taxi to the queue
void insert(double d){
    taxis.push_back(d);//Adds new node to end of the queue
    goUp(taxis.size() - 1);//Finds the position of the new added node
}

//Sorts the heap
void Heapify(int i){
    int right = rightChild(i);
    int left = leftChild(i);
    int smallest = i;

    if( right < taxis.size() && taxis[right] < taxis[smallest] ){//If right node is lower than parent node than marks it as smallest
        smallest = right;
    }

    if( left < taxis.size() && taxis[left] < taxis[smallest]){//If left node is lower than parent or right node than marks it as smallest
        smallest = left;
    }

    if( smallest != i){//If the smallest one of the three nodes is not the parent then swaps the smallest with the parent
        swap(taxis[i], taxis[smallest]);
        Heapify(smallest);
    }
}

///Prints the minimum value in the queue
void extractMin(){
    double result;
    if(taxis.size() > 0){//If the number f taxis is not zero then works as expected else prints "No taxi".
        result = taxis[0];//Gets the first element of the queue which is smallest one
        swap(taxis[0], taxis[taxis.size() - 1]);//Swaps the last element and first element
        taxis.pop_back();//Deletes the old first node
        Heapify(0);//Sorts the queue
        cout<<result<<endl;
    } else{
        cout<<"No taxi is available!"<<endl;
    }
}

int main(int argc, char *argv[]){


    ifstream file;
    file.open("locations.txt");//Opens the file

    if (!file){
        cerr << "Input file cannot be opened!";//Gives error if occurs with an error during the openin of the file
        exit(1);
    }

    srand(time(NULL));//Sets the seed

    int m = stoi(argv[1]); //m value read from command line
    float p = stof(argv[2]); //p value read from command line
    p = p*100; // p value multiplied by 100 to ease of operations
    int left_opt = m;

    clock_t start;
    clock_t end;


    string readData;
    getline(file, readData); // Reads headers of the file

    float prob;
    int addition_num = 0;
    int update_num = 0;

    start = clock(); //Calculation time started

    while(left_opt > 0){ // Operates as much as m number

        if(left_opt % 100 == 0 && m != left_opt){ // Calls a taxi in every 100 operations
            extractMin();
            left_opt--;
            continue;
        }

        prob = rand() % 100; // Calculates probability

        if(prob <= p){ // If the probability is equal or lower than given value then it makes update operation
            if(taxis.size() == 1){
                taxis[0] -= 0.01; // Decreases the distance of the picked taxi
                Heapify(0); // Sorts again
            }else if(taxis.size() > 1){
                int index = rand() % (taxis.size() - 1); // Picks randomly a taxi
                taxis[index] -= 0.01; // Decreases the distance of the picked taxi
                Heapify(0); // Sorts again
            }
            update_num++;
        } else { // If the probability is higher than given value then reads data from the file
            file >> readData;

            if(file.eof()){
                break;
            }

            double longitude = stod(readData);
            file >> readData;
            double latitude = stod(readData);
            getline(file, readData, '\n'); //this is for reading the \n character into dummy variable.

            insert(sqrt(pow((longitude - 33.40819),2) + pow((latitude - 39.19001),2))); // Adds the distance of the new taxi to the queue

            addition_num++;
        }

        left_opt--;
    }

    end = clock(); //Calculation time ended

    cout<<"Number of addition is: "<<addition_num<<endl;
    cout<<"Number of update is: "<<update_num<<endl;
    cout<<"Passed time in milliseconds: "<<(((float)end)-((float)start))/ ( CLOCKS_PER_SEC / 1000 )<<endl;

    return 0;
}