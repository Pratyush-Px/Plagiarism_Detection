#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // for transform
#include <cctype>    // for tolower
#include <vector>
#include <sstream>
#include <set>
#include <unordered_set>
#include <iterator> // for inserter

using namespace std;
// function pointer instead of generic functio.
using GramFunction = vector<string> (*)(const vector<string>&, size_t); //A pointer to a function that takes vector<string> and unsigned and returns vector<string>

const unordered_set<string> stopWords = {
    "the", "is", "and", "a", "an", "to", "of", "in", "on", "for",
    "with", "at", "by", "from", "as", "are", "was", "were", "be"
};

 
double compare(const vector<string> &token1, const vector<string> &token2, GramFunction make_ngrams, size_t n);
vector<string> make_ngrams(const vector<string> &tokens, size_t n);

string readfile(const string &filename)
{
    ifstream readfile(filename);
    if (!readfile.is_open())
    {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(1);
    }
    string str;
    string file_contents;
    while (getline(readfile, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
    }
    readfile.close();
    return file_contents;
}

string normalise(const string &text)
{
    string result;
    for (char ch : text)
    {
        if (isalnum(ch) || ch == ' ')
        {
            result += tolower(ch);
        }
        else
        {
            result += ' '; // Replace punctuation characters with space
        }
    }
    return result;
}

vector<string> tokenize(const string &text)
{
    vector<string> words;
    string word;
    stringstream ss(text);

    while (ss >> word)
    {
        if (stopWords.find(word) == stopWords.end()) { //check if word is not a stop word
            words.push_back(word);
        }
    }
    return words;
}

//n-gram generation (trigrams)
vector<string> make_trigrams(const vector<string> &tokens) {
    vector<string> trigrams;

    for (size_t i = 0; i + 2 < tokens.size(); i++) {  //size_t is unsigned intege type returned by container.size() method , container cannot have negative size!!
        trigrams.push_back(tokens[i] + " " + tokens[i + 1] + " " + tokens[i + 2]);
    }

    return trigrams;
}

vector<string> make_bigrams(const vector<string> &tokens){
    vector<string> bigrams;

    for(size_t i = 0; i+1 < tokens.size(); i++){
        bigrams.push_back(tokens[i] + " " + tokens[i+1]);
    }
    return bigrams;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: ./check <file1> <file2>" << endl;
        return 1;
    }
    string file1 = readfile(argv[1]);
    // cout << file1;
    string file2 = readfile(argv[2]);
    // cout << file2;

    file1 = normalise(file1);
    file2 = normalise(file2);

    //tokenise
    vector<string> token1 = tokenize(file1);
    vector<string> token2 = tokenize(file2);

    double unigram_result = compare(token1, token2, make_ngrams, 1);
    double bigram_result = compare(token1, token2, make_ngrams, 2);
    double trigram_result = compare(token1, token2, make_ngrams, 3);

    cout << "Unigram Similarity: " << unigram_result * 100 << "%" << endl;  
    cout << "Bigram Similarity: " << bigram_result * 100 << "%" << endl;
    cout << "Trigram Similarity: " << trigram_result * 100 << "%" << endl;

   double final_score = 0.2 * unigram_result + 0.4 * bigram_result + 0.4 * trigram_result;
    
    cout << "Final Similarity Score: " << final_score * 100 << "%" << endl;
    return 0;
}
//checking similarity using jacard index method

double compare(const vector<string> &token1, const vector<string> &token2, GramFunction make_grams, size_t n)
{
    vector<string> grams1 = make_grams(token1, n);
    vector<string> grams2 = make_grams(token2, n);

    // convert the vectors to ordered_sets to eliminate duplicates! complexity: (O(log n) for set operations)
    set<string> set1(grams1.begin(), grams1.end());
    set<string> set2(grams2.begin(), grams2.end());

    //find intersection and union
    set<string> intersection;
    set<string> uni;

    set_intersection(
        set1.begin(), set1.end(),
        set2.begin(), set2.end(),
        inserter(intersection, intersection.begin()));

    set_union(
        set1.begin(), set1.end(),
        set2.begin(), set2.end(),
        inserter(uni, uni.begin()));

    
    double jaccard_similarity = 0.0;
    if(!uni.empty()){
        jaccard_similarity = static_cast<double>(intersection.size()) / static_cast<double>(uni.size());
        return jaccard_similarity;
    }else{
        return 0.0;
    }

}

vector<string> make_ngrams(const vector<string> &tokens, size_t n) {
    vector<string> ngrams;

    if (tokens.size() < n || n == 0) return ngrams;

    for (size_t i = 0; i + n <= tokens.size(); i++) {
        string gram = tokens[i];
        for (size_t j = 1; j < n; j++) {
            gram += " " + tokens[i + j];
        }
        ngrams.push_back(gram);
    }

    return ngrams;
}
