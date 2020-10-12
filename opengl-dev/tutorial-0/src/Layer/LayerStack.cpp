
#include "LayerStack.h"

namespace ggm
{

	LayerStack::~LayerStack()
	{
		for(Layer* layer : mLayers)
		{
			layer->Detach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		mLayers.emplace(mLayers.begin() + mLayerInsertIndex, layer);
		++mLayerInsertIndex;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		mLayers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto iter = std::find(mLayers.begin(), mLayers.begin() + mLayerInsertIndex, layer);
		if(iter != mLayers.begin() + mLayerInsertIndex)
		{
			layer->Detach();
			mLayers.erase(iter);
			--mLayerInsertIndex;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto iter = std::find(mLayers.begin() + mLayerInsertIndex, mLayers.end(), overlay);
		if(iter != mLayers.end())
		{
			overlay->Detach();
			mLayers.erase(iter);
		}
	}

}
