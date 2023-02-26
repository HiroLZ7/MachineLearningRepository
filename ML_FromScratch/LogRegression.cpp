//
//  main.cpp
//  LogisticRegression
//
//  Created by Yazan Abughazaleh on 2/18/23.
//

#include <iostream>
#include <vector>
#include <valarray>
#include <fstream>
#include <chrono>

using namespace std;
//Matrix multiplication
vector<vector<double>> multiply(const vector<vector<double>> matA, const vector<vector<double>> matB){
    int matArow = matA.size();
    int matAcol = matA[0].size();
    
    int matBrow = matB.size();
    int matBcol = matB[0].size();
    vector<vector<double>> result(matArow, vector<double>(matBcol,0));
    
    if(matAcol != matBrow){
        cout<<"Matrix Multiplication Failed"<<endl;
        exit(1);
    }
    else{
        //Select Row
        for(int rowSel = 0; rowSel < matArow; rowSel++){
            //Select Column
            for(int colSel = 0; colSel < matBcol; colSel++){
                for(int opSel = 0; opSel < matBrow; opSel++){
                    result[rowSel][colSel] += matA[rowSel][opSel] * matB[opSel][colSel];
                }
            }
        }
    }
    return result;
}

//Matrix addition
vector<vector<double>> add(const vector<vector<double>> matA, const vector<vector<double>> matB){
    int matArow = matA.size();
    int matAcol = matA[0].size();
    
    int matBrow = matB.size();
    int matBcol = matB[0].size();
    vector<vector<double>> result(matArow, vector<double>(matAcol,0));
    if(matAcol != matBcol || matArow != matBrow){
        cout<<"Matrix Addition Failed"<<endl;
        exit(1);
    }
    else{
        //Select Row
        for(int rowSel = 0; rowSel < matArow; rowSel++){
            //Select Column
            for(int colSel = 0; colSel < matBcol; colSel++){
                
                result[rowSel][colSel] = matA[rowSel][colSel] + matB[rowSel][colSel];
                
            }
        }
    }
    return result;
}

//Matrix subtraction

vector<vector<double>> subtract(const vector<vector<double>> matA, const vector<vector<double>> matB){
    int matArow = matA.size();
    int matAcol = matA[0].size();
    
    int matBrow = matB.size();
    int matBcol = matB[0].size();
    vector<vector<double>> result(matArow, vector<double>(matAcol,0));
    if(matAcol != matBcol || matArow != matBrow){
        cout<<"Matrix Subtraction Failed"<<endl;
        exit(1);
    }
    else{
        //Select Row
        for(int rowSel = 0; rowSel < matArow; rowSel++){
            //Select Column
            for(int colSel = 0; colSel < matBcol; colSel++){
                
                result[rowSel][colSel] = matA[rowSel][colSel] - matB[rowSel][colSel];
                
            }
        }
    }
    return result;
}




//Matrix transpose

vector<vector<double>> transpose(const vector<vector<double>> mat){
    vector<vector<double>> result(mat[0].size(), vector<double>());
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {
            result[j].push_back(mat[i][j]);
            
        }
    }
    return result;
}

//Sigmoid
vector<vector<double>> sigmoid(const vector<vector<double>> mat){
    vector<vector<double>> result(mat.size(), vector<double>(mat[0].size()));
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {
            result[i][j]= 1.0/ (1+exp(-mat[i][j]));
        }
    }
    return result;
}



void printMatrix(const vector<vector<double>> MAT){
    for (int i = 0; i < MAT.size(); i++)
    {
        for (int j = 0; j < MAT[i].size(); j++)
        {
            cout << MAT[i][j]<< " ";
            
        }
        cout<<endl;
    }
}

vector<vector<double>> glm(vector<double> sex, vector<double> survived){
    vector<vector<double>> weights(2,vector<double>(1,1));
    
    vector<vector<double>> dataMatrix(sex.size(),vector<double>(2,0));
    for(int i = 0; i < sex.size(); i++){
        dataMatrix[i][0] = 1;
        dataMatrix[i][1] = sex[i];
    }
    
    vector<vector<double>> labels(survived.size(),vector<double>(1,0));
    for(int i = 0; i < survived.size(); i++){
        labels[i][0] = survived[i];
    }
    
    double learningRate = .001;
    for(int i = 0; i < 50000; i++){
        vector<vector<double>> dMatrixWeight = multiply(dataMatrix, weights);
        vector<vector<double>> probs = sigmoid(dMatrixWeight);
        
        vector<vector<double>> error = subtract(labels,probs);
        vector<vector<double>> dMatrixTranspose = transpose(dataMatrix);
        vector<vector<double>> edmatrix = multiply(dMatrixTranspose, error);
        weights[0][0] += (learningRate * edmatrix[0][0]);
        weights[1][0] += (learningRate * edmatrix[1][0]);
        
    }
    return weights;
}

vector<double> predict(vector<double> sex, vector<vector<double>> weights){
    vector<vector<double>> testMatrix(sex.size(),vector<double>(2,0));
    for(int i = 0; i < sex.size(); i++){
        testMatrix[i][0] = 1;
        testMatrix[i][1] = sex[i];
    }
    vector<vector<double>> predicted = multiply(testMatrix, weights);
    vector<double> probabilities(predicted.size(),0);
    vector<double> predictions(predicted.size(),0);
    for(int i = 0; i < predicted.size();i++){
        probabilities[i] = exp(predicted[i][0]) / (1 + exp(predicted[i][0]));
        if(probabilities[i] > .5){
            predictions[i] = 1;
        }else{
            predictions[i] = 0;
        }
    }
    
    return predictions;
}


void calculateStats(vector<double> predictions, vector<double> survived){
    double TP = 0; // true positive
    double FP = 0; // false positive
    double TN = 0; // true negative
    double FN = 0; // false negative
    
    for (int i = 0; i < predictions.size(); i++) {
        
        if (predictions[i] == 1 and survived[i] == 1) {
            TP++;
        }
        
        else if (predictions[i] == 1 and survived[i] == 0) {
            FP++;
        }
       
        else if (predictions[i] == 0 and survived[i] == 1) {
            FN++;
        }
        
        
        else {
            TN++;
        }
    }
    double accuracy = (TP + TN) / (TP + TN + FP + FN);
    double sensitivity = TP / (TP + FN);
    double specificity = TN / (TN + FP);
    
    cout << endl;
    cout << "Metrics: " << endl;
    cout << "Accuracy: " << accuracy << endl;
    cout << "Sensitivity: " << sensitivity << endl;
    cout << "Specificity: " << specificity << endl;
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream inputFile;
    string line;
    string pno, pclass_in, surv_in, sex_in, age_in;
    vector<double> pclass;
    vector<double> survive;
    vector<double> sex;
    vector<double> age;
    cout<<"Opening titanic.csv File"<<endl;
    inputFile.open("titanic_project.csv");
    if(!inputFile.is_open()){
        cout<<"Could not open titanic_project.csv"<<endl;
        return 1;
    }
    getline(inputFile,line);
    cout<<"Header: "<<line<<std::endl;
    int observationNumber = 0;
    while(inputFile.good()){
        getline(inputFile,pno,',');
        getline(inputFile,pclass_in,',');
        getline(inputFile,surv_in,',');
        getline(inputFile,sex_in,',');
        getline(inputFile,age_in,'\n');
        pclass.push_back(stof(pclass_in));
        survive.push_back(stof(surv_in));
        sex.push_back(stof(sex_in));
        age.push_back(stof(age_in));
        observationNumber++;
    }
    
    inputFile.close();
    
    vector<double> train_sex(800);
    vector<double> test_sex(observationNumber - 800);
    
    vector<double> train_survive(800);
    vector<double> test_survive(observationNumber - 800);
    
    for(int i = 0; i < observationNumber; i++){
        if (i < 800) {
            train_sex.at(i) = sex.at(i);
            train_survive.at(i) = survive.at(i);
        }
        else {
            test_sex.at(i - 800) = sex.at(i);
            test_survive.at( i - 800) = survive.at(i);
        }
    }
    
    cout<<"Training Model!"<<endl;
    auto start = chrono::steady_clock::now();
    vector<vector<double>> weights = glm(train_sex, train_survive);
    auto stop = chrono::steady_clock::now();
    cout << "The model took " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << " milliseconds to train." << endl;
    cout<<"Coefficients for Logistic Regression: "<<endl;
    double w0 = weights[0][0];
    double w1 = weights[1][0];
    cout<<"w0 (Intercept): "<<w0<<" , w1 (Slope): "<<w1<<endl;
    vector<double> predictions = predict(test_sex, weights);
    calculateStats(predictions, test_survive);
    return 0;
}


