//
//  main.cpp
//  NaiveBayes
//
//  Created by Yazan Abughazaleh on 2/23/23.
//

#include <iostream>
#include <vector>
#include <valarray>
#include <fstream>
#include <chrono>
#include <math.h>
#include <cmath>
#include <iomanip>
#define _USE_MATH_DEFINES


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

vector<double> apriori(vector<double> survive){
    vector<double> apriori(2,0);
    int nrow = survive.size();
    double probNo=0;
    double probYes=0;
    for(int i = 0; i < nrow; i++){
        if(survive[i] == 1){
            probYes++;
        }else{
            probNo++;
        }
    }
    probNo /= (double) nrow;
    probYes /= (double) nrow;
    apriori[0] = probNo;
    apriori[1] = probYes;
    return apriori;
}

vector<double> counts(vector<double> survive){
    vector<double> counts(2,0);
    double countYes = 0;
    double countNo = 0;
    for(int i = 0; i < survive.size(); i++){
        if(survive[i] == 1){
            countYes++;
        }else{
            countNo++;
        }
    }
    counts[0] = countNo;
    counts[1] = countYes;
    return counts;
}

vector<vector<double>> pclassLikely(vector<double> survive,vector<double> pclass){
    vector<double> count = counts(survive);
    vector<vector<double>> pcl_Likely(2,vector<double>(3,0));
    for(int i = 0; i < survive.size();i++){
        if(survive[i] == 0 && pclass[i] == 1){
            pcl_Likely[0][0]++;
        }
        else if(survive[i] == 0 && pclass[i] == 2){
            pcl_Likely[0][1]++;
        }
        else if(survive[i] == 0 && pclass[i] == 3){
            pcl_Likely[0][2]++;
        }
        else if(survive[i] == 1 && pclass[i] == 1){
            pcl_Likely[1][0]++;
        }
        else if(survive[i] == 1 && pclass[i] == 2){
            pcl_Likely[1][1]++;
        }
        else{
            pcl_Likely[1][2]++;
        }
    }
    for(int i = 0; i < pcl_Likely.size();i++){
        for(int j = 0; j < pcl_Likely[0].size();j++){
            if(i == 0){
                pcl_Likely[i][j] /= count[0];
            }
            else{
                pcl_Likely[i][j] /= count[1];
            }
        }
    }
    return pcl_Likely;
}

vector<vector<double>> sexLikely(vector<double> survive,vector<double> sex){
    vector<double> count = counts(survive);
    vector<vector<double>> sexLikely(2,vector<double>(2,0));
    for(int i = 0; i < survive.size();i++){
        if(survive[i] == 0 && sex[i] == 0){
            sexLikely[0][0]++;
        }
        else if(survive[i] == 0 && sex[i] == 1){
            sexLikely[0][1]++;
        }
        
        else if(survive[i] == 1 && sex[i] == 0){
            sexLikely[1][0]++;
        }
        else if(survive[i] == 1 && sex[i] == 1){
            sexLikely[1][1]++;
        }
        
    }
    for(int i = 0; i < sexLikely.size();i++){
        for(int j = 0; j < sexLikely[0].size();j++){
            if(i == 0){
                sexLikely[i][j] /= count[0];
            }
            else{
                sexLikely[i][j] /= count[1];
            }
        }
    }
    return sexLikely;
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
    

vector<double> ageMean(vector<double> survive,vector<double> age){
    vector<double> mean(2,0);
    vector<double> count = counts(survive);
    for(int i = 0; i < age.size(); i++){
        if(survive[i] == 0){
            mean[0] += age[i];
        }else{
            mean[1] += age[i];
        }
        
    }
    mean[0]/=count[0];
    mean[1]/=count[1];
    
    return mean;
}

    
vector<double> ageVar(vector<double> survive,vector<double> age, vector<double> ageM){
    vector<double> var(2,0);
    vector<double> count = counts(survive);
    for(int i = 0; i < age.size(); i++){
        if(survive[i] == 0){
            var[0] += pow((age[i] - ageM[0]), 2);
        }else{
            var[1] += pow((age[i] - ageM[1]), 2);
        }
        
    }
    var[0]/=count[0]+1;
    var[1]/=count[1]+1;
    
    return var;
}

double calc_age_lh(double v, double mean_v, double var_v){
    return 1.0/ sqrt(2 * M_PI * var_v) * exp(-(pow(v-mean_v,2))/(2 * var_v));
}




int main(int argc, const char * argv[]) {
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
    
    vector<double> train_pclass(800);
    vector<double> test_pclass(observationNumber - 800);
    
    vector<double> train_age(800);
    vector<double> test_age(observationNumber - 800);
    
    for(int i = 0; i < observationNumber; i++){
        if (i < 800) {
            train_sex.at(i) = sex.at(i);
            train_survive.at(i) = survive.at(i);
            train_pclass.at(i) = pclass.at(i);
            train_age.at(i) = age.at(i);
        }
        else {
            test_sex.at(i - 800) = sex.at(i);
            test_survive.at( i - 800) = survive.at(i);
            test_pclass.at(i - 800) = pclass.at(i);
            test_age.at(i - 800) = age.at(i);
        }
    }
    
    auto start = chrono::steady_clock::now();
    vector<double> apri = apriori(train_survive);
    cout <<"Prob No: "<<apri[0]<<endl;
    cout <<"Prob Yes: "<<apri[1]<<endl;
    
    vector<vector<double>> priorPclass = pclassLikely(train_survive,train_pclass);
    cout<<"Likelyhood for p(pclass|survived)"<<endl;
    cout<<"Pclass     1  2  3"<<endl;
    cout<<"survived\n   no\n   yes"<<endl;
    printMatrix(priorPclass);
    
    vector<vector<double>> priorSex = sexLikely(train_survive, train_sex);
    cout<<"Likelyhood for p(sex|survived)"<<endl;
    cout<<"Sex       0  1"<<endl;
    cout<<"survived\n   no\n   yes"<<endl;
    printMatrix(priorSex);
    
    vector<double> ageM = ageMean(train_survive, train_age);
    cout<<"Age mean:"<<endl;
    cout<<"Not survived: "<<ageM[0]<<endl;
    cout<<"Survived: "<<ageM[1]<<endl;
    
    vector<double> ageV = ageVar(train_survive, train_age, ageM);
    cout<<"Age variance:"<<endl;
    cout<<"Not survived: "<<sqrt(ageV[0])<<endl;
    cout<<"Survived: "<<sqrt(ageV[1])<<endl;
    auto end = chrono::steady_clock::now();
    cout << "Time taken to train the model with the training data: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds." << endl;
    
    
    
    double numS = 0;
    double numP = 0;
    double denom = 0;
    cout<<"Evaluating Model"<<endl;
    cout << setw(15) << "[0]" << "\t\t" << setw(15) << "[1]" << endl;
    for(int i = 0; i < test_survive.size() -1; i++){
        if(test_pclass[i] == 1 && test_sex[i] == 0){
            numS = priorPclass[1][0] * priorSex[1][0] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]);
            numP = priorPclass[0][0] * priorSex[0][0] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
            denom = priorPclass[1][0] * priorSex[1][0] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]) + priorPclass[0][0] * priorSex[0][0] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
        }else if(test_pclass[i] == 1 && test_sex[i] == 1){
            numS = priorPclass[1][0] * priorSex[1][1] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]);
            numP = priorPclass[0][0] * priorSex[0][1] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
            denom = priorPclass[1][0] * priorSex[1][1] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]) + priorPclass[0][0] * priorSex[0][1] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
        }else if(test_pclass[i] == 2 && test_sex[i] == 0){
            numS = priorPclass[1][1] * priorSex[1][0] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]);
            numP = priorPclass[0][1] * priorSex[0][0] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
            denom = priorPclass[1][1] * priorSex[1][0] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]) + priorPclass[0][1] * priorSex[0][0] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
        }else if(test_pclass[i] == 2 && test_sex[i] == 1){
            numS = priorPclass[1][1] * priorSex[1][1] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]);
            numP = priorPclass[0][1] * priorSex[0][1] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
            denom = priorPclass[1][1] * priorSex[1][1] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]) + priorPclass[0][1] * priorSex[0][1] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
        }else if(test_pclass[i] == 3 && test_sex[i] == 0){
            numS = priorPclass[1][2] * priorSex[1][0] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]);
            numP = priorPclass[0][2] * priorSex[0][0] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
            denom = priorPclass[1][2] * priorSex[1][0] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]) + priorPclass[0][2] * priorSex[0][0] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
        }else if(test_pclass[i] == 3 && test_sex[i] == 1){
            numS = priorPclass[1][2] * priorSex[1][1] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]);
            numP = priorPclass[0][2] * priorSex[0][1] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
            denom = priorPclass[1][2] * priorSex[1][1] * apri[1] * calc_age_lh(test_age[i], ageM[1], ageV[1]) + priorPclass[0][2] * priorSex[0][1] * apri[0] * calc_age_lh(test_age[i], ageM[0], ageV[0]);
        }
        double probability_survived = numS / denom;
        double probability_perished = numP / denom;
        cout << "[" << right << setw(5) << i << "]" << right << setw(10) << probability_perished << "\t\t" << right << setw(10) <<  probability_survived << endl;
    }
    
    return 0;
}
