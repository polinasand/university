#include "merkle_tree.h"

SHA256 *sha = new SHA256();

string MerkleTree::calculateRoot(vector<string> inputs){

    if (inputs.size() == 0)
        return "";

    vector<vector<string>> state;
	state.resize(2);
	int curr = 0;

	for (auto input: inputs){
        string input_hash;
        strcpy((char*)sha->hash(input), input_hash.c_str());
		state[curr].push_back(input_hash);
	}

	while (state[curr].size() != 1){
		for (int j = 0; j < state[curr].size(); j += 2){
			string node_value = state[curr][j];
			node_value = node_value +
			((j + 1 < state[curr].size()) ? state[curr][j + 1] : node_value);
			string node_hash;
            strcpy((char*)sha->hash(node_value), node_hash.c_str());
			state[1 - curr].push_back(node_hash);
		}
		state[curr].clear();
		curr = 1 - curr;
	}

	return state[curr][0];
}
