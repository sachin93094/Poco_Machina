//
// FileModule.cpp
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/Module.h"
#include "Poco/OSP/JS/ModuleFactory.h"
#include "Poco/JS/File/FileWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/ClassLibrary.h"
#include "v8.h"


using Poco::JS::Core::Wrapper;
using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JS {
namespace File {


class FileWrapper: public Poco::JS::Core::Wrapper
{
public:
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate)
	{
		v8::EscapableHandleScope handleScope(pIsolate);
		Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
		poco_check_ptr (pPooledIso);
		v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("OSP.File"s));
		if (pooledObjectTemplate.IsEmpty())
		{
			v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
			objectTemplate->SetInternalFieldCount(1);

			Poco::JS::File::FileWrapper fileWrapper;
			objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "File"s), fileWrapper.constructor(pIsolate));

			pooledObjectTemplate.Reset(pIsolate, objectTemplate);
		}
		v8::Local<v8::ObjectTemplate> fileTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
		return handleScope.Escape(fileTemplate);
	}
};


class FileModule: public Poco::JS::Core::Module
{
public:
	v8::Local<v8::Object> exportIt(v8::Isolate* pIsolate)
	{
		v8::EscapableHandleScope handleScope(pIsolate);

		FileWrapper fileWrapper;
		v8::MaybeLocal<v8::Object> maybeModuleObject = fileWrapper.wrapNative(pIsolate);
		v8::Local<v8::Object> moduleObject;
		if (maybeModuleObject.ToLocal(&moduleObject))
		{
			return handleScope.Escape(moduleObject);
		}
		else
		{
			return moduleObject;
		}
	}
};


class FileModuleFactory: public Poco::OSP::JS::ModuleFactory
{
public:
	Poco::JS::Core::Module* createModule()
	{
		return new FileModule;
	}
};


} } } } // namespace Poco::OSP::JS::File


POCO_BEGIN_NAMED_MANIFEST(Module, Poco::OSP::JS::ModuleFactory)
	POCO_EXPORT_CLASS(Poco::OSP::JS::File::FileModuleFactory)
POCO_END_MANIFEST

