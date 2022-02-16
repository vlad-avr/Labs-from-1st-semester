
#include <iostream>
#include <fstream>
#include<cstring>

using namespace std;

/*TASK
The text is stored inside a text file and it contains duplicates and odd spaces, which must be cleared. Then the text must be printed allinged to the left border of the window.

*/

/*Checks whether the character is a letter or number and not a punctuation mark*/
bool is_char(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    else if (c >= 'A' && c <= 'Z') {
        return true;
    }
    else if (c >= '0' && c <= '9') {
        return true;
    }
    else {
        return false;
    }
}

bool is_upper_case(char c) {
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    else {
        return false;
    }
}
/*Compares 2 words to find out whether they are duplicates*/
bool is_duplicated(char str1[], char str2[]) {

    if (is_upper_case(str1[0]) || is_upper_case(str2[0])) {
        str1[0] = str2[0];
    }
    
    for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++) {
        if (str1[i] != str2[i])
            return false;
    }
    return true;
}



void Convert_line(char line[], int max_length) {
    char prev[20];
    char cur[20];
    int line_length = 0;
    for (int i = 0; line[i] != '\0'; i++) {
        if (is_char(line[i])) {
            int k = 0;
            for (int j = i; is_char(line[j]); j++, k++) {
                cur[k] = line[j];
            }
            i += k - 1;
            cur[k] = '\0';
            if (!is_duplicated(prev, cur)) {
                if (line_length + strlen(cur) >= max_length) {
                    cout << "\n";
                    line_length = 0;
                    cout << cur;
                }
                else {
                    cout << " " << cur;
                }
                line_length += strlen(cur)+1;
            }
            strcpy_s(prev, cur);
        }
        else if (line[i] == ' ') {
            continue;
        }
        else {
            line_length++;
            cout << line[i];
            strcpy_s(prev, "\0");
        }
    }

}

int main()
{
    ifstream input_file;
    /*My file with input was stored on my Desktop*/
    input_file.open("C:\\Users\\USER\\Desktop\\LAB_6_INPUT.txt");
    
    /*Reads the text by paragraphs*/
    char line[1000];
    while (!input_file.eof()) {
        input_file.getline(line, 1000, '\n');
        Convert_line(line, 50);
        cout << endl;
    }
    
    input_file.close();
}
