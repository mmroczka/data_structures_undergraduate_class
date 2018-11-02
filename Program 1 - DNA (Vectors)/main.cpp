#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
template<class T>
void printVec(vector<T> S){
	//just prints a vector-no spaces, but one element per line
	for (int i = 0; i < S.size(); i++){
		cout << S[i];
		cout << endl;
	}
}
*/

void getInput(vector<string> & S, int n){
	S.resize(n); //resizes to fit # of fragments
	for (int i = 0; i < n; i++){  //will loop through 'n' times to match number of fragments
		cin >> S[i];
	}
}

vector<string> concatenateFragments(vector<string> S){
	vector<string> temp;
	for (int i = 0; i < S.size(); i++){
		for (int j = 0; j < S.size(); j++){
			temp.push_back(S[i] + S[j]);
		}
	}
	return temp;
}

vector<string> findSubstrings(vector<string> TwoKStrings, vector<string> fragments){
	//Pre: Function assumes all TwoKStrings are the same length and arbitrarily uses 
	//the first word in the TwoKStrings vector to come up with the length of all the fragments
	vector<string> valid;
	string concatenatedWord, substringToCheck, fragment;
	int kMinus1Counter = 0, k;
	for (int i = 0; i < TwoKStrings.size(); i++){
		concatenatedWord = TwoKStrings[i];  //stores first concatenated word from TwoKStrings vector
		k = concatenatedWord.length() / 2; //k again denotes the length of each individual fragment
		// basically if the counter below reaches (k-1) in a length k substring, it allows the
		// concatenated word currently being examined into the valid word vector
		kMinus1Counter = 0;
		for (int j = 1; j - 1 < k - 1; j++){ //starting at index[1] and going till you're one letter short of the end of the word
			substringToCheck = concatenatedWord.substr(j, k); //part of substring we are comparing to original fragments
			for (int m = 0; m < fragments.size(); m++){
				fragment = fragments[m]; //fragments we are comparing substring too
				if (substringToCheck == fragment){
	kMinus1Counter++;
					break;   //the break is used so that if won't continue checking other fragments (thus saving time)
				}
			}
			if (kMinus1Counter == k - 1) //if the total # of substrings valid from the concatenated word equals k-1...
	valid.push_back(concatenatedWord); //add it to the valid vector
		}
	}
	return valid; //returns all valid words in a vector
}

int main(){
	vector<string> S;
	vector<string> concatenations;
	int p, n, t, k;

	cin >> p;
	while(p != 0){
		cin >> n >> t;
		getInput(S, n);

		k = S[0].length();  // k represents the length of letters in each individaul fragment
		concatenations = concatenateFragments(S);
		k *= 2;
		while (k < t){
			S = concatenations;
			concatenations = concatenateFragments(concatenations);
			k = concatenations[0].length();
			concatenations = findSubstrings(concatenations, S);
		}
		concatenations = findSubstrings(concatenations, S);
		cout << concatenations.size() << endl;
		p--;
	}
	return 0;
}

