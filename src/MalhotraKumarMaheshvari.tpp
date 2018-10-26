#include "MalhotraKumarMaheshvari.hpp"
#include <queue>


template<typename T>
bool MalhotraKumarMaheshvari<T>::inLayeredNetwork(Iterator it)
{
	return !deleted_[it->Source()] && !deleted_[it->Target()]
		&& BlockingFlowAlgorithm<T>::inLayeredNetwork(it);
}

template<typename T>
void MalhotraKumarMaheshvari<T>::deleteVertice(std::size_t vertice)
{
	for (auto it = this->network_->IterateOutgoingEdgesAt(vertice); it; ++it)
	{
		if (inLayeredNetwork(it))
			potentialIn_[it->Target()] -= (it->Capacity() - it->Flow());
	}

	for (auto it = this->network_->IterateIncomingEdgesAt(vertice); it; ++it)
	{
		if (inLayeredNetwork(it))
			potentialOut_[it->Source()] -= (it->Capacity() - it->Flow());
	}

	deleted_[vertice] = true;
}

template<typename T>
T MalhotraKumarMaheshvari<T>::potential(std::size_t vertice)
{
	if (vertice == this->network_->Source())
		return potentialOut_[vertice];
	if (vertice == this->network_->Target())
		return potentialIn_[vertice];
	return std::min(potentialIn_[vertice], potentialOut_[vertice]);
}

template<typename T>
void MalhotraKumarMaheshvari<T>::recalcPotential(std::size_t vertice)
{
	potentialIn_[vertice] = 0;
	potentialOut_[vertice] = 0;

	for (auto it = this->network_->IterateOutgoingEdgesAt(vertice); it; ++it)
	{
		if (inLayeredNetwork(it))
			potentialOut_[vertice] += it->Capacity() - it->Flow();
	}

	for (auto it = this->network_->IterateIncomingEdgesAt(vertice); it; ++it)
	{
		if (inLayeredNetwork(it))
			potentialIn_[vertice] += it->Capacity() - it->Flow();
	}
}

template<typename T>
void MalhotraKumarMaheshvari<T>::pushFlowThroughVerticeSingleDirection(
	std::size_t vertice, T initialPush, std::vector<Iterator>& iterators, bool reversed)
{
	std::queue<std::pair<std::size_t, T>> verticeQueue;
	verticeQueue.push(std::make_pair(vertice, initialPush));

	while (!verticeQueue.empty())
	{
		auto current = verticeQueue.front().first;
		auto pushing = verticeQueue.front().second;
		verticeQueue.pop();

		auto& it = iterators[current];
		while (pushing > 0 && it)
		{
			if (!inLayeredNetwork(it))
			{
				++it;
				continue;
			}

			auto next = reversed ? it->Source() : it->Target();

			auto actualPush =
				std::min(it->Capacity() - it->Flow(), pushing);

			it->AddFlow(actualPush);

			this->potentialOut_[it->Source()] -= actualPush;
			this->potentialIn_[it->Target()] -= actualPush;
			
			pushing -= actualPush;

			if (next != this->network_->Source()
				&& next != this->network_->Target())
			{
				verticeQueue.push(std::make_pair(next, actualPush));
			}

			if (it->Capacity() == it->Flow())
				++it;
		}
	}
}

template<typename T>
void MalhotraKumarMaheshvari<T>::Initialize(std::shared_ptr<Network<T>> network)
{
	potentialIn_.resize(network->VerticeCount());
	potentialOut_.resize(network->VerticeCount());

	deleted_.resize(network->VerticeCount());
	
	BlockingFlowAlgorithm<T>::Initialize(network);
}

template<typename T>
void MalhotraKumarMaheshvari<T>::pushBlockingFlow()
{
	auto& network = *this->network_;

	deleted_.assign(network.VerticeCount(), false);

	for (std::size_t i = 0; i < network.VerticeCount(); ++i)
	{
		recalcPotential(i);
	}

	std::vector<Iterator> forwards;
	forwards.reserve(network.VerticeCount());
	std::vector<Iterator> backwards;
	backwards.reserve(network.VerticeCount());

	for (std::size_t i = 0; i < network.VerticeCount(); ++i)
	{
		forwards.push_back(network.IterateOutgoingEdgesAt(i));
		backwards.push_back(network.IterateIncomingEdgesAt(i));
	}

	T blockingFlow = 0;
	while (!deleted_[network.Source()] && !deleted_[network.Target()])
	{
		std::size_t keyVertice = InfiniteSize;
		for (std::size_t j = 0; j < network.VerticeCount(); ++j)
		{
			if (!deleted_[j] &&
				(keyVertice == InfiniteSize || potential(keyVertice) > potential(j)))
			{
				keyVertice = j;
			}
		}

		if (potential(keyVertice) != 0)
		{
			blockingFlow += potential(keyVertice);
			T initialPush = potential(keyVertice);
			pushFlowThroughVerticeSingleDirection(keyVertice, initialPush, forwards, false);
			pushFlowThroughVerticeSingleDirection(keyVertice, initialPush, backwards, true);
		}

		deleteVertice(keyVertice);
	}
}
