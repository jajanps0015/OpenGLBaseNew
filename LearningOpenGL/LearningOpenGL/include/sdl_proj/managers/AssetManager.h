#pragma once

#include <Graphics.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map> 
#include <SDL_mixer.h>
#include <ShaderUtil.h>

using namespace FOGrP;

namespace sdlFr
{
	class AssetManager
	{
	private:
		static AssetManager* sInstance;

		std::map<std::string, SDL_Texture*> mTextures;
		std::map<SDL_Texture*, unsigned> mTextureRefCount;

		std::map<std::string, TTF_Font*> mFonts;
		std::map<std::string, SDL_Texture*> mText;

		std::map<std::string, Mix_Music*> mMusic;
		std::map<std::string, Mix_Chunk*> mSFX;
		std::map<Mix_Music*, unsigned> mMusicRefCount;
		std::map<Mix_Chunk*, unsigned*> mSFXRefCount;

		std::map<std::string, SDL_Surface*> mSurfaceTextures;
		std::map<std::string, SDL_Surface*> mSurfaceText;
		std::map<SDL_Surface*, unsigned> mSurfaceaceRefCount;

		static std::map<std::string, ShaderUtil> shaders;

		static ShaderUtil loadShaderFromFile(const GLchar* vShaderFile,
			const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);

		AssetManager();
		~AssetManager();

	public:
		static AssetManager* Instance();
		static void Release();

		SDL_Texture* GetTexture(std::string filename, bool managed = false);
		void DestroyTexture(SDL_Texture* texture);

		TTF_Font* GetFont(std::string filename, int size);
		SDL_Texture* GetText(std::string text,
			std::string filename,
			int size, SDL_Color color,
			bool managed = false);

		Mix_Music* GetMusic(std::string filename, bool managed = false);
		Mix_Chunk* GetSFX(std::string filename, bool managed = false);
		void DestroyMusic(Mix_Music* music);
		void DestroySFX(Mix_Chunk* sfx);

		SDL_Surface* GetSurfaceTexture(std::string filename, bool managed = false);
		SDL_Surface* GetSurfaceText(std::string text, std::string filename, int size,
			SDL_Color color, bool managed = false);
		void DestroySurface(SDL_Surface* surface);

		static ShaderUtil GetShader(std::string name);
		static ShaderUtil LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile,
			const GLchar* gShaderFile, std::string name);
	};
}
