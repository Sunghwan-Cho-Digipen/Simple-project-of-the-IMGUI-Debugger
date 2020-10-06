#include "LayerStack.h"

namespace ggm
{
	LayerStack::LayerStack()
	{
		mLayerInsert = mLayers.begin();
	}

	LayerStack::~LayerStack()
	{
		for(Layer* layer : mLayers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		mLayerInsert = mLayers.emplace(mLayerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		mLayers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto iter = std::find(mLayers.begin(), mLayers.end(), layer);
		if(iter != mLayers.end())
		{
			mLayers.erase(iter);
			--mLayerInsert;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto iter = std::find(mLayers.begin(), mLayers.end(), overlay);
		if(iter != mLayers.end())
		{
			mLayers.erase(iter);
		}
	}

	

}
