#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		// find parent and compress path
		if (sets.at(table).parent == table){
			return table;
		}else{
			int result = getParent(sets.at(table).parent);
			sets.at(table).parent = result;
			return result;
		}
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			// merge two components
			// use union by rank heuristic
                        // update max_table_size
			int desRank = sets.at(realDestination).rank;
			int sourceRank = sets.at(realSource).rank;

			if (desRank < sourceRank ){
				sets.at(realDestination).parent = realSource;
				sets.at(realSource).size += sets.at(realDestination).size;
				max_table_size = max(max_table_size, sets.at(realSource).size);
			}else if (desRank > sourceRank){
				sets.at(realSource).parent = realDestination;
				sets.at(realDestination).size += sets.at(realSource).size;
				max_table_size = max(max_table_size, sets.at(realDestination).size);
			}else{
				sets.at(realSource).parent = realDestination;
				sets.at(realDestination).size += sets.at(realSource).size;
				sets.at(realDestination).rank++;
				max_table_size = max(max_table_size, sets.at(realDestination).size);
			}
			

		}else{
			return;
		}		
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
                --destination;
                --source;
		
		tables.merge(destination, source);
	        cout << tables.max_table_size << endl;
	}

	return 0;
}
