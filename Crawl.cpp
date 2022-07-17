#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

int count, pages, each_page;
string url, text, img, file, find_img = "<img src=\"https://voz.vn/attachment"; // pattern to dectect data

void input() {
    cout << "Link: ";
    cin >> url;
    cout << "Number of Pages: ";
    cin >> pages;
}

void get_data() {
        for (int each_page = 1; each_page <= pages; each_page++) { // get data each page
        system(("wget -O VOZ.txt --user-agent=\"Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0\" " + url + "page-" + to_string(each_page)).c_str()); //download current page
        }
}

void commit() {
        fstream f1("VOZ.txt");

        while (getline(f1, text)){// get data current page
            if (text.find(find_img) != string::npos) {
                for (int i = 0; i <= text.length() - 2; i++) {
                    if (text[i] == char(34) && text[i + 1] == char(32)) {
                        img = text.substr(10,i - 10);
                        time_t now = time(0);
                        system(("wget --user-agent=\"Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0\" " + img + " -O Photo_" + to_string(now) + ".jpg").c_str()); // download data
                        count++;
                        cout << img << endl; // show link of data
                        cout << endl;
                        break;
                    }             
                }
            }
        }

        f1.close();
}

int main() {
    input();
    get_data();
    commit();
}