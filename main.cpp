// Project UID db1f506d06d84ab787baf250c265e24e

#include "csvstream.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <exception>


using namespace std;

// EFFECTS: Returns a set containing the unique "words" in the original
//          string, delimited by whitespace.
set<string> unique_words(const string& str) {
    istringstream source(str);
    set<string> words;
    string word;

    // Read word by word from the stringstream and insert into the set
    while (source >> word) {
        words.insert(word);
    }
    return words;
}

class Classifier
{
private:
    int numPosts;
    int numWords;
    map<string, int> postsPerWord;
    map<string, int> postsPerLabel;
    map<pair<string, string>, int> postsPerPair;

public:

    Classifier()
        :numPosts(0), numWords(0) {}

    int getNumPosts()
    {
        return numPosts;
    }

    int getNumWords()
    {
        return numWords;
    }

    void addPost()
    {
        numPosts++;
    }
    
    void addLabel(const string &label)
    {
        bool found = false;
        for (auto it = postsPerLabel.begin(); it != postsPerLabel.end(); it++)
        {
            if (it->first == label)
            {
                it->second++;
                found = true;
            }
        }
        if (!found)
        {
            postsPerLabel[label] = 1;
        }
    }

    void setPostsPerWord(const set<string> &words, const set<string> &Content)
    {
        for (auto it = words.begin(); it != words.end(); it++)
        {
            numWords++;
            postsPerWord[*it] = 0;
            for (auto iter2 = Content.begin(); iter2 != Content.end(); iter2++)
            {
                if (isWordPresent(*it, *iter2))
                {
                    postsPerWord[*it] += 1;
                }
            }
        }
    }

    void setPostsPerPair(string filename)
    {
        for (auto it = postsPerLabel.begin(); it != postsPerLabel.end(); it++)
        {
            for (auto iter2 = postsPerWord.begin(); 
                iter2 != postsPerWord.end(); iter2++)
            {
                csvstream csvin(filename);
                map<string, string> row;
                postsPerPair[{it->first , iter2->first}] = 0;
                while (csvin >> row)
                {
                    if (row["tag"] == it->first && 
                        isWordPresent(iter2->first, row["content"]))
                    {
                        postsPerPair[{it->first, iter2->first}] += 1;
                    }
                }
                row.clear();
            }
        }
    }

    bool isWordPresent(const string& word, const string& post)
    {
        stringstream stream(post);
        string words;
        while (stream >> words)
        {
            if (words.compare(word) == 0)
            {
                return true;
            }
        }
        return false;
    }


    void printLabelMap()
    {
        for (auto it = postsPerLabel.begin(); it != postsPerLabel.end(); it++)
        {
            cout << it->first << ": " << it->second << endl;
        }
    }

    void printWordMap()
    {
        for (auto it = postsPerWord.begin(); it != postsPerWord.end(); it++)
        {
            cout << it->first << ": " << it->second << endl;
        }
    }

    void printPostsPerPair()
    {
        for (auto it = postsPerPair.begin(); it != postsPerPair.end(); it++)
        {
            pair<string, string> p = it->first;
            cout << "{" << p.first << ", " << 
                p.second << "} "<< ": " << it->second << endl;
        }
    }

};

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4)
    {
        return 0;
    }
    cout.precision(3);

    Classifier a;
    string file = argv[1];
    csvstream csvin(file);
    string allPosts = "";

    map<string, string> row;
    while (csvin >> row) {
        a.addPost();
        a.addLabel(row["tag"]);
        allPosts += row["content"] + " ";
    }
    row.clear();

    csvstream insertContent(file);
    set<string> unique = unique_words(allPosts);
    set<string> postContent;
    while (insertContent >> row)
    {
        postContent.insert(row["content"]);
    }
    row.clear();
    a.setPostsPerWord(unique, postContent);
    a.setPostsPerPair(file);

    cout << "trained on " << a.getNumPosts() << " examples";

}
