//
//  main.cpp
//  MLMetrics
//
//  Created by Yazan Abughazaleh on 1/26/23.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

double sumVector(std::vector<double> vec);
double mean(std::vector<double> vec);
double median(std::vector<double> vec);
double range(std::vector<double> vec);
double covariance(std::vector<double> vecX, std::vector<double> vecY);
double correlation(std::vector<double> vecX, std::vector<double> vecY);

int main(int argc, const char * argv[]) {
    std::ifstream inputFile;
    std::string line;
    std::string rm_in, medv_in;
    std::vector<double> rm;
    std::vector<double> medv;
    std::cout<<"Opening Boston.csv File"<<std::endl;
    inputFile.open("Boston.csv");
    if(!inputFile.is_open()){
        std::cout<<"Could not open Bostn.csv"<<std::endl;
        return 1;
    }
    std::getline(inputFile,line);
    std::cout<<"Header: "<<line<<std::endl;
    int observationNumber = 0;
    while(inputFile.good()){
        std::getline(inputFile,rm_in,',');
        std::getline(inputFile,medv_in,'\n');
        rm.push_back(std::stof(rm_in));
        medv.push_back(std::stof(medv_in));
        observationNumber++;
    }
    
    std::cout<<"vector size: "<<rm.size()<<std::endl;
    std::cout<<"Closing Boston.csv"<<std::endl;
    inputFile.close();
    std::cout<<"Number of observations: "<<observationNumber<<std::endl;
    std::cout<<"\nrmSum: "<<sumVector(rm)<<std::endl;
    std::cout<<"\nmedvSum: "<<sumVector(medv)<<std::endl;
    std::cout<<"\nrmMean: "<<mean(rm)<<std::endl;
    std::cout<<"\nmedvMean: "<<mean(medv)<<std::endl;
    std::cout<<"\nrmMedian: "<<median(rm)<<std::endl;
    std::cout<<"\nmedvMedian: "<<median(medv)<<std::endl;
    std::cout<<"\nrmRange: "<<range(rm)<<std::endl;
    std::cout<<"\nmedvRange: "<<range(medv)<<std::endl;
    std::cout<<"\nCovariance "<<covariance(rm, medv)<<std::endl;
    std::cout<<"\nCorrelation "<<correlation(rm, medv)<<std::endl;
    return 0;
}

double sumVector(std::vector<double> vec){
    double sum = 0;
    for(double d : vec){
        sum += d;
    }
    return sum;
}

double mean(std::vector<double> vec){
    double mean = sumVector(vec) / vec.size();
    return mean;
}

double median(std::vector<double> vec){
    double median;
    std::sort(vec.begin(),vec.end());
    if(vec.size() % 2 == 0){
        median = (vec.at((vec.size()/2)) + vec.at((vec.size()/2)-1))/2;
    }
    else{
        median = (vec.at(vec.size()/2));
    }
    return median;
}

double range(std::vector<double> vec){
    double range = 0;
    
    range = (*std::max_element(vec.begin(), vec.end())) - (*std::min_element(vec.begin(), vec.end()));
    return range;
}

double covariance(std::vector<double> vecX, std::vector<double> vecY){
    double covariance = 0;
    double vecXmean = mean(vecX);
    double vecYmean = mean(vecY);
    if(vecX.size() == vecY.size()){
        double covSum = 0;
        for(int i = 0; i < vecY.size();i++){
            covSum += ((vecX.at(i) - vecXmean) * (vecY.at(i) - vecYmean));
        }
        covariance = covSum/(vecX.size()-1);
    }
    return covariance;
}

double correlation(std::vector<double> vecX, std::vector<double> vecY){
    double correlation = 0;
    double covar = covariance(vecX, vecY);
    double sigmaX = sqrt( covariance(vecX, vecX));
    double sigmaY = sqrt( covariance(vecY, vecY));
    correlation = (covar/(sigmaX*sigmaY));
    return correlation;
}
