#pragma once

#include <chrono>

using namespace std;
namespace e3d {
    
typedef struct{
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    std::chrono::duration<double, std::milli> diff;
}timeCounter;

typedef struct{
    int frames;
    timeCounter tc;
}fpsCount;
 
//General struct used for error
enum Error {
    kSucces,
    kAssetNotFound,
    kIndexUnknow,
    kError
};
    
//TO DO
//Catch error and display
class Debug
{
private:
   
    
public:
    Debug();
    void fpsInit(fpsCount* fps);
    void fpsMesure(fpsCount* fps);
    double timeMesure(timeCounter* t);
    
};

}