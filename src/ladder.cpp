#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.h"
using namespace std;
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg){   cout << word1 << word2 << ": " << msg << endl;}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if(str1 == str2)
        return d>=1;

    int len1 = str1.length();
    int len2 = str2.length();

    if(abs(len1-len2)>1)
        return false;
    int x=0, y=0,checker=0;
    while(x<len1 &&y<len2){
        if(str1[x]!=str2[y]){
            if(checker == 1)
                return false;
            if(len1>len2)
                x++;
            else if(len1<len2)
                y++;
            else{
                x++;
                y++;
            }
            checker++;

        }else{
            x++;
            y++;
    }
    }

if(len1>x||len2>y){
    checker++;
}
return checker>=1;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1,word2,1);

}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word){
        return {"1"};}
    if (begin_word.length() != end_word.length()){
        return {"1", "2"};}
    if (word_list.find(begin_word) == word_list.end()){
        return {"1","2","3"};}
    if (word_list.find(end_word) == word_list.end()){
        return {"1","2","3","4"};}

    queue<vector<string>> lq;
    lq.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    
    vector<string> sp;
    while(!lq.empty()){
       vector<string> current = lq.front();
        lq.pop();
        string fin = current.back();
        for(const string&  word: word_list){
            if(is_adjacent(fin,word) && !visited.contains(word)){
                visited.insert(word);
                vector<string> newlad = current;
                newlad.push_back(word);
                if(word == end_word){
                    return newlad;
                    }
                lq.push(newlad);
    
            }
            }
        }
    cout << "hi";
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if(!file){
        error("", "", "file not found");
    }
    string in;
    while (file >> in) {
    word_list.insert(in);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) {cout << "No word ladder found." << endl;}
    else
    {
        cout << "Word ladder found: ";
        for (auto it = ladder.begin(); it != ladder.end(); it++)
        {
            cout << *it;
            if (it != ladder.end() - 1)
                cout << " ";
        }
        cout << " " << endl;
    }
}

