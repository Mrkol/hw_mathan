#include "Network.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& out, Network<T>& network)
{
	out << "digraph G" << std::endl;
	out << "{" << std::endl;
	out << "\t" << network.Source() << " [color=green]" << std::endl;
	out << "\t" << network.Target() << " [shape=box]" << std::endl;
	for (std::size_t i = 0; i < network.VerticeCount(); ++i)
	{
		auto it = network.IterateOutgoingEdgesAt(i);
		while (it)
		{
			out << "\t" << it->Source() << " -> " << it->Target() << " ";
			out << "[label=\"";
			out << it->Flow();
			out << "/";
			out << it->Capacity();
			out << "\"]" << std::endl;

			++it;
		}
	}
	out << "}" << std::endl;
	return out;
}


template<typename T>
Network<T>::Iterator::Iterator(std::unique_ptr<InternalIterator> internal)
	: internal_(std::move(internal))
{

}

template<typename T>
Network<T>::Iterator::Iterator(Iterator& other)
	: internal_(other.internal_->copy())
{

}

template<typename T>
auto Network<T>::Iterator::operator=(Iterator& other)
	-> Iterator&
{
	internal_ = other.internal_.copy();
	return *this;
}

template<typename T>
auto Network<T>::Iterator::operator->()
	-> InternalIterator*
{
	return &*internal_;
}

template<typename T>
auto Network<T>::Iterator::operator++()
	-> Iterator&
{
	internal_->advance();
	return *this;
}

template<typename T>
auto Network<T>::Iterator::operator++(int)
	-> Iterator
{
	Iterator copy(internal_->copy());
	++*this;
	return copy;
}

template<typename T>
Network<T>::Iterator::operator bool()
{
	return !internal_->ended();
}
