// Muhammed Salih YILDIZ
// 150180012

#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>

using namespace std;

struct Sales{

    Sales(string Country, string ItemType, string OrderId, int UnitsSold, float Profit);
    ~Sales();
    string country;
	string itemType;
	string orderId;
	int unitsSold;
    float profit;
};

Sales::Sales(string Country, string Type, string OrderId, int UnitsSold, float Profit){
    country = Country;
	itemType = Type;
	orderId = OrderId;
	unitsSold = UnitsSold;
    profit = Profit;
}

Sales::~Sales(){}

void swap(Sales* a, Sales* b)
{
    Sales t = *a;
    *a = *b;
    *b = t;
}

int partition(vector<Sales> &vec, int low, int high){
    Sales pivot = vec[high];
    int i = low ;

    for(int j = low; j < high; j++ ){
        int compare = vec[j].country.compare(pivot.country);
        if( compare < 0){
            swap(&vec[i], &vec[j]);
            i++;
        } else if(compare == 0 && !(vec[j].profit < pivot.profit)) {
            swap(&vec[i], &vec[j]);
            i++;
        }
    }
    swap(&vec[i], &vec[high]);
    return (i);
}

void quickSort(vector<Sales> &vec, int low, int high) {
    if(low < high){
        int partIndex = partition(vec, low, high);

        quickSort(vec, low, partIndex-1);
        quickSort(vec, partIndex+1, high);
    }
}

int main(int argc, char *argv[]){

    vector<Sales> datas;

    ifstream file;
    file.open("sales.txt");

    if (!file){
        cerr << "Input file cannot be opened!";
        exit(1);
    }

    int N = stoi(argv[1]); //you should read value of N from command line
    
    string line;
    string country;
	string itemType;
	string orderId;
	int unitsSold;
    float profit;

    Sales* Sale = new Sales(country, itemType, orderId, unitsSold,  profit);

    getline(file, line); //this is the header line

    for(int i = 0; i<N; i++){

        getline(file, line, '\t'); //country (string)
        country = line;
        getline(file, line, '\t'); //item type (string)
		itemType = line;
        getline(file, line, '\t'); //order id (string)
		orderId = line;
        file >> line; //units sold (integer)
		unitsSold = stoi(line);
        file >> line; //total profit (float)
        profit = stof(line);
        getline(file, line, '\n'); //this is for reading the \n character into dummy variable.

        Sale->country = country;
        Sale->itemType = itemType;
        Sale->orderId = orderId;
        Sale->unitsSold = unitsSold;
        Sale->profit = profit;
        
        datas.push_back(*Sale);
    }
    delete Sale;
	file.close();
	clock_t start;
	clock_t end;

	start = clock();
    quickSort(datas, 0, datas.size() - 1);
	end = clock();

	ofstream ofile;

	ofile.open("sorted.txt");

	if(!ofile){
		cerr << "Output file cannot be opened!";
        exit(1);
	}

	ofile<<"Country\tItem Type\tOrder ID\tUnits Sold\tTotal Profit\n";

	for(int i = 0; i < datas.size(); i++) {
		ofile<<datas[i].country<<"\t"<<datas[i].itemType<<"\t"<<datas[i].orderId<<"\t"<<datas[i].unitsSold<<"\t"<<datas[i].profit<<"\n";
	}

    datas.clear();

    cout<<(float(end-start)/CLOCKS_PER_SEC)*1000<<endl;
	
    
	
    return 0;
}
