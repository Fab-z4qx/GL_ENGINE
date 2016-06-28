#include "Debug.h"
#include <iostream>

namespace e3d {
    
Debug::Debug(){}
    
void Debug::fpsInit(fpsCount* fps){
    fps->tc.start = std::chrono::system_clock::now();
    fps->frames = 0;
    fps->tc.diff = std::chrono::duration<double, std::milli>(0) ;
}
    
void Debug::fpsMesure(fpsCount* fps){
    fps->tc.diff = std::chrono::system_clock::now() - fps->tc.start;
    if(fps->tc.diff.count() > 1000){ // 1s
         std::cout << "Frame : " << fps->frames << std::endl;
         std::cout << fps->tc.diff.count() << std::endl;
         std::cout << "FPS : " << (1000.0*fps->frames) / fps->tc.diff.count() << std::endl;
         fps->tc.start = std::chrono::system_clock::now();
         fps->frames = 0;
     }
     fps->frames++;
}

double Debug::timeMesure(timeCounter* t){
    return std::chrono::duration<double, std::milli>(std::chrono::system_clock::now() - t->start).count();
}

};