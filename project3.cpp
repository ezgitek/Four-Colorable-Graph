/*
Student Name: Ezgi Tekdemir
Student Number: 2014400090
Project Number: 3
Operating System: Virtual Machine
Compile Status: Compiling
Program Status: {Working/Not Working}
Notes:
*/

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

class FourColor{
	public:
		 list <int>* edges; //the linked lists of vertices which are connected to vertices
		 pair<int, pair<int, string>>* valences; //no of vertex, valence, color
		 int NUM_OF_VERTICES;
		 string COLOR [4] = {"red", "green", "blue", "orange"};
	public:
		FourColor();
		~FourColor();
		void importData(char*);
		void runAlgorithm(char*);

};

FourColor::FourColor(){
	edges = NULL;
	valences = NULL;
	NUM_OF_VERTICES = 0;
}

FourColor::~FourColor(){
	delete[] edges;
	delete[] valences;
}



void FourColor::importData (char* inputFile){
	ifstream in (inputFile);
	in >> NUM_OF_VERTICES;
	edges = new list <int> [NUM_OF_VERTICES];
	valences = new pair <int, pair<int, string>> [NUM_OF_VERTICES];

	int temp;
	for(int i=0; i<NUM_OF_VERTICES; ++i){
		cout << i << ": ";
		int valence = 0;
		for(int j=0; j<NUM_OF_VERTICES; ++j){
			in>>temp;
			if(temp==1){
				edges[i].insert(edges[i].end(), j);
				valence += 1;
				cout<<edges[i].back()<<" ";
			}
		}
		pair <int, string> v (valence, "color");
		pair <int, pair<int, string>> node (i, v);
		valences[i] = node;
		cout<<"valence: "<<valences[i].second.first<<endl;

	}

}

void FourColor::runAlgorithm (char* outputFile){
	ofstream out (outputFile);

	bool is_swapped = true;
	int j=0;
	pair<int,pair<int,string>> temp;

	//bubble sort (descending order of valence)
	while(is_swapped){
		is_swapped=false;
		j++;
		for(int i=0; i<NUM_OF_VERTICES-j; ++i){
			if(valences[i].second.first < valences[i+1].second.first){
				temp = valences[i];
				valences[i] = valences[i+1];
				valences[i+1] = temp;
				is_swapped = true;
			} 
		}
	}


	int col=0; // int count = 0;
	for (int i=0; i<NUM_OF_VERTICES; ++i){

			vector <int> nowColored;
		if(valences[i].second.second != "color"){
			continue;
		}else{
			valences[i].second.second = COLOR[col];
			nowColored.push_back(i);
						//count++;

						cout << "node " << valences[i].first << " in " << COLOR[col] << endl;

			for(int j=0; j<NUM_OF_VERTICES; ++j){
				bool canColor = true;
				for(int k= 0 ; k< nowColored.size();k++){
					
					if (find(begin(edges[nowColored[k]]), 
						end(edges[nowColored[k]]), valences[j].first) 
						!= end(edges[nowColored[k]])) {

						canColor = false;
						break;
					}


				}
					if (find(begin(edges[valences[i].first]), 
						end(edges[valences[i].first]), valences[j].first) 
						== end(edges[valences[i].first]) && canColor && valences[j].second.second == "color")   {
							
							valences[j].second.second = COLOR[col];
							nowColored.push_back(j);

							cout << valences[j].first << " (if) " << valences[j].second.second << endl;
						//	count++;	
						
					}else{
						//cout<< " else: " << j;

						continue;
					}
			}
			cout<<"\n";
		}
				col++;

		//if(count==NUM_OF_VERTICES)
		//	break;

		if(col>4){
			out << "ups";
			return;
		} 
	}

    is_swapped = true;
	j=0;
	while(is_swapped){
		is_swapped=false;
		j++;
		for(int i=0; i<NUM_OF_VERTICES-j; ++i){
			if(valences[i].first > valences[i+1].first){
				temp = valences[i];
				valences[i] = valences[i+1];
				valences[i+1] = temp;
				is_swapped = true;
			} 
		}
	}



	for (int i = 0; i < NUM_OF_VERTICES; ++i)
	{
		out << valences[i].second.second << endl;
	}

}

int main(int argc, char *argv[]) {
	FourColor* fc = new FourColor();
	fc->importData(argv[1]);
	fc->runAlgorithm(argv[2]);

	return 0;
}