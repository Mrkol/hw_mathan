#include "MaxFlowAlgorithm.hpp"

template<typename T>
void MaxFlowAlgorithm<T>::Initialize(std::shared_ptr<Network<T>> network)
{
	network_ = network;
}

template<typename T>
std::shared_ptr<Network<T>> MaxFlowAlgorithm<T>::GetNetwork()
{
	return network_;
}

template<typename T>
T MaxFlowAlgorithm<T>::GetFlow()
{
	T flow = 0;

	for (auto it = network_->IterateOutgoingEdgesAt(network_->Source()); it; ++it)
	{
		flow += it->Flow();
	}

	return flow;
}
