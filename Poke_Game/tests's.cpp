#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream file;
    file.open("results.txt");
    file << "hello";


}