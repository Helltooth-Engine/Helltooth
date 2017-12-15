#include <string>

namespace ht { namespace utils {

	class String {
	private:
		char* m_Data = nullptr;
		unsigned int m_Size;

		mutable unsigned int m_HashValue = 0;

	public:
		String();
		String(const String& other);
		String(const char* string);
		String(const std::string& string);
		String(char c, int rep = 1);

		~String();

		void Append(char c);
		void Append(const char* string);
		void Append(const String& string);
		void Append(const std::string& string);

		String Substring(unsigned int left, unsigned int right = (unsigned int)-1);

		void Clear();

		unsigned int Hash() const;

		inline unsigned int GetSize() const { return m_Size; }
		inline const char* GetData() const { return m_Data; }

	public: // operator block

		inline friend String operator+(String left, char right) { left.Append(right); return left; }
		inline friend String operator+(String left, const char* right) { left.Append(right); return left; }
		inline friend String operator+(String left, const String& right) { left.Append(right); return left; }
		inline friend String operator+(String left, const std::string& right) { left.Append(right); return left; }

		inline void operator+=(char other) { Append(other); }
		inline void operator+=(const char* other) { Append(other); }
		inline void operator+=(const String& other) { Append(other); }
		inline void operator+=(const std::string& other) { Append(other); }

		inline bool operator==(const String& other) const { return (Hash() == other.Hash()); }
		inline bool operator!=(const String& other) const { return (Hash() != other.Hash()); }

		inline char operator[](unsigned int index) const { return m_Data[index]; }
	};

} }