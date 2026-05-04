#include <iostream>        // Allows input/output like cout and cin
#include <fstream>         // For file handling (like reading txt files)
#include <sstream>         // For breaking lines or strings into pieces
#include <cctype>
#include <ctime>   // For time(0) — used in seeding srand()
#include <unordered_map>   // Stores key-value pairs for emotions and their keywords
#include <vector>          // To store a list of words or strings
#include <algorithm>       // For things like converting to lowercase
using namespace std;
unordered_map<string, vector<string>> emotionKeywords;

void loadEmotionKeywords(const string& filename) {
    ifstream file(filename);  // Open the file
    string line;

    while (getline(file, line)) { // Read line by line
        stringstream ss(line);
        string emotion, keywords_str;

        getline(ss, emotion, ':');           // Get the emotion (e.g., "sadness")
        getline(ss, keywords_str);           // Get the rest of the line (all keywords)

        stringstream keyword_stream(keywords_str);
        string keyword;
        vector<string> keywords;

        while (getline(keyword_stream, keyword, ',')) {
            // Remove leading/trailing spaces
            keyword.erase(0, keyword.find_first_not_of(" \t"));
            keyword.erase(keyword.find_last_not_of(" \t") + 1);
            keywords.push_back(keyword);
        } 

        emotionKeywords[emotion] = keywords;  // Save the list to the map
    }
}
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
pair<string, int> detectEmotion(const string& userInput) {
    string input = toLowerCase(userInput);
    unordered_map<string, int> emotionMatchCount;

    for (auto& pair : emotionKeywords) {
        string emotion = pair.first;
        vector<string> keywords = pair.second;

        for (string keyword : keywords) {
            if (input.find(keyword) != string::npos) {
                emotionMatchCount[emotion]++;
            }
        }
    }

    string detectedEmotion = "";
    int maxMatches = 0;

    for (auto& pair : emotionMatchCount) {
        if (pair.second > maxMatches) {
            maxMatches = pair.second;
            detectedEmotion = pair.first;
        }
    }

    return {detectedEmotion, maxMatches};
}


string getRandomLineFromFile(const string& filename) {
    ifstream file(filename);
    vector<string> lines;
    string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    if (lines.empty()) return "Sorry, I don't have a response right now.";

    srand(time(0));
    int index = rand() % lines.size();
    return lines[index];
} // for isspace

// Helper function to trim whitespace from both ends of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos)
        return ""; // string is all whitespace

    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

string getComfortResponse(const string& emotion) {
    ifstream file("Comfort.txt");
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(":");
        if (pos != string::npos) {
            string key = toLowerCase(trim(line.substr(0, pos)));
            string response = trim(line.substr(pos + 1));
            if (key == emotion) {
                return response;
            }
        }
    }
    return "I'm here for you. Feel free to talk.";
}
void printFileContent(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void respondBasedOnEmotion(const string& emotion, int matchCount) {
    if (emotion == "greetings") {
        cout <<getRandomLineFromFile("Greetings.txt") << endl;
    } else if (emotion == "listening") {
        cout << getRandomLineFromFile("listening.txt") << endl;
    }else if (matchCount <= 2) {
        cout << getComfortResponse("Comfort.txt") << endl;
    } else if(matchCount>2 && emotion=="Sadness/Depression"){
         printFileContent("Sadness_Depression.txt") ;
    }else if(matchCount>2 && emotion=="Anger/Frustration"){
         printFileContent("Anger_Frustration.txt");
    }else if(matchCount>2 && emotion=="Anxiety/Fear"){
         printFileContent("Anxiety_Fear.txt") ;
    }else if(matchCount>2 && emotion=="Confusion/Hopelessness"){
         printFileContent("Confusion_Hopelessness.txt") ;
    }else if(matchCount>2 && emotion=="Shame/Guilt"){
         printFileContent("Shame_Guilt.txt") ;
    }else if(matchCount>2 && emotion=="Stress/Overwhelm"){
         printFileContent("Stress_Overwhelm.txt");
    }else if(matchCount>2 && emotion=="Loneliness/Isolation"){
         printFileContent("Loneliness_Isolation.txt") ;
    }else if(matchCount>2 && emotion=="Insecurity/LowSelfWorth"){
         printFileContent("Insecurity_LowSelfWorth.txt");
    }else{
        cout << "Mental Health Bot 🤖: Take care of yourself. I'm always here if you need to talk." << endl;
    }
   

}




int main() {
    loadEmotionKeywords("emotions_detection.txt");
    while(true){
    cout << "You:\n";
    string userInput;
    getline(cin, userInput);  // Take full line input from user
    auto result = detectEmotion(userInput);
    string emotion = result.first;
    int matchcount = result.second;
    cout<< emotion << endl;
    cout<< matchcount << endl;
    respondBasedOnEmotion(emotion, matchcount);
   }

    return 0;
}
