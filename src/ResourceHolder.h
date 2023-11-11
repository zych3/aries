#pragma once
#include "ariespcf.h"
namespace aries
{
	enum class Texture
	{
		mob,
		hero,
		floor,
		weapon,
		background
	};
	enum class Font
	{
		dialog,
		title
	};

	enum class SoundBuffer
	{
		hero_attack,
		mob_attack,
		hero_death,
		mob_death
	};

	enum class Shader
	{
		test1,
		test2,
		test3
	};
	enum class Music {};
	enum class Image {};

	template<typename Resource, typename ID>
	class ResourceHolder
	{
	private:
		void load(ID id, const std::string& filename);
		

		template <typename Parameter>
		void load(ID id, const std::string& filename, const Parameter& secondParam); //for shaders, as they pass in 3 args
		
		Resource& get(ID id);
		
		const Resource& get(ID id) const;
		
		


	private:
		std::map <ID, std::unique_ptr<Resource>> mResourceMap;
	};

	
}