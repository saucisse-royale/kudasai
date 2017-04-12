#pragma once

#include <functional>
#include <iostream>

#define RAII_NULL_HANDLE (0)

namespace kds {

	/// A RAII wrapper for objects that need to be freed through a deleter function
	/// This is completely generic, it will work with any deleter function
	///
	/// How to use:
	/// Declare object as
	/// 	RAII<ObjectType> object{deleter, args...};
	///
	/// Cleanup will be performed when the object goes out of scope
	///
	/// If the deleter function is not yet loaded when the object is declared, use
	/// 	RAII<ObjectType> object{};
	/// And when the deleter function is laoded, call
	/// 	object.setDeleter(deleter, args...);
	///
	/// To modify a wrapped object, use
	/// 	object = rhs;
	/// Or
	/// 	pObject.reset() = pRhs;
	///	for pointers
	template<typename Type>
	class RAII {
	public:

		template<typename Fun, typename... Args>
		RAII(Fun&& fun, Args&&... args) noexcept :
			_deleter{ [&]{ std::forward<Fun>(fun)(std::forward<Args>(args)...); } }
		{}

		RAII() = default;
		RAII(RAII&&) = default;


		~RAII() noexcept {
			_clean();
		}

		Type* reset() noexcept {
			_clean();
			return &_obj;
		}

		template<typename Fun, typename... Args>
		RAII<Type>& reset(Type obj, Fun&& fun, Args&&... args) noexcept {
			_clean();
			_obj = obj;
			_deleter = [&]{ std::forward<Fun>(fun)(std::forward<Args>(args)...); };
			return *this;
		}

		template<typename Fun, typename... Args>
		void setDeleter(Fun&& fun, Args&&... args) noexcept {
			_deleter = [&]{ std::forward<Fun>(fun)(std::forward<Args>(args)...); };
		}

		Type const* operator&() noexcept {
			return &_obj;
		}

		operator Type() noexcept {
			return _obj;
		}

		template<typename OtherType>
		bool operator==(OtherType const& rhs) const noexcept {
			return Type(rhs) == _obj;
		}

		void operator=(Type rhs) noexcept {
			if (rhs != _obj) {
				_clean();
				_obj = rhs;
			}
		}

	private:
		void _clean() {
			if (_obj != RAII_NULL_HANDLE) {
				_deleter();
				_obj = RAII_NULL_HANDLE;
			}
		}

		Type _obj{RAII_NULL_HANDLE};
		std::function<void(void)> _deleter{[]{}};
	}; // class RAII
} // namespace kds
