#include "Dinic.hpp"


template<typename T>
T Dinic<T>::pushSinglePath(std::size_t start, T currentMin,
	std::vector<Iterator>& iterators)
{
	if (start == this->network_->Target()
		|| currentMin == 0)
		return currentMin;

	auto& it = iterators[start];

	while (it)
	{
		if (!this->inLayeredNetwork(it))
		{
			++it;
			continue;
		}

		T tryPush = it->Capacity() - it->Flow();
		if (currentMin != -1 && currentMin < tryPush)
			tryPush = currentMin;

		T flow = pushSinglePath(it->Target(), tryPush, iterators);

		if (flow > 0)
		{
			it->AddFlow(flow);
			return flow;
		}

		++it;
	}

	return 0;
}

template<typename T>
void Dinic<T>::pushBlockingFlow()
{
	auto& network = *this->network_;
	
	std::vector<Iterator> iterators;
	iterators.reserve(network.VerticeCount());

	for (std::size_t i = 0; i < network.VerticeCount(); ++i)
	{
		iterators.push_back(network.IterateOutgoingEdgesAt(i));
	}

	while (pushSinglePath(network.Source(), -1, iterators) > 0);
}
