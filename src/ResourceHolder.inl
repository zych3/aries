template <typename Resource, typename ID>
void aries::ResourceHolder<Resource, ID>::load(ID id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());

	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - failed to load file " + filename);

	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);

}

template <typename Resource, typename ID>
template <typename Parameter>
void aries::ResourceHolder<Resource, ID>::load(ID id, const std::string& filename, const Parameter& secondParam)
{
	std::unique_ptr<Resource> resource(new Resource());

	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - failed to load file " + filename);
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename ID>
Resource& aries::ResourceHolder<Resource, ID>::get(ID id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource, typename ID>
const Resource& aries::ResourceHolder<Resource, ID>::get(ID id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}