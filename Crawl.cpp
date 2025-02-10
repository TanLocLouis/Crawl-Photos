#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void input(int& numPages, string& url) {
    cout << "Link without page-n: ";
    cin >> url;
    cout << "Number of pages: ";
    cin >> numPages;
}

void commit(string filename, int& count) {
        fstream f1(filename);

        string text, img_link;
        string imgPattern = "<img src=\"https://voz.vn/attachment"; // pattern to dectect data
        while (getline(f1, text)){ // get data current page
            if (text.find(imgPattern) != string::npos) {
                for (int i = 0; i < text.length() ; i++) {
                    if (text[i] == '\"') {
                        img_link = text.substr(i + 1, text.length() - i - 2); // get link of image
                        string cmd = "curl -A \"Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0\" -o Photo_" + std::to_string(count) + ".jpg \"" + img_link + "\"";
                        system(cmd.c_str());
                        count++;

                        cout << endl;
                        cout << "------------------------------------------------------------------" << endl;
                        cout << img_link << endl; // show link of image
                        cout << "------------------------------------------------------------------" << endl;
                        cout << endl;

                        break;
                    }             
                }
            }
        }
        f1.close();
}

void get_data(int numPages, string url) {
    int count = 0;
    for (int eachPage = 1; eachPage <= numPages; eachPage++) {
        cout << "------------------------------------------------------------------" << endl;
        cout << "Downloading page " << eachPage << "..." << endl;
        cout << "------------------------------------------------------------------" << endl;
        string cmd = "curl.exe -A \"Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0\" -o VOZ.txt " + url + "page-" + to_string(eachPage); // get data from current page
        system(cmd.c_str()); // get images' link from current page
        commit("VOZ.txt", count); // download images
    }
}

int main() {
    int numPages;
    string url;

    input(numPages, url);
    get_data(numPages, url);
}