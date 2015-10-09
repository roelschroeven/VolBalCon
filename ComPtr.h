//---------------------------------------------------------------------------

#ifndef ComPtrH
#define ComPtrH
//---------------------------------------------------------------------------

#include <objbase.h>

struct ECom: public Exception { ECom(AnsiString FunctionName, HRESULT hr); HRESULT hr; };

#define COM_CHECKED(expr)   {HRESULT hr = (expr); if (!SUCCEEDED(hr)) throw ECom(#expr, hr); }


//---------------------------------------------------------------------------

//#define TRACK_REFCOUNTS
#ifdef TRACK_REFCOUNTS
#include <map>
extern std::map<IUnknown*, unsigned> RefCounts;
#endif

//
// Manage COM-pointers, much like boost::intrusive_ptr does but specially made
// for COM pointers.
//
// In short:
//  - call AddRef() when a new reference is created
//  - call Release() when a reference is removed
//
// Warning: only use this with pointers to IUnknown or subclasses!!
//

void TComPtrAddRef(IUnknown *p);
void TComPtrRelease(IUnknown *p);

template<class T> GUID uuidof() { return __uuidof(T); }

template<class T> class TComPtr
{
public:

  //
  // Constructors: construct empty object, construct from contained type pointer, construct from
  // other TComPtr object
  //

  TComPtr(): px(0)  {  }

  explicit TComPtr(T * p, bool DoAddRef=false): px(p)
  {
#ifdef TRACK_REFCOUNTS
    // Increase our idea of the reference count here because it's assumed that the pointer comes
    // from something like QueryInterface() and it had already increased the real reference count.
    if (p)
      RefCounts[p] += 1;
#endif
    if (DoAddRef)
      AddRef();
  }

  explicit TComPtr(IUnknown * p, bool DoAddRef=false): px((T*)p)
  {
#ifdef TRACK_REFCOUNTS
    // Increase our idea of the reference count here because it's assumed that the pointer comes
    // from something like QueryInterface() and it had already increased the real reference count.
    if (p)
      RefCounts[p] += 1;
#endif
    if (DoAddRef)
      AddRef();
  }

  TComPtr(REFCLSID ClassId, REFIID InterfaceId)
  {
  px = (T*)CoCreateInstance(ClassId, InterfaceId);
#ifdef TRACK_REFCOUNTS
    if (px)
      RefCounts[px] += 1;
#endif
  }

  explicit TComPtr(const TComPtr<T> &other): px(other.get())
  {
    AddRef();
  }

  //
  // Destructor
  //

  ~TComPtr()
  {
    Release();
  }

  //
  // Assignment operators
  // (Release() on old contained pointer, AddRef() on new contained pointer)
  //

  TComPtr & operator=(const TComPtr<T> &other)
  {
    if (px == other.px)
      return *this;
    Release();
    px = other.get();
    AddRef();
    return *this;
  }

  TComPtr & operator=(T *p)
  {
    Release();
    px = p;
    AddRef();
    return *this;
  }

  void reset()
  {
    Release();
    px = NULL;
  }

  // Conversion operator to TComPtr of base class (i.e. IUnknown)
  operator TComPtr<IUnknown>()
  {
    TComPtr<IUnknown> t;
    t = (IUnknown*)px;
    return t;
  }
  // Conversion operator to bool for use in boolean contexts (false if underlying pointer is NULL,
  // true otherwise)
  operator bool() { return bool(px); }

  //
  // Access to contained pointer
  //

  T * get() const         { return px; }

  T & operator*() const   { return *px; }

  T * operator->() const  { return px;  }


private:

  T * px;

  void Release()
  {
    if (px)
      {
#ifdef TRACK_REFCOUNTS
      if (RefCounts[px] == 0)
        OutputDebugString("RefCount already 0!!");
#endif
      // Cast to IUnknown: otherwise we need to include the C-Map header files all over the place
      // (for the compiler to know all the different interfaces at this point)
      ((IUnknown*)px)->Release();
      //TComPtrRelease(px);
#ifdef TRACK_REFCOUNTS
      RefCounts[px] -= 1;
#endif
      }
  }

  void AddRef()
  {
    if (px)
      {
      // Cast to IUnknown: otherwise we need to include the C-Map header files all over the place
      // (for the compiler to know all the different interfaces at this point)
      ((IUnknown*)px)->AddRef();
#ifdef TRACK_REFCOUNTS
      RefCounts[px] += 1;
#endif
      }
  }

};

//
// Comparison operators
// (just compare the pointers)
//

template<class T, class U> inline bool operator==(TComPtr<T> const &a, TComPtr<U> const &b)
{
  return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(TComPtr<T> const &a, TComPtr<U> const &b)
{
  return a.get() != b.get();
}

template<class T, class U> inline bool operator<(TComPtr<T> const &a, TComPtr<U> const &b)
{
  return a.get() < b.get();
}


//---------------------------------------------------------------------------


IUnknown* CoCreateInstance(REFCLSID ClassId, REFIID InterfaceId);
IUnknown* QueryInterface(IUnknown *pIUnknown, REFIID InterfaceId);
IUnknown* QueryInterface(TComPtr<IUnknown> Unknown, REFIID InterfaceId);

#endif
