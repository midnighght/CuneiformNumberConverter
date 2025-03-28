#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

#include <array>

// Define a constexpr array of 60 string elements
const std::array<std::string, 60> CUNEIFORM = {
    "𒀹", "𒁹", "𒈫", "𒐈", "𒐼", "𒐊", "𒐋", "𒑂", "𒑄", "𒑆",
    "𒌋", "𒌋𒁹", "𒌋𒈫", "𒌋𒐈", "𒌋𒐼", "𒌋𒐊", "𒌋𒐋", "𒌋𒑂", "𒌋𒑄", "𒌋𒑆",
    "𒎙", "𒎙𒁹", "𒎙𒈫", "𒎙𒐈", "𒎙𒐼", "𒎙𒐊", "𒎙𒐋", "𒎙𒑂", "𒎙𒑄", "𒎙𒑆",
    "𒌍", "𒌍𒁹", "𒌍𒈫", "𒌍𒐈", "𒌍𒐼", "𒌍𒐊", "𒌍𒐋", "𒌍𒑂", "𒌍𒑄", "𒌍𒑆",
    "𒑩", "𒑩𒁹", "𒑩𒈫", "𒑩𒐈", "𒑩𒐼", "𒑩𒐊", "𒑩𒐋", "𒑩𒑂", "𒑩𒑄", "𒑩𒑆",
    "𒑪", "𒑪𒁹", "𒑪𒈫", "𒑪𒐈", "𒑪𒐼", "𒑪𒐊", "𒑪𒐋", "𒑪𒑂", "𒑪𒑄", "𒑪𒑆"
};

// Function to convert a decimal number to another base
std::string decimalToHexagesimal(unsigned long long number) {
    if (number == 0) return "𒀹";
    std::string result;
    while (number > 0) {
        int remainder = number % 60;
        result = "·" + CUNEIFORM[remainder] + result;
        number /= 60;
    }
    
    return result;
}

// Function to get fractional part of a decimal number in another base
std::string getFractionalPart(long double decimals, int precision) {
    std::string fractionalPart;
    int counter = 0;
    while (decimals > 0 && counter < precision) {
        decimals *= 60;
        int fraction = static_cast<int>(decimals);
        fractionalPart += CUNEIFORM[fraction] + "·";
        decimals -= fraction;
        counter++;
    }
    
    return fractionalPart;
}

// General function for base conversion
std::string GeneralBaseConversion(const std::string& number, int precision) {
    
    size_t pointPos = number.find('.');
    if (pointPos == std::string::npos) {  // Integer conversion
            return decimalToHexagesimal(stoull(number));
    }
    else {  // Fractional number conversion
       
        std::string integerPart = GeneralBaseConversion(number.substr(0, pointPos), precision);
        std::string fractionalPart;
        
        fractionalPart = getFractionalPart(stold("0." + number.substr(pointPos + 1)), precision);

        return integerPart + ":" + fractionalPart;
    }
}

int main() {
    // Set UTF-8 output for Windows console
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif

    std::string result = GeneralBaseConversion("1.414213", 3);

    std::cout << "Cuneiform Representation: " << result << std::endl;

    return 0;
}