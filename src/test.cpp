#include "EdgeListNetwork.hpp"
#include "NetworkBuilder.hpp"
#include "MalhotraKumarMaheshvari.hpp"


using Type = long long;



int main()
{
	std::size_t vertCount = 0;
	std::size_t edgeCount = 0;
	std::cin >> vertCount >> edgeCount;

	NetworkBuilder<EdgeListNetwork, Type> builder;
	builder.Initialize(vertCount).SetSource(0).SetTarget(vertCount - 1);

	for (std::size_t i = 0; i < edgeCount; ++i)
	{
		std::size_t from = 0;
		std::size_t to = 0;
		Type cap = 0;
		std::cin >> from >> to >> cap;
		builder.AddCapacity(from, to, cap);
	}

	std::shared_ptr<Network<Type>> network(builder.Finalize());

	//std::cout << *network << std::endl;

	MalhotraKumarMaheshvari<Type> algorithm;
	algorithm.Initialize(network);
	algorithm.Calculate();
	Type answer = algorithm.GetFlow();

	std::cout << answer << std::endl;
	
	//std::cout << *network << std::endl;

	return 0;
}