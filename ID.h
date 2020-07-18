#pragma once

#include <cstdint>
#include <memory>

namespace tezcat
{
	typedef std::uint32_t uint32_t;
	typedef std::uint64_t uint64_t;

	class ID
	{
	public:
		ID() : m_ID(0) {}
		explicit ID(uint64_t id) : m_ID(id) {}
		ID(uint32_t group, uint32_t index) : m_ID(uint64_t(index) | uint64_t(group) << 32UL) {}

		//获得ID
		uint64_t getID() const { return m_ID; }
		//组中索引
		uint32_t getIndex() const { return m_ID & 0xffffffffUL; }
		//组别
		uint32_t getGroup() const { return m_ID >> 32; }

		bool operator == (const ID &other) const
		{
			return m_ID == other.m_ID;
		}

		bool operator != (const ID &other) const
		{
			return m_ID != other.m_ID;
		}

		bool operator < (const ID &other) const
		{
			return m_ID < other.m_ID;
		}


	private:
		uint64_t m_ID;
	};

	static const ID INVALID;
}