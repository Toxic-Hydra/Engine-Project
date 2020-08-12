//
// Created by ivanl on 6/20/2020.
//

#ifndef ENGINE_ASSETMANAGER_H
#define ENGINE_ASSETMANAGER_H
#include <SDL.h>
#include <string>
#include <map>

class AssetManager {
private:
    std::map<std::string, SDL_Texture*> textures; //i'd like to set this to shared_ptr, but need to wrap.
    std::map<std::string, std::tuple<SDL_Rect,int>> sheetMap; //returns a tuple with rect pointer and numFrames
    //will also have maps for sounds and fonts
public:
    AssetManager();
    void AddTexture(std::string assetId, std::string filePath);
    void SplitTexture(std::string assetId, std::string directions);
    std::tuple<SDL_Rect, int> GetSheetRect(std::string assetId); //Honestly I just want to play with tuples
    SDL_Texture* GetTexture(std::string assetId);
    void Clear();
};


#endif //ENGINE_ASSETMANAGER_H
