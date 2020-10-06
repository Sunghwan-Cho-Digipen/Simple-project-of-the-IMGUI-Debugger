#pragma once

#include <vector>
#include "Layer.h"

namespace ggm
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return mLayers.begin(); }
		std::vector<Layer*>::iterator end() { return mLayers.end(); }
		auto rbegin() { return mLayers.rbegin(); }
		auto rend() { return mLayers.rend(); }
		
	private:
		std::vector<Layer*> mLayers;
		std::vector<Layer*>::iterator mLayerInsert;
		
	};
}
