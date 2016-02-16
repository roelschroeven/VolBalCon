//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <RsUtil.h>

#include "ComPtr.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ECom::ECom(AnsiString FunctionName, HRESULT hr): Exception(""), hr(hr)
{
  Message = rsutil::PrintF("%s: error %u == 0x%08x == \"%ls\"",
    FunctionName.c_str(),
    hr,
    hr,
    rsutil::GetErrorText(hr).c_str());
}

IUnknown* CoCreateInstance(REFCLSID ClassId, REFIID InterfaceId)
{
  IUnknown *pResult;
  HRESULT hr = CoCreateInstance(ClassId, NULL, CLSCTX_INPROC_SERVER, InterfaceId, (void**)&pResult);
  if (!SUCCEEDED(hr))
    throw ECom("CoCreateInstance()", hr);
  return pResult;
}

IUnknown* QueryInterface(IUnknown *pIUnknown, REFIID InterfaceId)
{
  IUnknown *pResult;
  HRESULT hr = pIUnknown->QueryInterface(InterfaceId, (void**)&pResult);
  if (!SUCCEEDED(hr))
    throw ECom("QueryInterface()", hr);
  return pResult;
}

IUnknown* QueryInterface(TComPtr<IUnknown> Unknown, REFIID InterfaceId)
{
  return QueryInterface(Unknown.get(), InterfaceId);
}

#ifdef TRACK_REFCOUNTS
std::map<IUnknown*, unsigned> RefCounts;
#endif

