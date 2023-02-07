/* Icinga 2 | (c) 2023 Icinga GmbH | GPLv2+ */

#pragma once

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/key_extractors.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <utility>

namespace icinga
{

/**
 * A tree- and hash-map. Ordered iteration combined with O(1) lookup.
 *
 * @ingroup base
 */
template<class K, class V>
class HybridMap
{
public:
	typedef std::pair<const K, V> ValueType;

private:
	typedef boost::multi_index::member<ValueType, typename ValueType::first_type, &ValueType::first> IndexedByKey;

	typedef boost::multi_index_container<ValueType, boost::multi_index::indexed_by<
		boost::multi_index::ordered_unique<IndexedByKey>,
		boost::multi_index::hashed_unique<IndexedByKey>
	>> ActualMap;

public:
	typedef typename boost::multi_index::nth_index<ActualMap, 0>::type::iterator Iterator;

	bool Contains(const K& k) const
	{
		return GetHash().find(k) != GetHash().end();
	}

	bool Get(const K& k, V& v) const
	{
		auto pos (GetHash().find(k));

		if (pos == GetHash().end()) {
			return false;
		}

		v = pos->second;
		return true;
	}

	inline auto GetLength() const
	{
		return m_Data.size();
	}

	auto begin() const
	{
		return GetTree().begin();
	}

	auto end() const
	{
		return GetTree().end();
	}

	void Set(K k, V v)
	{
		m_Data.erase(k);
		m_Data.insert(ValueType(std::move(k), std::move(v)));
	}

	inline void Remove(const K& k)
	{
		m_Data.erase(k);
	}

	inline void Remove(const Iterator& i)
	{
		m_Data.erase(i);
	}

	inline void Clear()
	{
		m_Data.clear();
	}

private:
	ActualMap m_Data;

	inline auto& GetTree() const
	{
		return boost::get<0>(m_Data);
	}

	inline auto& GetHash() const
	{
		return boost::get<1>(m_Data);
	}
};

}
