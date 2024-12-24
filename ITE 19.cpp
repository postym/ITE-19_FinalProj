#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Helper function to get value of a Roman numeral
int romanValue(char ch) {
    switch (ch) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

// Converts a Roman numeral string to its decimal equivalent
int romanToDecimal(char *roman) {
    int total = 0, i = 0;
    while (roman[i]) {
        int current = romanValue(roman[i]);
        int next = romanValue(roman[i + 1]);
        if (current < next)
            total -= current; // Subtraction case
        else
            total += current; // Addition case
        i++;
    }
    return total;
}

// Perform arithmetic operations on two numbers
int performArithmetic(int num1, int num2, char op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        default: return 0; // Unsupported operation
    }
}

// Converts a number to its word equivalent
void decimalToWords(int num, char *output) {
    const char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    const char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    const char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const char *thousands[] = {"", "Thousand", "Million"};

    char buffer[512] = "";
    int thousandGroup = 0;

    if (num == 0) {
        strcpy(output, "Zero");
        return;
    }

    // Handle negative numbers
    if (num < 0) {
        strcat(buffer, "Negative ");
        num = -num;
    }

    while (num > 0) {
        int chunk = num % 1000;
        if (chunk > 0) {
            char chunkWords[100] = "";
            if (chunk / 100 > 0) {
                strcat(chunkWords, ones[chunk / 100]);
                strcat(chunkWords, " Hundred ");
            }
            if ((chunk % 100) >= 10 && (chunk % 100) < 20) {
                strcat(chunkWords, teens[chunk % 10]);
            } else {
                strcat(chunkWords, tens[(chunk % 100) / 10]);
                strcat(chunkWords, " ");
                strcat(chunkWords, ones[chunk % 10]);
            }
            if (thousandGroup > 0) {
                strcat(chunkWords, " ");
                strcat(chunkWords, thousands[thousandGroup]);
            }
            strcat(chunkWords, " ");
            strcat(chunkWords, buffer);
            strcpy(buffer, chunkWords);
        }
        num /= 1000;
        thousandGroup++;
    }

    strcpy(output, buffer);
}

// Process a single line of input
void processLine(char *line, FILE *out) {
    char roman1[100], roman2[100], op;
    if (sscanf(line, "%s %c %s", roman1, &op, roman2) != 3) {
        fprintf(out, "Invalid input\n");
        return;
    }

    // Convert Roman numerals to decimals
    int num1 = romanToDecimal(roman1);
    int num2 = romanToDecimal(roman2);

    if (num1 == 0 || num2 == 0) {
        fprintf(out, "Invalid Roman numeral\n");
        return;
    }

    // Perform the arithmetic operation
    int calculation = performArithmetic(num1, num2, op);

    // Write the result in words
    char resultInWords[512];
    decimalToWords(calculation, resultInWords);

    // Write the numeric result and the result in words to output
    fprintf(out, "%s\n", resultInWords);
}

// Process input and output files
void processFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), in)) {
        processLine(line, out);
    }

    fclose(in);
    fclose(out);
}

int main() {
    processFile("Input.txt", "Output.txt");
    return 0;
}
