#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

int main(){
    time_t clock;
    tm* tm;
    fstream notefile, temp;
    string newnotes, fnotes, line, clear;
    int n = 1, opt;
    unsigned int num, size;
    char clock_time[100];
    vector<string> notes {};
    while(true){
        time(&clock);
        tm = localtime(&clock);
        strftime(clock_time, 100, "| %A, %d %B %Y | %H:%M |", tm);
        notes.clear();
        notefile.open("notefile.txt", ios::in);
        while(getline(notefile, fnotes)){
            notes.push_back(fnotes);
        }
        notefile.close();
        size = notes.size();
        cout << "___________________________________\n" << clock_time << endl;
        cout << "Welcome to the Notes!\nWhat would you like to do?\n\n";
        cout << "1. View notes\n2. Add notes\n3. Remove notes\n4. Clear All notes\n5. Exit\n\n- ";
        cin >> opt;
        switch(opt){
            case 1:
                cout << "___________\n||" << notes.size() << " Notes||\nNotes :\n\n";
                if(notes.empty()){
                    cout << "You don't have any notes!\n";
                }
                else{
                    for(string x : notes){
                        cout << n << ". " << x << endl;
                        n++;
                    }
                }
                cout << "\nPress enter to go back!\n";
                cin.ignore();
                cin.get();
                n = 1;
                break;
            case 2:
                cout << "Type your notes here : \n";
                cin.ignore();
                getline(cin, newnotes);
                notefile.open("notefile.txt", ios::out|ios::app);
                if(notes.size() != 0){
                    notefile << endl;
                }
                notefile << newnotes;
                notefile.close();
                cout << "\nNotes added!\n";
                break;
            case 3:
                cout << "Insert the number of the notes you want to remove : ";
                cin >> num;
                if(num <= size && num > 0){
                    temp.open("temp.txt", ios::out);
                    notefile.open("notefile.txt", ios::in);
                    while(getline(notefile, line)){
                        if(line != notes[num - 1]){
                            temp << line;
                            if(notes[size - 1] == notes[num - 1]){
                                if(line != notes[size - 2]){
                                    temp << endl;
                                }
                            }
                            else{
                                if(line != notes[size - 1]){
                                    temp << endl;
                                }
                            }
                        }
                    }
                    temp.close();
                    notefile.close();
                    remove("notefile.txt");
                    rename("temp.txt", "notefile.txt");
                    cout << "\nNotes successfully removed!\n";   
                }
                else{
                    cout << "\nNotes not found!\n";
                }
                break;
            case 4:
                cout << "Are you sure you want to clear all notes?\nType 1 to confirm : ";
                cin.ignore();
                getline(cin, clear);
                if(clear == "1"){
                    remove("notefile.txt");
                    cout << "\nNotes successfully cleared!\n";
                }
                break;
            case 5:
                cout << "Exiting...\n___________________________________";
                return 0;
            default:
                cout << "\nInvalid number!\n";
        }
    }
}