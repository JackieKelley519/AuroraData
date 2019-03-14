#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    std::ofstream out_data("irb_update.txt");

    int i = 0;
    std::ifstream ifs("irb_data.txt");
    std::string inString( (std::istreambuf_iterator<char>(ifs)),
                          (std::istreambuf_iterator<char>()  ));

    string  outString;

    const iterator_traits<string::iterator>::difference_type
    numberOfWords = count_if( inString.begin(), inString.end(),
                    bind2nd(equal_to<char>(), ',')) + 1;

    string::size_type  startIndex, endIndex;

    outString.reserve(inString.length() + numberOfWords);

    for (startIndex = endIndex = 0; endIndex != string::npos;
            startIndex = endIndex + 1 ) {

        outString += ("\"Document-" + std::to_string(i) + ("\" : {"));
        i++;

    /* No startIndex+1 here.  We set startIndex=endIndex+1 in the for loop */
        endIndex = inString.find_first_of("{", startIndex);

        outString.append(inString, startIndex,
            ((endIndex == string::npos) ? string::npos :
                endIndex - startIndex - 1));
  }
  out_data << outString;
}
