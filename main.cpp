
// Includes necessary libraries
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

// Function to input data points into two vectors
void inputData(vector<int>& x, vector<int>& y) {
    int size;
  
    // Asking for the number of data points to be inputted
    cout << "Enter the number of data points you want to input: ";
    cin >> size;

    cout << "Please enter values for x and y:" << endl;
    for(int i=0; i<size; i++) {
        int value;
        // Input x values
        cout << "x["<<i<<"]: ";
        cin >> value;
        x.push_back(value);
        
        // Input y values
        cout << "y["<<i<<"]: ";
        cin >> value;
        y.push_back(value);
    }
}

// Function to calculate R-squared (R2), a statistical measure 
float R2(float w_opt,float b_opt, const vector<int>& x, const vector<int>& y, float y_mean)
{
    float fi;
    float ssRES = 0;   // Residual sum of squares
    float ssTOT = 0;   // Total sum of squares
    float R2;

    // Calculation of residual sum of squares
    for (int i = 0; i <= x.size(); i++)
    {
        fi = w_opt * x[i] + b_opt;
        ssRES += (y[i] - fi)*(y[i] - fi);

    }

    // Calculation of total sum of squares
    for (int i = 0; i < x.size(); i++)
    {
        ssTOT += (y[i] - y_mean)*(y[i] - y_mean);
    }
    
    // Calculation of R-squared (R2)
    R2 = 1 - (ssRES/ssTOT);
    return(R2);
}

// Function to calculate variance
float varianceX(const vector<int>& x, float x_mean)
{
    float sum2 = 0, var = 0;
    // calculating the variance
    for (int i = 0; i < x.size(); i++)
    {
        sum2 = pow((x[i] - x_mean), 2); 
        var += sum2;
    }
    return(var / x.size());
}

// Function to calculate covariance
float covariance(const vector<int>& x, const vector<int>& y, float x_mean, float y_mean)
{
    float mul = 0;

    // Calculating the covariance
    for (int i = 0; i <= x.size(); i++)
    {
        mul = mul + (x[i] - x_mean) * (y[i] - y_mean);

    }
    return (mul / x.size());
}

// Function implementing gradient descent optimization algorithm 
void gradientDescentAlgorithm(float &w_opt2, float &b_opt2, const vector<int>& x, const vector<int>& y, float learning_rate)
{
    float dw, db, num13 = (1 / 13.0);
    float sum_w = 0, sum_b = 0;
    float prediction;

    // Updating weights and bias with gradient descent
    for (int i = 0; i < x.size(); i++)
    {
        prediction = (w_opt2 * x[i]) + b_opt2;
        sum_w += x[i] * (prediction - y[i]);
        sum_b += prediction - y[i];
    }

    dw = num13 * sum_w;
    db = num13 * sum_b;
    w_opt2 -= learning_rate * dw;  // Updating weight
    b_opt2 -= learning_rate * db;  // Updating bias
}


// Function to calculate cost function
float cost_function(const vector<int>& x, const vector<int>& y, float w_opt, float b_opt)
{
    float sum = 0;
    float sum1;

    // Calculating cost function
    for (int i = 0; i <= x.size(); i++)
    {
        sum1 = ((w_opt * x[i] + b_opt) - y[i]) * ((w_opt * x[i] + b_opt) - y[i]);
        sum = sum + sum1;
    }

    return(sum / (2 * x.size()));
}

int main()
{
    vector<int> x, y;
   
    // Input data into vectors x and y
    inputData(x, y);

    // Initialize means of x and y
    float x_mean = 0;
    float y_mean = 0;
    
    int dataSize = x.size();

    // Calculate mean of x and y
    for (int i = 0; i < dataSize; i++)
    {
        x_mean = x_mean + x[i];
        y_mean = y_mean + y[i];
    }
    x_mean = x_mean / dataSize;
    y_mean = y_mean / dataSize;

    // Calculate covariance and variance
    float cov = covariance(x, y, x_mean, y_mean);
    float var_x = varianceX(x, x_mean);

    // Print the calculated variance and covariance
    cout << "x_mean is: " << x_mean << endl;
    cout << "y_mean is: " << y_mean << endl;
    cout << "Variance is: " << cov << endl;
    cout << "Covariance is: " << var_x << endl;

    // Calculate optimal weight and bias
    float w_opt = cov / var_x;
    float b_opt = y_mean - (w_opt * x_mean);

    cout << "\nW optimal is: " << w_opt << endl;
    cout << "B optimal is: " << b_opt << endl;

    // Calculate sum of predictions
    float pred_sum = 0;
    for (int i = 0; i <= dataSize; i++)
    {
        float pred = w_opt * x[i] + b_opt;
        pred_sum += (pred - y[i]) * (pred - y[i]);
    }

    // Output cost function and R2 value
    cout << "Cost function is: " << cost_function(x, y, b_opt, w_opt) << endl;
    cout << "Corresponding R2: " << R2(w_opt, b_opt, x, y, y_mean) << endl;

    // Input learning rate
    float learning_rate;
    cout << "Please enter the learning rate: ";
    cin >> learning_rate;

    // Gradient descent optimization loop
    float w_opt2, b_opt2;
    int maxItterations;
    char answer = 'y';
    while (answer == 'y')
    {
        cout << "\nenter w for gradient descent algorithm:";
        cin >> w_opt2;
        cout << "enter b for gradient descent algorithm:";
        cin >> b_opt2;

        cout << "How many iterations: ";
        cin >> maxItterations;
        
        for (int i = 0; i < maxItterations; i++)
        {
            cout << "this is the " << i+1 << "th iteration:"  << endl;
            gradientDescentAlgorithm(w_opt2, b_opt2, x, y, learning_rate);
            cout << "current w optimal is: " << w_opt2 << endl;
            cout << "current b optimal is: " << b_opt2 << endl;
            cout << "Cost function is: " << cost_function(x, y, b_opt, w_opt) << endl;
        }
        cout << "\nrepeat the gradient descent algorithm? (y/n):";
        cin >> answer;
    }

    system("pause");

    return 0;  // End of program
}
