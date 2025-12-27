#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // for transform
#include <cctype>    // for tolower
#include <vector>
#include <sstream>
#include <set>
#include <iterator> // for inserter
using namespace std;

double compare(const string &str1, const string&str2);

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
        words.push_back(word);
    }
    return words;
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

    double result = compare(file1, file2);
    cout << "Similarity: " << result*100 << " %" << endl;
    return 0;
}
//checking similarity using jacard index method
double compare(const string &str1, const string &str2)
{

    vector<string> token1 = tokenize(str1);
    vector<string> token2 = tokenize(str2);

    // convert the vectors to ordered_sets to eliminate duplicates
    set<string> set1(token1.begin(), token1.end());
    set<string> set2(token2.begin(), token2.end());

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