#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    if(argc < 2) {
        cout << "Error you need an operation." << endl << "Try sysget help" << endl;
        exit(1);
    }

    string args;

    for(int i = 1; i < argc; i++) {
        args = args + argv[i] + " ";
    }

    string cmd = "sysget " + args;
    system(cmd.c_str());
    return 0;
}