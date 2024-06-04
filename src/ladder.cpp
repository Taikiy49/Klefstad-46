#include "ladder.h"

bool edit_distance_within(const std::string & str1, const std::string & str2, int d){
    int m = str1.length();
    int n = str2.length();
    string word, word2;
    bool flag = false;
    if (str1==str2) return true;
    if (m>n){
        word = str1;
        word2 = str2;
    }
    else{
        word = str2;
        word2 = str1;
    }
    string temp;
    for (int i = 0; i < word.length(); ++i){
        if (i==0) temp = word.substr(i+1);
        else temp = word.substr(0,i)+word.substr(i+1);
        if (temp==word2) flag = true;
    }
    return flag;
}

bool is_adjacent(const string & word1, const string & word2){
    int len1 = word1.length();
    int len2 = word2.length();
    if (len1 - len2 > 1 || len2 - len1 > 1) return false;
    if (len1==len2){
        int diffCount = 0;
        if (word1==word2) return true;
        for (int i=0; i < len1; ++i){
            if (word1[i] != word2[i]) diffCount++;
            if (diffCount > 1) return false;
        }
        return diffCount == 1;
    }
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string & begin_word, const string & end_word, const set<string> & word_list){
    if (begin_word == end_word) {
        cerr << "Error: Start and end words are the same." << endl;
        return {};}

    if (word_list.find(end_word) == word_list.end()) {
    cerr << "Error: End word is not in the word list." << endl;
    return {};}
    
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();
        for (const string & word : word_list){
            if (is_adjacent(last_word, word)){
                if (visited.find(word) == visited.end()){
                    visited.insert(word);

                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string & file_name){
    ifstream file(file_name);
    string word;
    while (file >> word) word_list.insert(word);
    file.close();
}

void print_word_ladder(const vector<string> & ladder){
    if (ladder.empty()) cout << "No word ladder found." << endl;
    else{
        cout << "Word ladder found: ";
        for (const string & word : ladder) cout << word << " ";
        cout << endl;
    }
}


#define my_assert(e) { cout << #e << ((e) ? " passed" : " failed") << endl; }

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}