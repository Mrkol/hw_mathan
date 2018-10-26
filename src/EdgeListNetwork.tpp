#include "EdgeListNetwork.hpp"




template<typename T>
EdgeListNetwork<T>::EdgeListNetwork(std::size_t vertices)
	: verticeCount_(vertices), edgeCount_(0),
		firstEdgeFrom_(vertices, InfiniteSize),
		firstEdgeTo_(vertices, InfiniteSize)
{

}

template<typename T>
void EdgeListNetwork<T>::setSource(std::size_t source)
{
	source_ = source;
}

template<typename T>
void EdgeListNetwork<T>::setTarget(std::size_t target)
{
	target_ = target;
}

template<typename T>
void EdgeListNetwork<T>::addBareEdge(
	std::size_t from, std::size_t to, T capacity)
{
	if (firstEdgeFrom_[from] != InfiniteSize)
		nextEdgeFrom_.push_back(firstEdgeFrom_[from]);
	else
		nextEdgeFrom_.push_back(edgeCount_);

	if (firstEdgeTo_[to] != InfiniteSize)
		nextEdgeTo_.push_back(firstEdgeTo_[to]);
	else
		nextEdgeTo_.push_back(edgeCount_);

	firstEdgeFrom_[from] = edgeCount_;
	firstEdgeTo_[to] = edgeCount_;
	from_.push_back(from);
	to_.push_back(to);
	capacity_.push_back(capacity);
	flow_.push_back(T(0));
	++edgeCount_;
}

template<typename T>
std::size_t EdgeListNetwork<T>::VerticeCount()
{
	return verticeCount_;
}

template<typename T>
std::size_t EdgeListNetwork<T>::EdgeCount()
{
	return edgeCount_;
}

template<typename T>
std::size_t EdgeListNetwork<T>::Source()
{
	return source_;
}

template<typename T>
std::size_t EdgeListNetwork<T>::Target()
{
	return target_;
}

template<typename T>
void EdgeListNetwork<T>::ClearFlow()
{
	flow_.assign(flow_.size(), 0);
}

template<typename T>
auto EdgeListNetwork<T>::IterateOutgoingEdgesAt(std::size_t from)
	-> typename Network<T>::Iterator
{
	return typename Network<T>::Iterator(
		std::unique_ptr<InternalIterator>(
			new InternalIterator(firstEdgeFrom_[from], this, true)));
}

template<typename T>
auto EdgeListNetwork<T>::IterateIncomingEdgesAt(std::size_t to)
	-> typename Network<T>::Iterator
{
	return typename Network<T>::Iterator(
		std::unique_ptr<InternalIterator>(
			new InternalIterator(firstEdgeTo_[to], this, false)));
}

template<typename T>
EdgeListNetwork<T>::InternalIterator::InternalIterator(std::size_t index,
	EdgeListNetwork<T>* network, bool outgoing)
		: edgeIndex_(index), network_(network),
			outgoing_(outgoing),
			ended_(index == InfiniteSize)
{

}

template<typename T>
T EdgeListNetwork<T>::InternalIterator::Capacity()
{
	return network_->capacity_[edgeIndex_];
}

template<typename T>
T EdgeListNetwork<T>::InternalIterator::Flow()
{
	return network_->flow_[edgeIndex_];
}

template<typename T>
std::size_t EdgeListNetwork<T>::InternalIterator::Source()
{
	return network_->from_[edgeIndex_];
}

template<typename T>
std::size_t EdgeListNetwork<T>::InternalIterator::Target()
{
	return network_->to_[edgeIndex_];
}

template<typename T>
void EdgeListNetwork<T>::InternalIterator::AddFlow(T amount)
{
	network_->flow_[edgeIndex_] += amount;
	network_->flow_[edgeIndex_ ^ 1] -= amount;
}

template<typename T>
void EdgeListNetwork<T>::InternalIterator::advance()
{
	auto nextIndex = outgoing_ ? 
		network_->nextEdgeFrom_[edgeIndex_] 
			: network_->nextEdgeTo_[edgeIndex_];

	if (edgeIndex_ == nextIndex)
		ended_ = true;
	edgeIndex_ = nextIndex;
}

template<typename T>
bool EdgeListNetwork<T>::InternalIterator::ended()
{
	return ended_;
}

template<typename T>
std::unique_ptr<typename Network<T>::InternalIterator>
	EdgeListNetwork<T>::InternalIterator::copy()
{
	std::unique_ptr<InternalIterator> copy(
			new InternalIterator(edgeIndex_, network_, outgoing_));
	copy->ended_ = ended_;
	return copy;
}
