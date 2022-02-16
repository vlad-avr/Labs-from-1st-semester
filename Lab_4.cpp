#include<cmath>
#include <iostream>
#include<time.h>
using namespace std;

/*2)	Find common substring for 2 strings*/
void SubStr(char* X, char* Y, int m, int n)
{

    int** Arr = new int*[m+1];
    for (int i = 0; i < m + 1; i++) {
        Arr[i] = new int[n + 1];
    }
    int max_length = 0;
    int i_end = 0;
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {

            if (i == 0 || j == 0) {
                Arr[i][j] = 0;
            }
            else if (X[i - 1] == Y[j - 1]) {
                Arr[i][j] = Arr[i - 1][j - 1] + 1;
                
                if (max_length < Arr[i][j]) {
                    max_length = Arr[i][j];
                    i_end = i;
                }
            }
            else {
                Arr[i][j] = 0;
            }
        }
    }
    cout << i_end << "\t";
    cout << "The longest common substring is:  ";
    for (int i = i_end - max_length; i < i_end; i++) {
        cout << X[i];
    }
    for (int i = 0; i <= m; i++) {
        delete[] Arr[i];
    }
    delete[] Arr;
}

/*5)	The array of positive integer numbers ia given. Put '+' and '-' between them in such way that their sum is equal to 0. If it's impossible, print the appropriate message. */

/* Recursion that finds the sequence of numbers from given array that is equal to the half of the sum of array*/
bool Subset_sum(int*& arr, int sub_sum, int counter, int length) {
    if (sub_sum == 0) {
        return true;
    }
    else if (sub_sum < arr[length]) {
        return false;
    }
    
    for (int i = counter; i <= length; i++) {
        if (sub_sum >= arr[i]) {
            if (Subset_sum(arr, sub_sum - arr[i], i + 1, length)) {
                arr[i] = -arr[i];
                return true;
                break;
            }
            else {
                continue;
            }
        }
        else {
            if (Subset_sum(arr, sub_sum, i + 1, length)) {
                return true;
                break;
            }
            else {
                continue;
            }
        }
    }
    return false;
}


/*Main function of the task*/
void Array_To_Zero() {
    int n;
    bool is_possible = true;
    cout << "Enter the number of items: \t";
    cin >> n;
    int* arr = new int[n];
    int sum = 0;
    srand(time(0));
    for (int i = 0; i < n-1; i++) {
        /*Current code creates the sequaence of random numbers that match all the necessary requirements and will come down to 0 (for manual input the code must be changed but unfortunately I don't remember how)*/
        /*cin >> arr[i];
         sum += arr[i];*/
        arr[i] = rand() + 50000;
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
        else {
           sum -= arr[i];
        }
    }
    arr[n-1] = abs(sum);
    
    sum = 0;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << '\t';
        sum += arr[i];
    }
    cout << sum/2 << '\t';
    if (sum % 2 != 0) {
        is_possible = false;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] > sum / 2) {
            is_possible = false;
            break;
        }
    }
    if (is_possible) {

        int half_sum = sum / 2;
        sum = half_sum;
        is_possible = Subset_sum(arr, half_sum, 0, n - 1);
        if (is_possible) {
            for (int i = 0; i < n; i++) {
                if (arr[i] >= 0) {
                    sum -= arr[i];
                }
            }
            if (sum == 0) {
                for (int i = 0; i < n; i++) {
                    if (arr[i] < 0) {
                        cout << arr[i];
                    }
                    else {
                        cout << "+" << arr[i];
                    }
                }
            }
            else {
                cout << "  IMPOSSIBLE: leftover numbers do NOT match the necessary requirements  " << endl;
            }
        }
        else {
            cout << "  IMPOSSIBLE: unable to find given subset sum  " << endl;
        }
    }
    else {
        cout << "  SUM OF THE SEQUENCE IS NOT EVEN OR ONE OF ITS ELEMENTS IS GREATER THAN THE HALF OF ITS SUM  " << endl;
    }
    delete[] arr;
}

int main()
{
    /*Task about numeric sequence*/
    int a = 1;
    while (a == 1) {
        Array_To_Zero();
        cin >> a;
    }
    /*Task about finding longest common substring*/
    /*char X[] = "ABC";
    char Y[] = "123ABC";

    int m = strlen(X);
    int n = strlen(Y);

    SubStr(X, Y, m, n);
    return 0;*/
}


