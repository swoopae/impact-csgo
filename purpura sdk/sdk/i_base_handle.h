#pragma once

#define NUM_ENT_ENTRY_BITS         (11 + 2)
#define NUM_ENT_ENTRIES            (1 << NUM_ENT_ENTRY_BITS)
#define INVALID_EHANDLE_INDEX 0xFFFFFFFF
#define NUM_SERIAL_NUM_BITS        16 // (32 - NUM_ENT_ENTRY_BITS)
#define NUM_SERIAL_NUM_SHIFT_BITS (32 - NUM_SERIAL_NUM_BITS)
#define ENT_ENTRY_MASK             (( 1 << NUM_SERIAL_NUM_BITS) - 1)

class c_base_handle;

class i_handle_entity
{
public:
	virtual ~i_handle_entity() {}
	virtual void SetRefEHandle(const c_base_handle &handle) = 0;
	virtual const c_base_handle& GetRefEHandle() const = 0;
};

class c_base_handle
{
	friend class i_client_entity_list;
public:
	c_base_handle();
	c_base_handle(const c_base_handle &other);
	c_base_handle(unsigned long value);
	c_base_handle(int iEntry, int iSerialNumber);

	void Init(int iEntry, int iSerialNumber);
	void Term();

	// Even if this returns true, Get() still can return return a non-null value.
	// This just tells if the handle has been initted with any values.
	bool IsValid() const;

	int GetEntryIndex() const;
	int GetSerialNumber() const;

	int ToInt() const;
	bool operator !=(const c_base_handle &other) const;
	bool operator ==(const c_base_handle &other) const;
	bool operator ==(const i_handle_entity* pEnt) const;
	bool operator !=(const i_handle_entity* pEnt) const;
	bool operator <(const c_base_handle &other) const;
	bool operator <(const i_handle_entity* pEnt) const;

	// Assign a value to the handle.
	const c_base_handle& operator=(const i_handle_entity *pEntity);
	const c_base_handle& Set(const i_handle_entity *pEntity);

	i_handle_entity* Get() const;
protected:
	unsigned long  m_Index;
};

template< class T >
class c_handle : public c_base_handle
{
public:

	c_handle();
	c_handle(int iEntry, int iSerialNumber);
	c_handle(const c_base_handle &handle);
	c_handle(T *pVal);

	static c_handle<T> FromIndex(int index);

	T*        Get() const;
	void Set(const T* pVal);

	operator T*();
	operator T*() const;

	bool operator !() const;
	bool operator==(T *val) const;
	bool operator!=(T *val) const;
	const c_base_handle& operator=(const T *val);

	T*        operator->() const;
};

template<class T>
c_handle<T>::c_handle()
{
}

template<class T>
c_handle<T>::c_handle(int iEntry, int iSerialNumber)
{
	Init(iEntry, iSerialNumber);
}

template<class T>
c_handle<T>::c_handle(const c_base_handle &handle)
	: c_base_handle(handle)
{
}

template<class T>
c_handle<T>::c_handle(T *pObj)
{
	Term();
	Set(pObj);
}

template<class T>
inline c_handle<T> c_handle<T>::FromIndex(int index)
{
	c_handle<T> ret;
	ret.m_Index = index;
	return ret;
}

template<class T>
inline T* c_handle<T>::Get() const
{
	return (T*)c_base_handle::Get();
}

template<class T>
inline c_handle<T>::operator T *()
{
	return Get();
}

template<class T>
inline c_handle<T>::operator T *() const
{
	return Get();
}

template<class T>
inline bool c_handle<T>::operator !() const
{
	return !Get();
}

template<class T>
inline bool c_handle<T>::operator==(T *val) const
{
	return Get() == val;
}

template<class T>
inline bool c_handle<T>::operator!=(T *val) const
{
	return Get() != val;
}

template<class T>
void c_handle<T>::Set(const T* pVal)
{
	c_base_handle::Set(reinterpret_cast<const i_handle_entity*>(pVal));
}

template<class T>
inline const c_base_handle& c_handle<T>::operator=(const T *val)
{
	Set(val);
	return *this;
}

template<class T>
T* c_handle<T>::operator -> () const
{
	return Get();
}

inline c_base_handle::c_base_handle()
{
	m_Index = INVALID_EHANDLE_INDEX;
}

inline c_base_handle::c_base_handle(const c_base_handle &other)
{
	m_Index = other.m_Index;
}

inline c_base_handle::c_base_handle(unsigned long value)
{
	m_Index = value;
}

inline c_base_handle::c_base_handle(int iEntry, int iSerialNumber)
{
	Init(iEntry, iSerialNumber);
}

inline void c_base_handle::Init(int iEntry, int iSerialNumber)
{
	m_Index = (unsigned long)(iEntry | (iSerialNumber << NUM_SERIAL_NUM_SHIFT_BITS));
}

inline void c_base_handle::Term()
{
	m_Index = INVALID_EHANDLE_INDEX;
}

inline bool c_base_handle::IsValid() const
{
	return m_Index != INVALID_EHANDLE_INDEX;
}

inline int c_base_handle::GetEntryIndex() const
{
	// There is a hack here: due to a bug in the original implementation of the
	// entity handle system, an attempt to look up an invalid entity index in
	// certain cirumstances might fall through to the the mask operation below.
	// This would mask an invalid index to be in fact a lookup of entity number
	// NUM_ENT_ENTRIES, so invalid ent indexes end up actually looking up the
	// last slot in the entities array. Since this slot is always empty, the
	// lookup returns NULL and the expected behavior occurs through this unexpected
	// route.
	// A lot of code actually depends on this behavior, and the bug was only exposed
	// after a change to NUM_SERIAL_NUM_BITS increased the number of allowable
	// static props in the world. So the if-stanza below detects this case and
	// retains the prior (bug-submarining) behavior.
	if (!IsValid())
		return NUM_ENT_ENTRIES - 1;
	return m_Index & ENT_ENTRY_MASK;
}

inline int c_base_handle::GetSerialNumber() const
{
	return m_Index >> NUM_SERIAL_NUM_SHIFT_BITS;
}

inline int c_base_handle::ToInt() const
{
	return (int)m_Index;
}

inline bool c_base_handle::operator !=(const c_base_handle &other) const
{
	return m_Index != other.m_Index;
}

inline bool c_base_handle::operator ==(const c_base_handle &other) const
{
	return m_Index == other.m_Index;
}

inline bool c_base_handle::operator ==(const i_handle_entity* pEnt) const
{
	return Get() == pEnt;
}

inline bool c_base_handle::operator !=(const i_handle_entity* pEnt) const
{
	return Get() != pEnt;
}

inline bool c_base_handle::operator <(const c_base_handle &other) const
{
	return m_Index < other.m_Index;
}

inline bool c_base_handle::operator <(const i_handle_entity *pEntity) const
{
	unsigned long otherIndex = (pEntity) ? pEntity->GetRefEHandle().m_Index : INVALID_EHANDLE_INDEX;
	return m_Index < otherIndex;
}

inline const c_base_handle& c_base_handle::operator=(const i_handle_entity *pEntity)
{
	return Set(pEntity);
}

inline const c_base_handle& c_base_handle::Set(const i_handle_entity *pEntity)
{
	if (pEntity)
		*this = pEntity->GetRefEHandle();
	else
		m_Index = INVALID_EHANDLE_INDEX;

	return *this;
}