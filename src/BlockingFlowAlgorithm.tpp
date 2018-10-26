#include "BlockingFlowAlgorithm.hpp"


template<typename T>
bool BlockingFlowAlgorithm<T>::inLayeredNetwork(Iterator it)
{
	return it->Flow() < it->Capacity()
		&& this->layer_[it->Target()] == this->layer_[it->Source()] + 1;
}

template<typename T>
bool BlockingFlowAlgorithm<T>::calculateLayeredNetwork()
{
	layer_.assign(this->network_->VerticeCount(), InfiniteSize);
	std::queue<std::size_t> verticeQueue;

	verticeQueue.push(this->network_->Source());
	this->layer_[this->network_->Source()] = 0;

	while (!verticeQueue.empty())
	{
		auto current = verticeQueue.front();
		verticeQueue.pop();
		auto it = this->network_->IterateOutgoingEdgesAt(current);
		while (it)
		{
			if (this->layer_[it->Target()] == InfiniteSize && 
				it->Flow() < it->Capacity())
			{
				this->layer_[it->Target()] = layer_[it->Source()] + 1;
				verticeQueue.push(it->Target());
			}
			++it;
		}
	}

	return layer_[this->network_->Target()] != InfiniteSize;
}

template<typename T>
void BlockingFlowAlgorithm<T>::Initialize(std::shared_ptr<Network<T>> network)
{
	layer_.resize(network->VerticeCount());

	MaxFlowAlgorithm<T>::Initialize(network);
}

template<typename T>
void BlockingFlowAlgorithm<T>::Calculate()
{
	while (calculateLayeredNetwork())
	{
		pushBlockingFlow();
	}
}
