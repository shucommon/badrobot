#include <fstream>
using namespace std;

const int cutoff = 6000;
const float rate1 = 0.3;
const float rate2 = 0.6;

int main()
{
    ifstream infile;
    ofstream outfile;
    int income, tax;
    infile.open("income.in");
    outfile.open("tax.out");
    while(infile >> income) {
        if(income < cutoff)
            tax = rate1 * income;
        else
            tax = rate2 * income;
        outfile << "Income = " << income
                << " greenbacks\n"
                << "Tax = " << tax
                << " greenbacks\n";
    }
    infile.close();
    outfile.close();
    return 0;
}
