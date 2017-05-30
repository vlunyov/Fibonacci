#include <iostream>
#include <vector>
#include <algorithm>

class AsciiNum
{
public:
	AsciiNum() = default;

	AsciiNum(long long x)
	{
		auto s = std::to_string(x);
		m_num.resize(s.size());
		std::reverse_copy(std::begin(s), std::end(s), m_num.begin());
	}

	AsciiNum(const std::string& str)
	{
		// TODO It is need to be implemented for testing.
	}

	AsciiNum(const AsciiNum& other)
	{
		m_num = other.m_num;
	}

	AsciiNum(AsciiNum&& other)
	{
		m_num = std::move(other.m_num);
	}

	AsciiNum& operator=(const AsciiNum& other)
	{
		m_num = other.m_num;
		return *this;
	}

	AsciiNum& operator=(AsciiNum&& other)
	{
		m_num = std::move(other.m_num);
		return *this;
	}

	std::string string() const
	{
		std::string s(m_num.size(), ' ');
		std::reverse_copy(std::begin(m_num), std::end(m_num), std::begin(s));
		return s;
	}

	AsciiNum& operator+=(const AsciiNum& other)
	{
		if(m_num.size() < other.m_num.size())
		{
			m_num.resize(other.m_num.size(), '0');
		}
		bool carry = false;
		for(std::size_t i = 0; i < m_num.size(); ++i)
		{
			char ch = i < other.m_num.size() ? other.m_num[i] : '0';
			m_num[i] += ch - '0' + carry;
			carry = m_num[i] > '9';
			if(carry)
			{
				m_num[i] -= 10;
			}
		}
		if(carry)
		{
			m_num.push_back('1');
		}
		return *this;
	}

private:
	std::vector<char> m_num;
};

bool operator==(const AsciiNum& left, const AsciiNum& right)
{
	return left.string() == right.string();
}

bool operator!=(const AsciiNum& left, const AsciiNum& right)
{
	return !operator==(left, right);
}

std::ostream& operator<<(std::ostream& os, const AsciiNum& num)
{
	return os << num.string();
}


template<typename F, typename N = int>
F fibonacci(N n, F first = 0, F second = 1)
{
	while(--n)
	{
		F temp{first};
		first = second;
		temp += second;
		second = temp;
	}
	return first;
}

namespace fibonacci_self_test {

void test()
{
	for(int i = 0; i < 93; ++i)
	{
		auto x = i + 1;
		auto f1 = fibonacci<AsciiNum>(x);
		auto f2 = fibonacci<uint64_t>(x);
		if(f1 != f2)
		{
			std::cout << "ERROR: Fibonacci(" << x << "): "
					  << f1 << " != " << f2 << std::endl;
		}
	}
}

} // namespace fibonacci_self_test

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	fibonacci_self_test::test();

	std::cout << "Fibonacci large numbers calculation\n";

	for(int i = 0; i < 100; ++i)
	{
		auto x = i + 1;
		auto f = fibonacci<AsciiNum>(x);
		std::cout << "Fibonacci(" << x << ")=" << f << std::endl;
	}

	return 0;
}
