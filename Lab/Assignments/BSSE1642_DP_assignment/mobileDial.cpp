#include <bits/stdc++.h>
using namespace std;

map<char, pair<int, int>> keypad = {
    {'1', {0, 0}}, {'2', {1, 0}}, {'3', {2, 0}}, {'4', {0, 1}}, {'5', {1, 1}}, {'6', {2, 1}}, {'7', {0, 2}}, {'8', {1, 2}}, {'9', {2, 2}}, {'*', {0, 3}}, {'0', {1, 3}}, {'#', {2, 3}}};

double distance(char key1, char key2)
{
    int x1 = keypad[key1].first;
    int y1 = keypad[key1].second;
    int x2 = keypad[key2].first;
    int y2 = keypad[key2].second;

    double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    return (int)(dist * 2 + 0.5) / 2.0;
}

double minEffort(string number, char leftPos, char rightPos, int index, map<string, double> &dp)
{
    if (index >= number.length())
    {
        return 0;
    }

    string key = to_string(index) + "_" + leftPos + "_" + rightPos;
    if (dp.find(key) != dp.end())
    {
        return dp[key];
    }

    char digit = number[index];

    double costLeft = distance(leftPos, digit) +
                      minEffort(number, digit, rightPos, index + 1, dp);

    double costRight = distance(rightPos, digit) +
                       minEffort(number, leftPos, digit, index + 1, dp);

    dp[key] = min(costLeft, costRight);
    return dp[key];
}

int main()
{
    string phoneNumber;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

    map<string, double> dp;
    double result = minEffort(phoneNumber, '*', '#', 0, dp);

    cout << "Phone number: " << phoneNumber << endl;
    cout << "Minimum effort: " << result << endl;

    return 0;
}