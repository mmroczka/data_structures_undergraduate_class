#include <iostream>
#include <cmath> // for square root function
#include <algorithm>
#include <vector>
using namespace std;
 
struct Primes{
	vector<int> primeVector; //this vector holds all primes that could possibly be used in a given test case
	vector<int> numbersToUse; //this vector holds all numbers that are in the current sequence we are checking
	bool sequenceFound = false;
	int numTotal;
	Primes(int first, int last){
		/*
		    name   : Primes
			purpose: it sets several class variables, builds a prime object and also calls the getPrimes function to generate all primes relevant in this instance
			called
			pre    : assumes 0 < first < last. You consequently can't use negatives. Also assumes last can be stored within integer range and is not a double
			post   : makes all primes between first and last as well as all primes smaller than first+first+1
			called
			by     : main
		*/
		UpperLimit = last + last;
		firstNumber = first; // <— this is used later in the getPrimes function at the end to eliminate checking primes that are too small
		numTotal = last - first + 1;
		numbersToUse.resize(numTotal);
		for (int i = 0; i < numTotal; i++)
			numbersToUse[i] = first + i;
		getPrimes();
	}
	void getPrimes(){
		/*
		   *NOTE* This function uses the sieve of eratosthenes, and it's implementation was adapted from an online resource located here: http://www.geeksforgeeks.org/sieve-of-eratosthenes/
		    name   : getPrimes
			purpose: This function generates a list of prime numbers between (first*first and last*last) using the
			         sieve of eratosthenes and stores it in the class vector called primeVector. We don't care about
					 numbers greater than twice the size of the last element since we are never going to multiply numbers bigger than that.
			called
			pre    : assumes Upperlimit is last+last and that last was non-negative. 
			         Assumes the back element in the numberToUse array is the largest element in the array.
					 Assumes vector is sorted smallest to largest
			post   : Assumes that after the function is done, primeVector contains a series of sorted ints that are prime
			called
			by     : Primes
		*/
		vector<bool> isPrime(UpperLimit);
		for (int i = 0; i < UpperLimit; i++) //sets all to true for the marking
			isPrime[i] = true;
		for (int i = 2; i < UpperLimit; i++) //run through all numbers greater than 2 but still less than the highest number
			if (i <= sqrt(UpperLimit) && isPrime[i] == true) // if it's less than the max number's square root and it has been marked as true
				for (int j = 2 * i; j < UpperLimit; j++) // run through all numbers setting the mutliple of that new prime equal to false
					if (j % i == 0)
						isPrime[j] = false;

		for (int i = 2; i < UpperLimit; i++)
			if (isPrime[i] == true && i > firstNumber+firstNumber) // if it's a prime number & the number is bigger than twice the value of the smallest number in the sequence
				primeVector.push_back(i);
	}

	bool isPrime(int n){
		/*
		    name   : isPrime
			purpose: this function runs the the vector primeVec and checks to see if 'n'
			         matches any of the integers in primeVec. If it does, it returns true, if it doesn't it returns false.
			called
			pre    : Assumes n is non-zero. IT DOES NOT ACTUALLY CHECK IF THE NUMBER IS PRIME! It merely looks to see if the number matches the number in the primeVec.
			         This was done intentionally, to make look-up times constant, that way we wouldn't have to calculate all primes including n every time we needed to look it up.
			post   : assumes that if n isn't in primeVec the number ISN'T prime. Assumes primeVec was generated correctly
			called
			by     : main
		*/

		for (int i = 0; i < primeVector.size(); i++){
			if (primeVector[i] == n)
				return true;
		}
		return false;
	}

	void recursion(vector<int> soFar, vector<int> numbersLeft){
		/*
		    name   : recursion
			purpose: checks to see if the vector soFar plus one element from numbersLeft is a prime sequence, if it is
			         it recursively calls itself again. once numbersLeft is empty, it prints the sequence then stops all
					 further recursions
			called
			pre    : assumes primeVec was built correctly, assumes everything in soFar is prime initially (or empty). assumes numbersLeft contains all values necessary
			         assumes values are non-negative and that numbersLeft is a list of sorted numbers
			post   : assumes soFar contains the answer of all numbersLeft integers made into a prime sequence. if the sequence doesn't exist, 
			         it does NOT update the class boolean sequence to true. this later is important in the program to make it print out that the sequence doesn't exist.
			called
			by     : main
		*/
		for (int i = 0; i < numbersLeft.size() && sequenceFound == false && soFar.size() != numTotal; i++){
			//sort(numbersLeft.begin(), numbersLeft.end());
			vector<int> nextIteration = soFar;
			vector<int> newNumbersLeft = numbersLeft;
			if (isPrime(soFar.back() + numbersLeft[i])){
	nextIteration.push_back(newNumbersLeft[i]);  // add one number to the sequence
	newNumbersLeft.erase(newNumbersLeft.begin() + i); //and subtract one number from the old list
				recursion(nextIteration, newNumbersLeft);
			}
		}
		if (sequenceFound == false && soFar.size() == numTotal){
			printVec(soFar);
			sequenceFound = true;
		}
	}

	void printVec(vector<int> vectorToPrint){
		/*
		    name   : printVec
			purpose: prints the vector that is passed to it with spaces separating each element
			called
			pre    : assumes vectorToPrint is not empty
			post   : assumes you wanted to have spaces between each element and one extra one at the end of the sequence
			called
			by     : recursion
		*/
		for (int i = 0; i < vectorToPrint.size(); i++)
			cout << vectorToPrint[i] << " ";
		cout << endl;
	}

private:
	int UpperLimit;
	int firstNumber;
};

int main(){
	int testCases, firstNumber = 1, lastNumber = 1;
	bool done = false;
	while (!done){
		cin >> firstNumber >> lastNumber;
		if (firstNumber == 0 && lastNumber == 0){
			done = true;
			break;
		}
		//lists primes that are in range of useable numbers
		Primes test(firstNumber, lastNumber); // creates object with range of useable numbers as well as primes within reach of those numbers
		//BELOW WAS USED FOR TESTING PURPOSES
		//cout << "All primes in range are: \n";
		//test.printVec(test.primeVector);
		//cout << endl;
		vector<int> soFar;
		vector<int> soGood = test.numbersToUse;
		for (int root = 0; root < test.numTotal; root++){
			soFar.push_back(soGood[root]);
			soGood.erase(soGood.begin() + root);
			test.recursion(soFar, soGood);
			if (test.sequenceFound == true)
				break;
			soFar.clear();
			soGood = test.numbersToUse;
		}
		if (test.sequenceFound == false)
			cout << "No prime sequence exists\n";
	}
	return 0;
}
