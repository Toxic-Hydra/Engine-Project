//
// Created by ivanl on 6/20/2020.
//

#include "AssetManager.h"
#include "TextureManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

void AssetManager::AddTexture(std::string assetId, std::string filePath)
{
    std::cout << "Loading: " << filePath << std::endl;
    textures.emplace(assetId, TextureManager::LoadTexture(filePath.c_str()));
}

void AssetManager::SplitTexture(std::string assetId, std::string directions)
{
    
    //AssetId is the pre loaded texture we want to split.
    std::ifstream input(directions);
    if (input.fail())
    {
        
        std::cerr << "Failed to SplitTexture: " << directions << std::endl;
        return;
    }

    /*
    *   Format:
    *   rectSource Name, x, y, w, h, numFrames;
    */
    
    std::string spriteName;
    int x, y, w, h, numFrames{0};
    std::string line;
    std::vector<std::string> lineV;
    
    while (std::getline(input, line))
    {
        
        if (line.size() == 0) //doing "" instead of \n cause issues for about 7 hours. fuck.
            continue;
        
        //split line, check length, convert to variables, create rect, setRect
        //String Splitter
        std::istringstream split(line);
        
        std::string token;
        while (std::getline(split, token, ' '))
        {
            
            lineV.push_back(token);
        }
        
        

        //Read string to values
        spriteName = lineV[0];
        
        x = std::stoi(lineV[1]);
        y = std::stoi(lineV[2]);
        w = std::stoi(lineV[3]);
        h = std::stoi(lineV[4]);
        //check for numFrames, if not we ignore.
        //This may be useless for now, we may still ignore it for now.
        if (lineV.size() == 6)
        {
            numFrames = std::stoi(lineV[5]);
        }
        //Create new rectangle for map
        SDL_Rect newRect;
        newRect.x = x;
        newRect.y = y;
        newRect.w = w;
        newRect.h = h;
        
        
        //std::cout << spriteName << " " << newRect.x << " " <<  newRect.y << " " << newRect.w << " " << newRect.h << std::endl;
        sheetMap.emplace(spriteName, std::tuple<SDL_Rect, int>(newRect, numFrames));

        lineV.clear();
    }



    input.close();


}

std::tuple<SDL_Rect, int> AssetManager::GetSheetRect(std::string assetId)
{
    return sheetMap[assetId];
}

SDL_Texture *AssetManager::GetTexture(std::string assetId)
{
    return textures[assetId];
}

void AssetManager::Clear()
{
    //DestroyTexture for every texture in textures, then clear.
    //cpp reference claims all cleared elements are destroyed.
    textures.clear();
    sheetMap.clear();
}

AssetManager::AssetManager() {

}
