#pragma once

#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include <string>

// Cheerp: Cannot call function 'stoi' with attribute 'asmjs' from function 'getNumericInput' with attribute 'genericjs', because parameter pointer is a '__idx' to a basic type
static int __stoi(std::string& s) {
	return std::stoi(s);
}

[[cheerp::genericjs]]
int getNumericInput(client::HTMLInputElement* inputElement) {
	std::string valueString = std::string(*(inputElement->get_value()));
	return __stoi(valueString);
}
