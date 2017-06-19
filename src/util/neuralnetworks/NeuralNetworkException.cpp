/**
 * @file
 * @author Leo Cazenille <leo.cazenille@upmc.fr>
 *
 *
 */

#include <include/util/neuralnetworks/NeuralNetworkException.h>

using namespace Neural;



/* --------------------- NeuralNetworkException --------------------- */

NeuralNetworkException::NeuralNetworkException(const std::string& what_arg) : runtime_error(what_arg) {
	// ...
}

