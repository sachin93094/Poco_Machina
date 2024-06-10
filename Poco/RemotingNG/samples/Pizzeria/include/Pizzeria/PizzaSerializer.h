//
// PizzaSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_Pizzeria_Pizza_INCLUDED
#define TypeSerializer_Pizzeria_Pizza_INCLUDED


#include "Pizzeria/ExtToppingDeserializer.h"
#include "Pizzeria/ExtToppingSerializer.h"
#include "Pizzeria/Pizza.h"
#include "Pizzeria/PizzaDetailsDeserializer.h"
#include "Pizzeria/PizzaDetailsSerializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Pizzeria::Pizza>
{
public:
	static void serialize(const std::string& name, const Pizzeria::Pizza& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Pizzeria::Pizza& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"name"s,"toppings"s,"basePrice"s,"details"s,""s};
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[0], value.getName(), ser);
		TypeSerializer<std::vector<Pizzeria::ExtTopping>>::serialize(REMOTING__NAMES[1], value.getToppings(), ser);
		TypeSerializer<Poco::UInt32>::serialize(REMOTING__NAMES[2], value.getBasePrice(), ser);
		TypeSerializer<Pizzeria::Pizza::Details>::serialize(REMOTING__NAMES[3], value.getDetails(), ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Pizzeria_Pizza_INCLUDED

