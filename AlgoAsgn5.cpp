#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

class Vertex {
	private:
		double X;
		double Y;
		bool assigned;
		
	public:
		void set_X(double param) {
			X = param;
		}
		void set_Y(double param) {
			Y = param;
		}
		void set_assigned() {
			assigned = true;
		}
		
		double get_X() {return X;}
		double get_Y() {return Y;}
		bool get_assigned() {return assigned;}
		
		Vertex() {
			X = 0.0;
			Y = 0.0;
			assigned = false;
		}
};

double find_path(Vertex * graph, int size) {
	double result = 0;
	double * dist_table;
	double distanceX = 0.0;
	double distanceY = 0.0;
	double distance = 0.0;
	
	int lowest_index = 0;
	int counter = 0;
	
	dist_table = new double[size];
	dist_table[0] = 0.0;
	
	graph[0].set_assigned();
	
	// initialize distance table (just easier this way)
	for (int i = 1; i < size; i++) {
		distanceX = graph[0].get_X() - graph[i].get_X();
		distanceX = pow(distanceX, 2.0);
		
		distanceY = graph[0].get_Y() - graph[i].get_Y();
		distanceY = pow(distanceY, 2.0);
		
		distance = distanceX + distanceY;
		distance = pow(distance, 0.5);
		
		dist_table[i] = distance;
	}
	
	// given a table of distances from the frontier, find the lowest, add it to the group and recalc distances
	while (counter < size) {
		// find the first nonzero distance in dist_table first
		for (int j = 1; j < size; j++) {
			if (dist_table[j] > 0.0) {
				lowest_index = j;
				break;
			}
		}
		
		// find the lowest comparing against the first nonzero value found in the table
		for (int j = 0; j < size; j++) {
			if (dist_table[j] != 0.0) {
				if (dist_table[j] < dist_table[lowest_index]) {
					lowest_index = j;
				}
			}
		}
		
		// add it to the group
		graph[lowest_index].set_assigned();
		result += dist_table[lowest_index];
		dist_table[lowest_index] = 0.0;
		
		// recalculate table
		for (int j = 0; j < size; j++) {
			if (graph[j].get_assigned() == false) {
				distanceX = graph[lowest_index].get_X() - graph[j].get_X();
				distanceX = pow(distanceX, 2.0);
		
				distanceY = graph[lowest_index].get_Y() - graph[j].get_Y();
				distanceY = pow(distanceY, 2.0);
		
				distance = distanceX + distanceY;
				distance = pow(distance, 0.5);
				
				if (distance < dist_table[j]) {
					dist_table[j] = distance;
				}
			}
		}
		counter++;
	}
	delete[] dist_table;
	return result;
}

int main() {
	string input;
	double coord;
	int size;
	double result;
	Vertex * graph;
	
	// needed for various nonsense
	bool end_flag = false;
	
	while (getline(cin, input)) {
		if (input == "end") {break;}
		if (input == "") {
			cout << endl;
			continue;
		}
		size = atoi(input.c_str());

		graph = new Vertex[size];
		
		for (int i = 0; i < size; i++) {
			cin >> coord;
			cin.ignore();
			graph[i].set_X(coord);
			
			cin >> coord;
			cin.ignore();
			graph[i].set_Y(coord);			
		}
		
		result = find_path(graph, size);
		
		cout << fixed << setprecision(2) << result << endl;
		input = "end";
		delete[] graph;
	}
}